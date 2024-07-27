/*
 * CBmp280I2cDriver.h
 *
 *  Created on: Jun 13, 2023
 *      Author: Kuete Konwo
 */

#ifndef SRC_CBMP280I2CDRIVER_H_
#define SRC_CBMP280I2CDRIVER_H_

#include "CBmp280LowLevelDriver.h"
#include "CGpioPin.h"
#include <string.h>

/** Models a Sub-Class for an I2C Driver-Interface */

class CBmp280I2cDriver: public CBmp280LowLevelDriver {
private:
	I2C_HandleTypeDef *m_hi2c;
	uint8_t m_deviceAddress;
public:
	/** Creates a SPI-Driver to handle Data Exchange
	 *
	 * @param hspi Spi Handler
	 * @param deviceAddress Address of the I2C Registers
	 */
	CBmp280I2cDriver(I2C_HandleTypeDef *hi2c, uint8_t deviceAddress);

	/*
	 * Reads one or more Registers when data has been send across
	 * the I2C. Returns true, if Register was read else false.
	 *
	 * @param startAddress start of Register's Address
	 * @param data Data to be read
	 * @param bytes amount of Data to be sent
	 */
	bool readRegisters(uint8_t startAddress, uint8_t *data, uint8_t bytes);

	/*
	 * Writes Data  to one or more Registers as a pair when data has
	 * been sent across the I2C. Returns true, if Register
	 * was written else false.
	 *
	 * @param address Register's Address
	 * @param data Data to be written
	 *
	 */
	bool writeRegister(uint8_t address, uint8_t data);
};

#endif /* SRC_CBMP280I2CDRIVER_H_ */
