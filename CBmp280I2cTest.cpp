/*
 * CBmp280I2cTest.cpp
 *
 *  Created on: May 31, 2023
 *      Author: Kuete Konwo
 */

#include "CBmp280I2cTest.h"

void CBmp280I2cTest::run() {

	const uint16_t bmp280Addr = 0b1110110;
	uint8_t idReg = 0xd0;
	uint8_t id = 0;
	CGpioPin led_0(GPIOC, 1 << 0);
	CBmp280I2cDriver bmp280(&hi2c1,bmp280Addr);

	led_0 = 1;
//		HAL_I2C_Master_Transmit(&hi2c1, bmp280Addr << 1, &idReg, 1,
//				HAL_MAX_DELAY);
//		HAL_I2C_Master_Receive(&hi2c1, bmp280Addr << 1, &id, 1, HAL_MAX_DELAY);
	bmp280.readRegisters(idReg, &id, 1);

// Eine Transaktion() mit Frame Sequence
//	HAL_I2C_Master_Seq_Transmit_DMA(&hi2c1, bmp280Addr << 1, &idReg, 1,
//	I2C_FIRST_FRAME);
//	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) {
//	}
//	HAL_I2C_Master_Seq_Receive_DMA(&hi2c1, bmp280Addr << 1, &id, 1,
//			I2C_LAST_FRAME);
//	while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) {
//	}
//	led_0 = 0;
	std::cout << "ID: "<< std::hex << int(id) << "\r\n";

}
