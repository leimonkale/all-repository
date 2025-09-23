#ifndef __LIGHT_H
#define __LIGHT_H

#include "stm32f10x.h"

// Light1: ADC1_IN3 (PA3)
// Light2: ADC2_IN7 (PA7)
void light1_init(void);  // ADC1��ʼ��
void light2_init(void);  // ADC2��ʼ��
int get_light1_value(void);  // ��ȡLight1
int get_light2_value(void);  // ��ȡLight2

#endif
