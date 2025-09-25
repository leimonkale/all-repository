#include "beep.h"
#include <stdint.h>
#include "stm32f10x.h"

// 自动重装载值数组（ARR）：决定音调（频率）
// 基于72MHz时钟，PSC=35（计数频率 72MHz / (35 + 1) = 2MHz ，这里结合下方参数按需调整 ，可根据实际情况校准）
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

// 延时函数（简单实现，如需更精准可使用系统滴答定时器等）
void delay_us(uint32_t us) {
    uint32_t i;
    // 校准依据：根据实际 CPU 频率调整循环次数，这里只是示例，需实测优化
    for (i = 0; i < us * 10; i++) {
        __NOP(); 
    }
}

void delay_ms(uint32_t ms) {
	uint32_t i;
    for (i = 0; i < ms; i++) {
        delay_us(1000);
    }
}

// 数组长度（三组数组元素数量相同）
uint8_t note_count = sizeof(arr_array) / sizeof(arr_array[0]);

// 用于控制蜂鸣器基础开关的 GPIO 相关定义（若使用外部中断控制基础开关时用到，可按需调整引脚）
#define BEEP_CTRL_GPIO_PORT    GPIOB
#define BEEP_CTRL_GPIO_PIN     GPIO_Pin_0
#define BEEP_CTRL_RCC          RCC_APB2Periph_GPIOB

// 用于 PWM 输出驱动蜂鸣器的定时器和通道相关定义（这里用 TIM3_CH1 举例，可按需修改）
#define BEEP_TIM               TIM3
#define BEEP_TIM_CH            TIM_Channel_1
#define BEEP_TIM_RCC_APB1      RCC_APB1Periph_TIM3
#define BEEP_GPIO_PORT         GPIOA
#define BEEP_GPIO_PIN          GPIO_Pin_6
#define BEEP_GPIO_AF_RCC       RCC_APB2Periph_GPIOA

// 函数实现
void beep_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    TIM_TimeBaseInitTypeDef tim_base_init_struct;
    TIM_OCInitTypeDef tim_oc_init_struct;

    // 初始化控制蜂鸣器基础开关的 GPIO（如果有需求用普通 GPIO 控制开关时）
    RCC_APB2PeriphClockCmd(BEEP_CTRL_RCC, ENABLE);
    gpio_init_struct.GPIO_Pin = BEEP_CTRL_GPIO_PIN;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BEEP_CTRL_GPIO_PORT, &gpio_init_struct);
    GPIO_ResetBits(BEEP_CTRL_GPIO_PORT, BEEP_CTRL_GPIO_PIN);  // 初始关闭

    // 初始化 PWM 输出相关的 GPIO 和定时器
    RCC_APB2PeriphClockCmd(BEEP_GPIO_AF_RCC | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(BEEP_TIM_RCC_APB1, ENABLE);

    // 配置 PWM 输出引脚
    gpio_init_struct.GPIO_Pin = BEEP_GPIO_PIN;
    gpio_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BEEP_GPIO_PORT, &gpio_init_struct);

    // 配置定时器时基
    tim_base_init_struct.TIM_Prescaler = 35;   // 预分频，可根据实际需求调整
    tim_base_init_struct.TIM_Period = 3816;    // 自动重装载值，配合预分频决定频率
    tim_base_init_struct.TIM_ClockDivision = TIM_CKD_DIV1;
    tim_base_init_struct.TIM_CounterMode = TIM_CounterMode_Down;  // 向下计数模式
    TIM_TimeBaseInit(BEEP_TIM, &tim_base_init_struct);

    // 配置 PWM 模式
    tim_oc_init_struct.TIM_OCMode = TIM_OCMode_PWM1;
    tim_oc_init_struct.TIM_OCPolarity = TIM_OCPolarity_High;
    tim_oc_init_struct.TIM_OutputState = TIM_OutputState_Enable;
    tim_oc_init_struct.TIM_Pulse = 1908;  // 初始比较值，决定占空比
    TIM_OC1Init(BEEP_TIM, &tim_oc_init_struct);  // 这里根据通道调整，如 TIM_Channel_1 就用 TIM_OC1Init

    TIM_Cmd(BEEP_TIM, ENABLE);  // 使能定时器
}

void beep_on(void)
{
    GPIO_SetBits(BEEP_CTRL_GPIO_PORT, BEEP_CTRL_GPIO_PIN);  // 普通 GPIO 控制打开（如果用这种方式）
    // 也可以通过调整 PWM 占空比等方式让蜂鸣器以特定频率持续响，比如：
    // TIM_SetCompare1(BEEP_TIM, TIM_GetAutoreload(BEEP_TIM) / 2);  // 占空比 50% 示例
}

void beep_off(void)
{
    GPIO_ResetBits(BEEP_CTRL_GPIO_PORT, BEEP_CTRL_GPIO_PIN);  // 普通 GPIO 控制关闭（如果用这种方式）
    // 或者关闭 PWM 输出：
    // TIM_SetCompare1(BEEP_TIM, 0);  // 占空比 0，停止 PWM 输出
}

// 播放自定义音调序列函数
void play_custom_tone(void)
{
	uint8_t i;
    for ( i = 0; i < note_count; i++) {
        TIM_SetAutoreload(BEEP_TIM, arr_array[i]);
        TIM_SetCompare1(BEEP_TIM, arr_array[i] / 2);  // 占空比 50% 示例，可按需调整
        delay_ms(delay_array[i]);
    }
}

