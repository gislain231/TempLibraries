/*
 * CBmp280SpiDriver.cpp
 *
 *  Created on: Jun 13, 2023
 *      Author: Kuete Konwo
 */

#include "CBmp280SpiDriver.h"

CBmp280SpiDriver::CBmp280SpiDriver(SPI_HandleTypeDef *hspi, CGpioPin *ss) {
	// init. of all Attributes
	m_hspi = hspi;
	m_ss = ss;
}

bool CBmp280SpiDriver::readRegisters(uint8_t startAddress, uint8_t *data,
		uint8_t bytes) {
	HAL_StatusTypeDef ret = HAL_OK;
	// prepare data to receive
	startAddress |= 0x80;

	*m_ss = 0;
	// Read cycle on the i2c line
	ret = HAL_SPI_Transmit(m_hspi, &startAddress, 1, HAL_MAX_DELAY);

	if (ret != HAL_OK) {
		// Transmission encoutered a Problem
		return false;
	}

	ret = HAL_SPI_Receive(m_hspi, data, bytes, HAL_MAX_DELAY);
	if (ret != HAL_OK) {
		// Receive encoutered a Problem
		return false;
	}
	*m_ss = 1;

	return true;
}

bool CBmp280SpiDriver::writeRegister(uint8_t address, uint8_t data) {
	HAL_StatusTypeDef ret = HAL_OK;
	address &= 0x7f;
	// prepare data to receive
	uint8_t buffer[2] = { address, data };

	uint16_t size = 2;

	// Read cycle on the i2c line
	ret = HAL_SPI_Transmit(m_hspi, buffer, size, HAL_MAX_DELAY);

	if (ret != HAL_OK) {
		// Transmission encoutered a Problem
		return false;
	}

	return true;
}
