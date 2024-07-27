/*
 * CLcd1602.h
 *
 *  Created on: 03.05.2023
 *      Author: sonpa
 */

#ifndef SRC_CLCD1602_H_
#define SRC_CLCD1602_H_

#include "CGpioBus.h"
#include "CGpioPin.h"
#include "tim.h"

/**
 * Models an 16x02 LCD-screen for write operations in 4 Bit Mode
 */
class CLcd1602 {
private:
	/** A pointer to the RS pin. */
	CGpioPin *m_rs;
	/** A pointer to the Data address DB7-DB0. */
	CGpioBus *m_data;
	/** A pointer to the enable pin. */
	CGpioPin *m_enable;

	/**
	 * this Method writes a Nibble to the Data-bus
	 *
	 * @param rs value for the rs pin
	 * @param data databit to be written
	 */
	void writeNibble(uint8_t rs, uint8_t data);

	/**
	 * this Method writes a DataByte to the Data-bus by writing a
	 * Nibble to the MSB(DB7-DB4) first and to the LSB(DB3-DB0)
	 *
	 * @param rs value for the rs pin
	 * @param data databit to be written
	 */
	void writeByte(uint8_t rs, uint8_t data);
public:
	/**
	 * Method initialises an LCD screen to 4Bit Mode
	 */
	void init();

	/**
	 * Constructor for the class CLCD1602
	 *
	 * @param rs pointer to the rs Pin
	 * @param enable pointer to the enable Pin
	 * @param data pointer to the DataBus
	 */
	CLcd1602(CGpioPin *rs, CGpioPin *enable, CGpioBus *data);

	/**
	 * Method sets the cursor to the entered position
	 *
	 * @param row row to where the cursor should be
	 * @param column column to where the cursor should be
	 */
	void setCursor(int row, int column);

	/**
	 * Method writes a string of characters on the screen
	 *
	 * @param text Message to display on the screen
	 */
	void write(const char *text);

	/**
	 * Method overloads the above write method for simplification
	 *
	 * @param text Message to display on the screen
	 */
	void write(const string& text);
};

#endif /* SRC_CLCD1602_H_ */
