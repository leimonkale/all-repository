#include "stm32f10x.h"

// 自动重装载值数组（ARR）：决定音调（频率）
// 基于72MHz时钟，PSC=71（计数频率1MHz）
uint16_t arr_array[] = {
    512, 1024, 512, 2048, 512, 1024, 256, 1024,
    256, 512, 128, 512, 128, 256, 64, 256,
    512, 1024, 512, 2048, 512, 1024, 256, 1024,
    
    // 段落2：升调变异（约5秒）
    128, 256, 64, 128, 64, 128, 32, 128,
    32, 64, 32, 128, 32, 64, 16, 64,
    16, 32, 8, 32, 8, 16, 4, 16,
    
    // 段落3：高频冲击（约5秒）
    4, 8, 4, 16, 8, 16, 16, 32,
    16, 32, 32, 64, 32, 64, 64, 128,
    64, 128, 128, 256, 128, 256, 256, 512,
    
    // 段落4：中频震荡（约5秒）
    256, 512, 256, 1024, 512, 1024, 1024, 2048,
    1024, 2048, 2048, 4096, 2048, 4096, 4096, 8192,
    4096, 8192, 8192, 4096, 8192, 4096, 2048, 4096,
    
    // 段落5：低频过渡（约5秒）
    2048, 1024, 2048, 1024, 512, 1024, 512, 256,
    512, 256, 128, 256, 128, 64, 128, 64,
    256, 128, 256, 128, 512, 256, 512, 1024,
    
    // 段落6：收尾循环（约5秒）
    512, 1024, 256, 512, 128, 256, 64, 128,
    32, 64, 16, 32, 8, 16, 4, 8,
    8, 16, 16, 32, 32, 64, 64, 128
};

// 延时数组（单位：ms）：决定每个音符的播放时长，与上面数组一一对应
uint16_t delay_array[] = {
    // 第一段延时（较慢节奏）
    300, 300, 300, 400, 300, 300, 200, 400,
    200, 300, 150, 300, 150, 200, 100, 200,
    
    // 第二段延时（稍快）
    250, 250, 250, 350, 250, 250, 180, 350,
    180, 250, 130, 250, 130, 180, 90, 180,
    
    // 第三段延时（加快）
    100, 150, 100, 200, 100, 150, 80, 150,
    80, 100, 60, 100, 60, 80, 50, 80,
    
    // 第四段延时（再加快）
    50, 80, 50, 100, 80, 100, 100, 150,
    100, 150, 150, 200, 150, 200, 200, 300,
    
    // 第五段延时（放缓）
    200, 300, 200, 400, 300, 400, 400, 500,
    400, 500, 500, 600, 500, 600, 600, 700,
    
    // 第六段延时（渐慢收尾）
    500, 400, 500, 400, 300, 400, 300, 200,
    300, 200, 150, 200, 150, 100, 150, 100
};

// 数组长度（三组数组元素数量相同）
uint8_t note_count = sizeof(arr_array) / sizeof(arr_array[0]);


void gpio_init(){
	GPIO_InitTypeDef init;
	//PA6 外部时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	//PA6 引脚初始化
	init.GPIO_Pin = GPIO_Pin_6;
	init.GPIO_Speed = GPIO_Speed_50MHz;
	init.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_Init(GPIOA, &init);

}

void tim3_init(){
	TIM_TimeBaseInitTypeDef BaseInit;
	TIM_OCInitTypeDef OcInit;

	//TIM3_CH1的外部时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	//72000000(Hz) /(7200) = 10000(Hz)
	
	//TIM3_CH1的基本初始化
	BaseInit.TIM_Prescaler = 35;  //预分频
	BaseInit.TIM_Period = 3816;     //记数器值
	BaseInit.TIM_ClockDivision = TIM_CKD_DIV1; //二分频
	BaseInit.TIM_CounterMode = TIM_CounterMode_Down; //向下记数
	TIM_TimeBaseInit(TIM3, &BaseInit);

	OcInit.TIM_Pulse = 1908;							//比较寄存器值，占空比
	OcInit.TIM_OCMode = TIM_OCMode_PWM1;      
	OcInit.TIM_OCPolarity = TIM_OCPolarity_High; //通道模式为 PWM1模式
	OcInit.TIM_OutputState = ENABLE;          //输出极性：高电平
	TIM_OC1Init(TIM3, &OcInit);               //输出状态：使能

	TIM_Cmd(TIM3, ENABLE);                    //初始化通道
                                          //使能定时器3，定时开始工作。
}

void delay_us(uint32_t us) {
    uint32_t i;
    // 校准依据：50MHz = 50 个周期/μs，空循环单次约 10 个周期，故系数取 5（需实测微调）
    for (i = 0; i < us * 5; i++) {
        __NOP(); // 空操作，仅消耗时间
    }
}

void delay_ms(uint32_t ms) {
    uint32_t i;
    for (i = 0; i < ms; i++) {
        delay_us(1000); // 复用微秒延时，实现毫秒级
    }
}

int main(){

	gpio_init();
	tim3_init();
	while(1){
		int i;
		for(i = 0;i<sizeof(arr_array);i++){
			TIM_SetAutoreload(TIM3, arr_array[i]);
			TIM_SetCompare1(TIM3, arr_array[i]/2);
			delay_ms(delay_array[i]);
		}
		
	}

}
