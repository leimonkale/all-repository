#include "stm32f10x.h"
#include "light.h"  // 包含双ADC采集函数
#include "uart.h"
#include "engin.h"
#include <stdio.h>
#include "led.h"
#include "delay.h"
#include "systick.h"


// 1. 定义你的判断范围（核心参数，按需求设置）
#define FRONT_MIN 1000   // 正前方的最小差值
#define FRONT_MAX 1200 // 正前方的最大差值
#define SAMPLE_TIMES 5 

//PB8
void gpio_setIn()		//设置管脚为输入模式
{
	GPIO_InitTypeDef init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	init.GPIO_Pin = GPIO_Pin_8;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &init);
}
void gpio_setOut()		//设置管脚为输出模式
{
	GPIO_InitTypeDef init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	init.GPIO_Pin = GPIO_Pin_8;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &init);
}

int dht11_read(int *hum, int *tem)
{
	int cnt, i, j;
	char buf[5] = {0};
	
	//1、设置管脚为输出功能
	gpio_setOut();
	
	//2、拉低电平，持续 >= 18ms (20ms)
	GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET);
	systick_delay_ms(20);
	
	//3、拉高电平 30(us)
	GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_SET);
	systick_delay_us(30);
	
	//4、设置管脚为 输入模式
	gpio_setIn();
	
	//5、读取管脚电平，判断DHT11是否响应
	if( GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0){
		
		//等待低电平结束
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0);
		//等待高电平结束
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 1);
		
		for(i = 0; i < 5; i++){		//循环5次读取 5字节数据
			for(j = 7;j >= 0; j--){
				cnt = 0;
				//等待DHT11发送数据时 低电平结束
				while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0);
		
				//读取DHT11发送数据时 高电平的时长
				while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 1){
					cnt++;
					systick_delay_us(10);
				}
				if(cnt > 5){
					buf[i] = buf[i] | (1 << j);
				}
			}
		}
		//校验5字节中前 4字节之和的低 8位 是否等于 第5字节
		if( ((buf[0]+buf[1]+buf[2]+buf[3]) & 0xff) == buf[4]){
			*hum = buf[0];
			*tem = buf[2];
			return 0;
		}
	}
	return -1;
}
// 2. 定义方向枚举（使代码更易读）
typedef enum {
    DIR_LEFT = 0,       // 向左
    DIR_FRONT,          // 正前方
    DIR_RIGHT           // 向右
} Light_Direction;

// 3. 多采集取平均（减少ADC抖动，采集5次，去极值后平均）
uint16_t ADC_Get_Average(ADC_TypeDef* ADCx, uint8_t channel, uint8_t times) {
    uint16_t buf[SAMPLE_TIMES];
    uint16_t sum = 0, temp;
	uint8_t i;
	uint8_t j;
    
    // 采集times次数据
    for (i = 0; i < times; i++) {
        ADC_RegularChannelConfig(ADCx, channel, 1, ADC_SampleTime_239Cycles5); // 配置通道
        ADC_SoftwareStartConvCmd(ADCx, ENABLE);                                // 启动转换
        while (ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == RESET);                // 等待完成
        buf[i] = ADC_GetConversionValue(ADCx);                                 // 存数据
    }
    
    // 排序（去极值：去掉最大和最小，避免极端噪声）
    for (i = 0; i < times-1; i++) {
        for (j = 0; j < times-1-i; j++) {
            if (buf[j] > buf[j+1]) {
                temp = buf[j];
                buf[j] = buf[j+1];
                buf[j+1] = temp;
            }
        }
    }
    
    // 求和（去掉第一个最小和最后一个最大）
    for (i = 1; i < times-1; i++) {
        sum += buf[i];
    }
    
    // 返回平均值
    return sum / (times - 2);
}

