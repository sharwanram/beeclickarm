/*
 * LED.cpp
 *
 *  Created on: 15. 9. 2013
 *      Author: Tomas Bures <bures@d3s.mff.cuni.cz>
 */

#include "LED.h"

LED LED::rxtx(GPIOD, GPIO_Pin_12, RCC_AHB1Periph_GPIOD);
LED LED::outOfSync(GPIOD, GPIO_Pin_14, RCC_AHB1Periph_GPIOD);
LED LED::rfRecv(GPIOD, GPIO_Pin_13, RCC_AHB1Periph_GPIOD);
LED LED::rfSend(GPIOD, GPIO_Pin_15, RCC_AHB1Periph_GPIOD);

LED::LED(GPIO_TypeDef* gpio, uint32_t pin, uint32_t clk) :	gpio(gpio), pin(pin), clk(clk) {
}

LED::~LED() {
}

void LED::init() {
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* Enable the GPIO_LED Clock */
	RCC_AHB1PeriphClockCmd(clk, ENABLE);

	/* Configure the GPIO_LED pin */
	GPIO_InitStructure.GPIO_Pin = pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(gpio, &GPIO_InitStructure);
}

void LED::on() {
	gpio->BSRRL = pin;
}

void LED::off() {
	gpio->BSRRH = pin;
}


PulseLED* PulseLED::tickListener;

void PulseLED::tickInterruptHandler() {
	tickListener->tick();
}


PulseLED::PulseLED(LED& led, int minimalOnTimeTicks) : led(led), minimalOnTimeTicks(minimalOnTimeTicks), onTicks(-1) {
	tickListener=this;
}

PulseLED::~PulseLED() {
}

void PulseLED::pulse() {
	onTicks = 0;
	led.on();
}

void PulseLED::tick() {
	if (onTicks != -1) {
		onTicks++;

		if (onTicks > minimalOnTimeTicks) {
			onTicks = -1;
			led.off();
		}
	}
}

