#include "stm32f10x.h"                  // Device header
#include "light.h"


//PA3   ADC1_IN3

void light_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	ADC_InitTypeDef ADC_InitStructure;
	
	//1.RCC  GPIO  ADC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
	
    //2.GPIO_Init()  模拟输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
    //3.ADC_Init()   2个ADC 每个ADC有16个通道  采样时间配置 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  //工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;  //是单次（单通道）模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //连续
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //由软件启动转换 - 调函数启动转换 
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //数据右对齐 12位
	ADC_InitStructure.ADC_NbrOfChannel = 1; //顺序进行规则转换的 ADC 通道的数目
	ADC_Init(ADC1, &ADC_InitStructure); //ADC1初始化
	
	//ADC1_CH3   采样顺序:1  采样时间:1.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_1Cycles5);
	
    //4.使能
	ADC_Cmd(ADC1, ENABLE);
}

void light_start(void)
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //软件启动转换
}

void light_stop(void)
{
	ADC_SoftwareStartConvCmd(ADC1, DISABLE); //软件启动转换
}


int get_light_value(void)
{
	int value = 0;
	
	//等待转换完成
    while( ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	
	value = ADC_GetConversionValue(ADC1);
	
	return value; //0~4095  12位的精度
}