Light_Direction Get_Light_Direction(void) {
    uint16_t adc_left, adc_right;
    int32_t diff; // 差值（用int32_t避免负数溢出）
    
    // 采集左右ADC值（各采集5次，去极值平均，抗抖动）
    adc_left = ADC_Get_Average(ADC1, ADC_Channel_3, 5);  // 左侧：ADC1_IN3（PA3）
    adc_right = ADC_Get_Average(ADC2, ADC_Channel_7, 5); // 右侧：ADC2_IN7（PA7）
    
    // 计算差值（关键：这里是“右侧 - 左侧”，需与硬件方向匹配）
    diff = adc_right - adc_left;
    
    // 判断方向
    if (diff < FRONT_MIN) {
        return DIR_LEFT;       // 差值 < 200 → 向左
    } else if (diff > FRONT_MAX) {
        return DIR_RIGHT;      // 差值 > 250 → 向右
    } else {
        return DIR_FRONT;      // 200 ≤ 差值 ≤ 250 → 正前方
    }
}

int main(void)
{
    Light_Direction dir;
    char buf[128];
    uint16_t adc_left, adc_right;
    
    // 初始化：双ADC（左=ADC1, 右=ADC2）和串口
	led_init();
	gpio_init();
	tim3_init();
	systick_init();
    light1_init();  // 左侧光敏电阻（PA3, ADC1）
    light2_init();  // 右侧光敏电阻（PA7, ADC2）
    uart_init(115200);
    
      while (1) {
		sprintf(buf,"模式运行中...%d %d %d %d %d %d\n",flag2,flag3,flag4,flag5,flag6,flag7);
		uart_send_str(buf);
		if(flag7){
			sprintf(buf,"flag7模式运行中...\n");
			uart_send_str(buf);
			if(flag3){
				TIM_SetCompare1(TIM3, 1000);
				flag3 = 0;
			}
			if(flag4){
				TIM_SetCompare1(TIM3, 1500);
				flag4 = 0;
			}
			if(flag5){
				TIM_SetCompare1(TIM3, 2000);
				flag5 = 0;
			}
			if(flag6){
				flag6 = 0;
				flag7 = 0;
			}
	   }else{
        // 采集最新的左右ADC值（用于打印）
		int tem, hum;
		 if( dht11_read(&hum, &tem) == 0){
		}
        adc_left = ADC_Get_Average(ADC1, ADC_Channel_3, 5);
        adc_right = ADC_Get_Average(ADC2, ADC_Channel_7, 5);
        
        // 判断方向
        dir = Get_Light_Direction();
        
        // 串口打印结果（便于调试，查看差值和方向）
        if(dir == DIR_LEFT){
			sprintf(buf, "左值：%d, 右值：%d, 差值：%d → 方向：向左, tem：%d,hum：%d\n", 
                        adc_left, adc_right, adc_right - adc_left,tem,hum);
					TIM_SetCompare1(TIM3, 2000);
					my_delay_ms(300);
		}else if(dir == DIR_FRONT){
			sprintf(buf, "左值：%d, 右值：%d, 差值：%d → 方向：正前方,tem：%d,hum：%d\n", 
                        adc_left, adc_right, adc_right - adc_left,tem,hum);
					TIM_SetCompare1(TIM3, 1500);
					my_delay_ms(300);
		}else if(dir == DIR_RIGHT){
			sprintf(buf, "左值：%d, 右值：%d, 差值：%d → 方向：向右,tem：%d,hum：%d\n", 
                        adc_left, adc_right, adc_right - adc_left,tem,hum);
					TIM_SetCompare1(TIM3, 1000);
					my_delay_ms(300);
        }
        uart_send_str(buf);  // 串口发送结果
		}
		
		if(flag2){
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		my_delay_ms(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		my_delay_ms(1000);
		
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
		my_delay_ms(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		my_delay_ms(1000);
		
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		my_delay_ms(1000);
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		my_delay_ms(1000);
			flag2 =0;
		}
		
		
        
        // 控制循环频率（500ms一次，可调整，避免数据刷屏过快）
        my_delay_ms(1000);
        
        // （可选）根据方向执行动作（如控制电机转向、LED指示）
        // if (dir == DIR_LEFT) Motor_Turn_Left();
        // else if (dir == DIR_RIGHT) Motor_Turn_Right();
        // else Motor_Go_Straight();
    }
}
