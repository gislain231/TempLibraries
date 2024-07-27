/*
 * CBmp280I2cTest.h
 *
 *  Created on: May 31, 2023
 *      Author: Kuete Konwo
 */

#ifndef SRC_CBMP280I2CTEST_H_
#define SRC_CBMP280I2CTEST_H_

#include <iostream>
#include <string.h>
#include "i2c.h"
#include "usart.h"
#include "CGpioPin.h"
#include "CBmp280I2cDriver.h"

/**Models a simple Class for Transmission with I2C*/

class CBmp280I2cTest {
public:
	inline void run();
};

extern "C" void runBmp280I2cTest() {
	CBmp280I2cTest().run();
}
#endif /* SRC_CBMP280I2CTEST_H_ */
