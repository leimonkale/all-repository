#include "stm32f10x.h"
#include "light.h"

// ��ʼ��Light1��ADC1_IN3 - PA3��
void light1_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    
    // ʹ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);  // ADCʱ��12MHz
    
    // ����PA3Ϊģ������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // ADC1���ã���ͨ������ģʽ��
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;  // ��ͨ������ɨ��
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  // ����ת��
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);
    
    // ����ADC1ͨ��3������ʱ��239.5����
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_239Cycles5);
    
    // У׼������
    ADC_Cmd(ADC1, ENABLE);
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1) == SET);
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1) == SET);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

// ��ʼ��Light2��ADC2_IN7 - PA7��
void light2_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    
    // ʹ��ʱ�ӣ�ADC2Ҳ��APB2�����ϣ�
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC2, ENABLE);
    // ADCʱ������light1_init�����ã������ظ�
    
    // ����PA7Ϊģ������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // ADC2���ã���ͨ������ģʽ��
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC2, &ADC_InitStructure);
    
    // ����ADC2ͨ��7������ʱ��239.5����
    ADC_RegularChannelConfig(ADC2, ADC_Channel_7, 1, ADC_SampleTime_239Cycles5);
    
    // У׼������
    ADC_Cmd(ADC2, ENABLE);
    ADC_ResetCalibration(ADC2);
    while(ADC_GetResetCalibrationStatus(ADC2) == SET);
    ADC_StartCalibration(ADC2);
    while(ADC_GetCalibrationStatus(ADC2) == SET);
    ADC_SoftwareStartConvCmd(ADC2, ENABLE);
}

// ��ȡLight1ֵ��ADC1��
int get_light1_value(void)
{
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    return ADC_GetConversionValue(ADC1);
}

// ��ȡLight2ֵ��ADC2��
int get_light2_value(void)
{
    while(ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC) == RESET);
    return ADC_GetConversionValue(ADC2);
}
