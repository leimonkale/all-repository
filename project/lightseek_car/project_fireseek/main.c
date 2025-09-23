#include "stm32f10x.h"
#include "light.h"  // ����˫ADC�ɼ�����
#include "uart.h"
#include "engin.h"
#include <stdio.h>
#include "led.h"
#include "delay.h"
#include "systick.h"


// 1. ��������жϷ�Χ�����Ĳ��������������ã�
#define FRONT_MIN 1000   // ��ǰ������С��ֵ
#define FRONT_MAX 1200 // ��ǰ��������ֵ
#define SAMPLE_TIMES 5 

//PB8
void gpio_setIn()		//���ùܽ�Ϊ����ģʽ
{
	GPIO_InitTypeDef init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	init.GPIO_Pin = GPIO_Pin_8;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &init);
}
void gpio_setOut()		//���ùܽ�Ϊ���ģʽ
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
	
	//1�����ùܽ�Ϊ�������
	gpio_setOut();
	
	//2�����͵�ƽ������ >= 18ms (20ms)
	GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET);
	systick_delay_ms(20);
	
	//3�����ߵ�ƽ 30(us)
	GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_SET);
	systick_delay_us(30);
	
	//4�����ùܽ�Ϊ ����ģʽ
	gpio_setIn();
	
	//5����ȡ�ܽŵ�ƽ���ж�DHT11�Ƿ���Ӧ
	if( GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0){
		
		//�ȴ��͵�ƽ����
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0);
		//�ȴ��ߵ�ƽ����
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 1);
		
		for(i = 0; i < 5; i++){		//ѭ��5�ζ�ȡ 5�ֽ�����
			for(j = 7;j >= 0; j--){
				cnt = 0;
				//�ȴ�DHT11��������ʱ �͵�ƽ����
				while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 0);
		
				//��ȡDHT11��������ʱ �ߵ�ƽ��ʱ��
				while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8) == 1){
					cnt++;
					systick_delay_us(10);
				}
				if(cnt > 5){
					buf[i] = buf[i] | (1 << j);
				}
			}
		}
		//У��5�ֽ���ǰ 4�ֽ�֮�͵ĵ� 8λ �Ƿ���� ��5�ֽ�
		if( ((buf[0]+buf[1]+buf[2]+buf[3]) & 0xff) == buf[4]){
			*hum = buf[0];
			*tem = buf[2];
			return 0;
		}
	}
	return -1;
}
// 2. ���巽��ö�٣�ʹ������׶���
typedef enum {
    DIR_LEFT = 0,       // ����
    DIR_FRONT,          // ��ǰ��
    DIR_RIGHT           // ����
} Light_Direction;

// 3. ��ɼ�ȡƽ��������ADC�������ɼ�5�Σ�ȥ��ֵ��ƽ����
uint16_t ADC_Get_Average(ADC_TypeDef* ADCx, uint8_t channel, uint8_t times) {
    uint16_t buf[SAMPLE_TIMES];
    uint16_t sum = 0, temp;
	uint8_t i;
	uint8_t j;
    
    // �ɼ�times������
    for (i = 0; i < times; i++) {
        ADC_RegularChannelConfig(ADCx, channel, 1, ADC_SampleTime_239Cycles5); // ����ͨ��
        ADC_SoftwareStartConvCmd(ADCx, ENABLE);                                // ����ת��
        while (ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == RESET);                // �ȴ����
        buf[i] = ADC_GetConversionValue(ADCx);                                 // ������
    }
    
    // ����ȥ��ֵ��ȥ��������С�����⼫��������
    for (i = 0; i < times-1; i++) {
        for (j = 0; j < times-1-i; j++) {
            if (buf[j] > buf[j+1]) {
                temp = buf[j];
                buf[j] = buf[j+1];
                buf[j+1] = temp;
            }
        }
    }
    
    // ��ͣ�ȥ����һ����С�����һ�����
    for (i = 1; i < times-1; i++) {
        sum += buf[i];
    }
    
    // ����ƽ��ֵ
    return sum / (times - 2);
}

