/*
 * CLcdTest.cpp
 *
 *  Created on: May 3, 2023
 *      Author: Kuete Konwo
 */

#include "CLcdTest.h"

void CLcdTest::run() {
	// creation and definition of RS PIN
	CGpioPin rs_pin(GPIOD, 1 << 2);
	// creation and definition of Enable PIN
	CGpioPin enable(GPIOC, 1 << 9);
	// creation and definition of DataBus
	CGpioBus data =
			CGpioBus().addPin(GPIOA, 1 << 11).addPin(GPIOA, 1 << 12).addPin(
			GPIOB, 1 << 1).addPin(GPIOB, 1 << 2);

	// LCD screen creation
	CLcd1602 myLcd(&rs_pin, &enable, &data);
	// LCD initialisation
	myLcd.init();
	// give cursor Position for first Message
	myLcd.setCursor(0, 5);
	// write message to LCD screen
	myLcd.write("Konwo");
	// give cursor Position for second Message
	myLcd.setCursor(1, 5);
	// write message to LCD screen
	myLcd.write("770042");

	while (1) {

	}
}

