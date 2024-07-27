/*
 * CSensorDataDisplay.h
 *
 *  Created on: 18.06.2023
 *      Author: Kuete Konwo
 */

#ifndef SRC_CSENSORDATADISPLAY_H_
#define SRC_CSENSORDATADISPLAY_H_

#include "CBmp280Device.h"
#include "CBmp280I2cDriver.h"
#include "CBmp280SpiDriver.h"
#include "CLcd1602.h"
#include <string.h>
#include "i2c.h"
#include "spi.h"

class CSensorDataDisplay {
public:
	inline void run();
};

extern "C" void runSensorDataDisplay(){
	CSensorDataDisplay().run();
}
#endif /* SRC_CSENSORDATADISPLAY_H_ */
