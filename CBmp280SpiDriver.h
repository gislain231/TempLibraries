/*
 * CBmp280SpiDriver.h
 *
 *  Created on: Jun 13, 2023
 *      Author: Kuete Konwo
 */

#ifndef SRC_CBMP280SPIDRIVER_H_
#define SRC_CBMP280SPIDRIVER_H_
#include "CGpioPin.h"
#include "CBmp280LowLevelDriver.h"

/** Models a Sub-Class for an SPI Driver-Interface */

class CBmp280SpiDriver: public CBmp280LowLevelDriver {
private:
	CGpioPin *m_ss;
	SPI_HandleTypeDef *m_hspi;
public:
	/** Creates a SPI-Driver to handle Data Exchange
	 *
	 * @param hspi Spi Handler
	 * @param ss slave select pointer
	 */
	CBmp280SpiDriver(SPI_HandleTypeDef *hspi, CGpioPin *ss);

	/*
	 * Reads one or more Registers when data has been send across
	 * the SPI. Returns true, if Register was read else false.
	 *
	 * @param startAddress start of Register's Address
	 * @param data Data to be read
	 * @param bytes amount of Data sent
	 */
	bool readRegisters(uint8_t startAddress, uint8_t *data, uint8_t bytes);

	/*
	 * Writes Data  to one or more Registers as a pair when data has
	 * been sent across the SPI. Returns true, if Register
	 * was written else false.
	 *
	 * @param address start of Register's Address
	 * @param data Data to be written
	 *
	 */
	bool writeRegister(uint8_t address, uint8_t data);
};

#endif /* SRC_CBMP280SPIDRIVER_H_ */
