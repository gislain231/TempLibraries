/*
 * CBmp280SPITest.cpp
 *
 *  Created on: Jun 11, 2023
 *      Author: Kuete Konwo
 */

#include "CBmp280SpiTest.h"

inline void CBmp280SpiTest::run() {
	CGpioPin csb(GPIOB, 1 << 12);
	// Nummer des Id-Registers im Speicher bereitstellen
	uint8_t idReg = 0xd0;
	CBmp280SpiDriver bmpSpi(&hspi2,&csb);
	// Ein Byte(Puffer) für den Empfang des Ergebnisses bereitstellen
	uint8_t id = 0;

		// Chip selektieren, Byte senden, Byte empfangen, deselektieren.

//		bmpSpi.writeRegister(idReg, 1);
		bmpSpi.readRegisters(idReg, &id, 1);
//		HAL_SPI_Transmit(&hspi2, &idReg, 1, HAL_MAX_DELAY);
//		HAL_SPI_Receive(&hspi2, &id, 1, HAL_MAX_DELAY);

		std::cout << "SPI-ID: " << int(id) << "\r\n";


//	// Puffer für Sende- (MOSI) und Empfangsdaten (MISO) bereitstellen.
//	uint8_t out[2] = { 0xd0, 0 };
//	uint8_t in[2] = { 0, 0 };
//
//	// Chip selektieren, zwei Bytes senden und empfangen
//	csb=0;
//	HAL_SPI_TransmitReceive(&hspi2,out ,in,2,HAL_MAX_DELAY);
//	csb=1;

}
