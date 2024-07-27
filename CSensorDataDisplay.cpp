/*
 * CSensorDataDisplay.cpp
 *
 *  Created on: 18.06.2023
 *      Author: Kuete Konwo
 */

#include "CSensorDataDisplay.h"

void CSensorDataDisplay::run() {
	// variable to store temp and press data
	float temp, press;
	CGpioPin csb(GPIOB, 1 << 12);
	string tempToStr;
	string pressToStr;
	// i2c Register address for bmp280
	const uint16_t bmp280Addr = 0b1110110;

// using i2c interface of the bmp280
	CBmp280I2cDriver bmp280I2c(&hi2c1, bmp280Addr);
//	CBmp280SpiDriver bmp280Spi(&hspi2, &csb);

// creation of a new Device to measure temp and Press
	CBmp280Device testDevice(&bmp280I2c);

	// creation and definition of RS PIN
	CGpioPin rs_pin(GPIOD, 1 << 2);
	// creation and definition of Enable PIN
	CGpioPin enable(GPIOC, 1 << 9);
	// creation and definition of DataBus
	CGpioBus data =
			CGpioBus().addPin(GPIOA, 1 << 11).addPin(GPIOA, 1 << 12).addPin(
			GPIOB, 1 << 1).addPin(GPIOB, 1 << 2);

	// Setting the device Mode
	testDevice.setMode(UltraLowPower, SBT_0_5);
	// saving the temperature and pressure measurements in local var.
	press = testDevice.getPressure();
	temp = testDevice.getTemperature();

	tempToStr = to_string(temp);
	pressToStr = to_string(press);
	// LCD screen creation
	CLcd1602 myLcd(&rs_pin, &enable, &data);
	// LCD initialisation
	myLcd.init();
	// give cursor Position for first Message
	myLcd.setCursor(0, 0);
	// write first Message to LCD screen
	myLcd.write("T:");
	// cursor for temperature
	myLcd.setCursor(0, 2);
	// write temperature to LCD screen
	myLcd.write(tempToStr);
	// cursor position for S.I Unit
	myLcd.setCursor(0, 11);
	// write S.I Unit
	myLcd.write("grad");
	// give cursor Position for second Message
	myLcd.setCursor(1, 0);
	// write P(Pressure) to screen
	myLcd.write("P:");
	myLcd.setCursor(1, 2);
	// write pressure to LCD screen
	myLcd.write(pressToStr);
	myLcd.setCursor(1, 11);
	// write S.I Unit
	myLcd.write("hPa");

	// Setting bmpMeasuring mode to UltraHighresolution
	testDevice.setMode(UltraHighresolution, SBT_1000);

	while (1) {
		// saving the temperature and pressure measurements in local var.
		press = testDevice.getPressure();
		temp = testDevice.getTemperature();
		// Execute the Programm every seconds and display on LCD
		tempToStr = to_string(temp);
		pressToStr = to_string(press);
		// give cursor Position for first Message
		myLcd.setCursor(0, 0);
		myLcd.write("T:");
		myLcd.setCursor(0, 2);
		// write temperature on LCD screen
		myLcd.write(tempToStr);
		myLcd.setCursor(0, 11);
		myLcd.write("grad");
		// give cursor Position for second Message
		myLcd.setCursor(1, 0);
		myLcd.write("P:");
		myLcd.setCursor(1, 2);
		// write pressure on LCD screen
		myLcd.write(pressToStr);
		myLcd.setCursor(1, 11);
		myLcd.write("hPa");

		HAL_Delay(1000);

	}
}
