/*
 * CGpioBus.cpp
 *
 *  Created on: Apr 27, 2023
 *      Author: Kuete Konwo
 */

#include "CGpioBus.h"

CGpioBus::CGpioBus() :
		m_pins(nullptr) {
	// TODO Auto-generated constructor stub
}

CGpioBus::CGpioBus(const CGpioBus &orig) {
	// create deep copy with Copy Constructor
	m_pins = nullptr;				// pointer init.

	for (Pin *myPin = orig.m_pins; myPin != nullptr; myPin = myPin->next) {
		// add existing Pins in the newly created Bus
		addPin(myPin->port, myPin->mask);
	}
}

CGpioBus& CGpioBus::operator =(const CGpioBus &src) {
	// assigns Pins to a Bus
	if (this != &src) {
		// left operand has different Contents(Pins) than right operand
		Pin *myPins = m_pins;
		m_pins = nullptr;		// init. pointer
		for (Pin *pins = src.m_pins; pins != nullptr; pins = pins->next) {
			// pass the rop pins to the lop pins one after the other
			addPin(pins->port, pins->mask);
		}
		while (myPins != nullptr) {
			// clear memory to avoid leakage
			Pin *next = myPins->next;
			delete myPins;
			myPins = next;
		}
	}
	return *this;
}

CGpioBus::~CGpioBus() {
	// TODO Auto-generated destructor stub
	// clear the  allocated dynamic Memory
	while (m_pins != nullptr) {
		// save the existing list of Pins
		Pin *next = m_pins->next;
		// delete existing list
		delete m_pins;
		// let the pointer point to the start of List
		m_pins = next;
	}
}

CGpioBus& CGpioBus::addPin(GPIO_TypeDef *port, uint16_t pinMask) {
	if (pinMask != m_pins->mask) {
		// create new pin in Bus
		Pin *myPin = new Pin;
		// pass the parameters of this Pin to the Bus(list)
		myPin->port = port;
		myPin->mask = pinMask;
		// let the pointer-tail show to the next free spot for the Pin
		myPin->next = m_pins;
		m_pins = myPin;
	} else {
		cerr << " Der Pin ist schon belegt. " << endl;
	}

	// returning the object for easy chaining
	return *this;
}

CGpioBus& CGpioBus::write(uint16_t value) {
	// Set the pins of the bus according to the given value
	for (Pin *myPin = m_pins; myPin != nullptr; myPin = myPin->next) {
		if (value & 0x1) {
			// least sign. Bit in value set,then Pin is set
			HAL_GPIO_WritePin(myPin->port, myPin->mask, GPIO_PIN_SET);
		} else {
			// respective Bit in value is not set, then reset Pin
			HAL_GPIO_WritePin(myPin->port, myPin->mask, GPIO_PIN_RESET);
		}
		// move to the next least significant bit in
		// the next iteration
		value >>= 1;
	}
	return *this;
}

CGpioBus& CGpioBus::operator =(uint16_t value) {
	// uses the Function write to delegate a Pin
	return write(value);
}

uint16_t CGpioBus::read() const {
	// return variable
	uint16_t value = 0;
	for (Pin *myPin = m_pins; myPin != nullptr; myPin = myPin->next) {
		if (HAL_GPIO_ReadPin(myPin->port, myPin->mask) == GPIO_PIN_SET) {
			// set the correponding Bit in value when Pin is set
			value |= 0x1;
		}
		// shifts the next bit so as to set the next MSB
		// in the next iteration

		value <<= 1;

	}
	// discard added 0 to the  value
	if(m_pins != nullptr){
		value >>= 1;
	}

	// return the value of the Bit contained in the Pin
	return value;
}

CGpioBus::operator uint16_t() const {
	// overload operator for read
	return read();
}
