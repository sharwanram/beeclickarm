/*
 * Timer.cpp
 *
 *  Created on: 18. 9. 2013
 *      Author: Tomas Bures <bures@d3s.mff.cuni.cz>
 */

#include "Timer.h"

Timer::Timer(TIM_TypeDef* tim, uint32_t clk) : tim(tim), clk(clk) {
}

Timer::~Timer() {
}

void Timer::init() {
	RCC_APB1PeriphClockCmd(clk, ENABLE);

	TIM_TimeBaseInitTypeDef timInitStruct;
	timInitStruct.TIM_Prescaler = 82;
	timInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	timInitStruct.TIM_Period = 0xFFFF;
	timInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	timInitStruct.TIM_RepetitionCounter = 0x00;
	TIM_TimeBaseInit(tim, &timInitStruct);

	TIM_Cmd(tim, ENABLE);
}