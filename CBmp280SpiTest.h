/*
 * CBmp280SpiTest.h
 *
 *  Created on: Jun 11, 2023
 *      Author: Kuete Konwo
 */

#ifndef SRC_CBMP280SPITEST_H_
#define SRC_CBMP280SPITEST_H_

#include <iostream>
#include <string.h>
#include "spi.h"
#include "usart.h"
#include "CGpioPin.h"
#include "CBmp280SpiDriver.h"

/** Models a simple Class for Transmission with SPI
 */
class CBmp280SpiTest {
public:
	inline void run();
};

extern "C" void runBmp280SpiTest(){
	CBmp280SpiTest().run();
}
#endif /* SRC_CBMP280SPITEST_H_ */
