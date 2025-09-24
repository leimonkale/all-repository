#include "stm32f10x.h"                  // Device header
#include "light.h"


//PA3   ADC1_IN3

void light_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	ADC_InitTypeDef ADC_InitStructure;
	
	//1.RCC  GPIO  ADC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
	
    //2.GPIO_Init()  ģ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
    //3.ADC_Init()   2��ADC ÿ��ADC��16��ͨ��  ����ʱ������ 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;  //�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;  //�ǵ��Σ���ͨ����ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //����
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //���������ת�� - ����������ת�� 
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //�����Ҷ��� 12λ
	ADC_InitStructure.ADC_NbrOfChannel = 1; //˳����й���ת���� ADC ͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure); //ADC1��ʼ��
	
	//ADC1_CH3   ����˳��:1  ����ʱ��:1.5����
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_1Cycles5);
	
    //4.ʹ��
	ADC_Cmd(ADC1, ENABLE);
}

void light_start(void)
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); //�������ת��
}

void light_stop(void)
{
	ADC_SoftwareStartConvCmd(ADC1, DISABLE); //�������ת��
}


int get_light_value(void)
{
	int value = 0;
	
	//�ȴ�ת�����
    while( ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	
	value = ADC_GetConversionValue(ADC1);
	
	return value; //0~4095  12λ�ľ���
}






