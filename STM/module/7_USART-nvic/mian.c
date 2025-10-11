#include <stm32f10x.h>
#include <stdio.h>
#include <string.h>

void usart_init()
{
    GPIO_InitTypeDef init;
    USART_InitTypeDef uInit;
    
    // 1. 使能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO, ENABLE);
    
    // 2. 配置TX(PA9)和RX(PA10)
    init.GPIO_Pin = GPIO_Pin_9;
    init.GPIO_Speed = GPIO_Speed_50MHz;
    init.GPIO_Mode = GPIO_Mode_AF_PP;  // 复用推挽输出
    GPIO_Init(GPIOA, &init);
    
    init.GPIO_Pin = GPIO_Pin_10;
    init.GPIO_Mode = GPIO_Mode_IPU;  // 上拉输入（比浮空更稳定）
    GPIO_Init(GPIOA, &init);
    
    // 3. 配置USART1
    uInit.USART_BaudRate = 115200;
    uInit.USART_WordLength = USART_WordLength_8b;
    uInit.USART_StopBits = USART_StopBits_1;
    uInit.USART_Parity = USART_Parity_No;
    uInit.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    uInit.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &uInit);
    
    // 4. 使能接收中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART1, ENABLE);
}

void nvic_init()
{
	NVIC_InitTypeDef init;
    // 配置中断分组（必须先设置，否则优先级无效）
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    
    init.NVIC_IRQChannel = USART1_IRQn;
    init.NVIC_IRQChannelPreemptionPriority = 0;  // 抢占优先级
    init.NVIC_IRQChannelSubPriority = 1;         // 子优先级
    init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&init);
}

void usart_put(uint16_t ch)
{
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, ch);
}

void usart_send(char *src)
{
    while(*src)
        usart_put(*src++);
}

int fputc(int ch, FILE *fp)
{
    usart_put(ch);
    return 0;
}

void delay(int ms)
{
    int i;
    while(ms--)
        for(i = 0; i < 8050; i++);
}

char buf[32] = {0};
int flag = 0;

void USART1_IRQHandler()
{
    static int index = 0;
    uint8_t data;
    
    if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        data = USART_ReceiveData(USART1);  // 读取接收数据
        
        // 处理回车换行（兼容'\r'和'\n'）
        if(data == '\r' || data == '\n')
        {
            if(index > 0)  // 避免空数据触发
            {
                buf[index] = '\0';
                flag = 1;
                index = 0;
            }
        }
        else
        {
            // 限制缓冲区长度，防止溢出
            if(index < 31)
            {
                buf[index++] = data;
            }
            else
            {
                // 缓冲区满时强制结束
                buf[31] = '\0';
                flag = 1;
                index = 0;
            }
        }
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}

int main()
{
    nvic_init();
    usart_init();

    printf("usart init success\r\n");
    
    while(1)
    {
        if(flag)
        {
            printf("recv: %s\r\n", buf);
            memset(buf, 0, sizeof(buf));  // 清空缓冲区
            flag = 0;
        }
    }
}
