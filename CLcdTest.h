/*
 * CLcdTest.h
 *
 *  Created on: May 3, 2023
 *      Author: Kuete Konwo
 */

#ifndef SRC_CLCDTEST_H_
#define SRC_CLCDTEST_H_

#include "CLcd1602.h"




/**
 * Helping Class for the Creation of an LCD screen
 */
class CLcdTest {
public:
	/**Creation of an LCD object to write data on the screen*/
	void run();
};

/**
 * Function to ensure communication between C functions in
 * other parts of the Programm
 */
extern "C" void runLcdTest(){
	CLcdTest().run();
}




#endif /* SRC_CLCDTEST_H_ */
