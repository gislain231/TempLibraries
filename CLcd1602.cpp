/*
 * CLcd1602.cpp
 *
 *  Created on: 03.05.2023
 *      Author: Kuete Konwo
 */

#include "CLcd1602.h"

void CLcd1602::writeNibble(uint8_t rs, uint8_t data) {
	// start the rs Pin
	m_rs->setState(rs);
	// start the enable Pin to prepare data transfer
	m_enable->setState(1);
	// Begin data transfer
	*m_data = data;
	// wait for 1ms to prevent unplanned events
	HAL_Delay(1);
	// Stop the data transfer after data transfer
	m_enable->setState(0);

}

void CLcd1602::writeByte(uint8_t rs, uint8_t data) {
	// write the high nibble to the MSB(7-4)
	writeNibble(rs, (data & 0xf0) >> 4);
	// write the low nibble to the LSB(3-0)
	writeNibble(rs, data & 0x0f);
}

void CLcd1602::init() {
	// LCD initialisation to 4Bit mode
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_Delay(40);	// wait for >15ms
	writeNibble(0, 0x3);
	HAL_Delay(10);	// wait for >4.1ms
	writeNibble(0, 0x3);
	HAL_Delay(5);	// wait for >100us
	writeNibble(0, 0x3);
	HAL_Delay(5);	// wait for >15ms
	writeNibble(0, 0x2); // 4Bit mode

	// display initialisation
	writeByte(0, 0x28);	 // function set: DL=0,N=1,F=0
	writeByte(0, 0x08);	 // Display control: D=0,C=0,B=0 off Mode
	writeByte(0, 0x01);	 // clear display
	// Entry Mode set:I/D=1(cursor increment) & S=0(no shift)
	writeByte(0, 0x06);
	// display control: display, cursor and blinking of cursor on
	writeByte(0, 0x0f);

}

CLcd1602::CLcd1602(CGpioPin *rs, CGpioPin *enable, CGpioBus *data) {
	// definition of the Attributes
	m_rs = rs;
	m_enable = enable;
	m_data = data;
}

void CLcd1602::setCursor(int row, int column) {
	int position;
	// calculating Cursor position
	if (row == 0) {
		// place the cursor with command for Ram
		position = column | 0x80;
	} else if (row == 1) {
		// place the cursor with command for Ram
		position = column | 0xc0;
	}
	// set the cursor to giving position
	writeByte(0, position);

}

void CLcd1602::write(const char *text) {
	// write the Message on the databus before end of characters
	while (*text != '\0') {
		// write to the address and increment to next data adr.
		writeByte(1, *text++);
	}
}

void CLcd1602::write(const string &text) {
	// call to the original write method
	write(text.c_str());
}

