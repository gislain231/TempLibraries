/*
 * CBmp280I2cDriver.cpp
 *
 *  Created on: Jun 13, 2023
 *      Author: sonpa
 */

#include "CBmp280I2cDriver.h"

CBmp280I2cDriver::CBmp280I2cDriver(I2C_HandleTypeDef *hi2c,
		uint8_t deviceAddress) {
	m_hi2c = hi2c;
	m_deviceAddress = deviceAddress;
}

bool CBmp280I2cDriver::readRegisters(uint8_t startAddress, uint8_t *data,
		uint8_t bytes) {
	// Deklaration eines lokalen Variablen
	HAL_StatusTypeDef ret = HAL_OK;

	// Read cycle on the i2c line
	ret = HAL_I2C_Master_Transmit(m_hi2c, m_deviceAddress << 1, &startAddress,
			1, HAL_MAX_DELAY);

	if (ret != HAL_OK) {
		// Transmission encoutered a Problem
		return false;
	}

	ret = HAL_I2C_Master_Receive(m_hi2c, m_deviceAddress << 1, data, bytes,
	HAL_MAX_DELAY);
	if (ret != HAL_OK) {
		// Receive encoutered a Problem
		return false;
	}
	return true;
}

bool CBmp280I2cDriver::writeRegister(uint8_t address, uint8_t data) {
	// Deklaration of local HAL Variable
	HAL_StatusTypeDef ret = HAL_OK;
	// prepare data to send
	uint8_t buffer[2] = { address, data };
	uint16_t size =2;

	// write cycle on the i2c line
	ret = HAL_I2C_Master_Transmit(m_hi2c, m_deviceAddress << 1, buffer, size,
			HAL_MAX_DELAY);
	if (ret != HAL_OK) {
		// Transmission encoutered a Problem
		return false;
	}

	return true;

}