Light_Direction Get_Light_Direction(void) {
    uint16_t adc_left, adc_right;
    int32_t diff; // ��ֵ����int32_t���⸺�������
    
    // �ɼ�����ADCֵ�����ɼ�5�Σ�ȥ��ֵƽ������������
    adc_left = ADC_Get_Average(ADC1, ADC_Channel_3, 5);  // ��ࣺADC1_IN3��PA3��
    adc_right = ADC_Get_Average(ADC2, ADC_Channel_7, 5); // �ҲࣺADC2_IN7��PA7��
    
    // �����ֵ���ؼ��������ǡ��Ҳ� - ��ࡱ������Ӳ������ƥ�䣩
    diff = adc_right - adc_left;
    
    // �жϷ���
    if (diff < FRONT_MIN) {
        return DIR_LEFT;       // ��ֵ < 200 �� ����
    } else if (diff > FRONT_MAX) {
        return DIR_RIGHT;      // ��ֵ > 250 �� ����
    } else {
        return DIR_FRONT;      // 200 �� ��ֵ �� 250 �� ��ǰ��
    }
}

int main(void)
{
    Light_Direction dir;
    char buf[128];
    uint16_t adc_left, adc_right;
    
    // ��ʼ����˫ADC����=ADC1, ��=ADC2���ʹ���
	led_init();
	gpio_init();
	tim3_init();
	systick_init();
    light1_init();  // ���������裨PA3, ADC1��
    light2_init();  // �Ҳ�������裨PA7, ADC2��
    uart_init(115200);
    
      while (1) {
		sprintf(buf,"ģʽ������...%d %d %d %d %d %d\n",flag2,flag3,flag4,flag5,flag6,flag7);
		uart_send_str(buf);
		if(flag7){
			sprintf(buf,"flag7ģʽ������...\n");
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
        // �ɼ����µ�����ADCֵ�����ڴ�ӡ��
		int tem, hum;
		 if( dht11_read(&hum, &tem) == 0){
		}
        adc_left = ADC_Get_Average(ADC1, ADC_Channel_3, 5);
        adc_right = ADC_Get_Average(ADC2, ADC_Channel_7, 5);
        
        // �жϷ���
        dir = Get_Light_Direction();
        
        // ���ڴ�ӡ��������ڵ��ԣ��鿴��ֵ�ͷ���
        if(dir == DIR_LEFT){
			sprintf(buf, "��ֵ��%d, ��ֵ��%d, ��ֵ��%d �� ��������, tem��%d,hum��%d\n", 
                        adc_left, adc_right, adc_right - adc_left,tem,hum);
					TIM_SetCompare1(TIM3, 2000);
					my_delay_ms(300);
		}else if(dir == DIR_FRONT){
			sprintf(buf, "��ֵ��%d, ��ֵ��%d, ��ֵ��%d �� ������ǰ��,tem��%d,hum��%d\n", 
                        adc_left, adc_right, adc_right - adc_left,tem,hum);
					TIM_SetCompare1(TIM3, 1500);
					my_delay_ms(300);
		}else if(dir == DIR_RIGHT){
			sprintf(buf, "��ֵ��%d, ��ֵ��%d, ��ֵ��%d �� ��������,tem��%d,hum��%d\n", 
                        adc_left, adc_right, adc_right - adc_left,tem,hum);
					TIM_SetCompare1(TIM3, 1000);
					my_delay_ms(300);
        }
        uart_send_str(buf);  // ���ڷ��ͽ��
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
		
		
        
        // ����ѭ��Ƶ�ʣ�500msһ�Σ��ɵ�������������ˢ�����죩
        my_delay_ms(1000);
        
        // ����ѡ�����ݷ���ִ�ж���������Ƶ��ת��LEDָʾ��
        // if (dir == DIR_LEFT) Motor_Turn_Left();
        // else if (dir == DIR_RIGHT) Motor_Turn_Right();
        // else Motor_Go_Straight();
    }
}
