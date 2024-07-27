/*
 * CBmp280Device.h
 *
 *  Created on: Jun 13, 2023
 *      Author: Kuete Konwo
 */

#ifndef SRC_CBMP280DEVICE_H_
#define SRC_CBMP280DEVICE_H_

#include "CBmp280LowLevelDriver.h"

enum OperatingMode {
	HighResolution,
	LowPower,
	StandardResolution,
	UltraHighresolution,
	UltraLowPower,
	Unintialized
};

enum StandbyTime {
	SBT_0_5, SBT_1000, SBT_125, SBT_2000, SBT_250,
	SBT_4000, SBT_500, SBT_62_5
};

class CBmp280Device {
private:
	CBmp280LowLevelDriver *m_driver;
	uint16_t m_dig_T1;
	int16_t m_dig_T2;
	int16_t m_dig_T3;
	uint16_t m_dig_P1;
	int16_t m_dig_P2;
	int16_t m_dig_P3;
	int16_t m_dig_P4;
	int16_t m_dig_P5;
	int16_t m_dig_P6;
	int16_t m_dig_P7;
	int16_t m_dig_P8;
	int16_t m_dig_P9;
	int32_t m_t_fine;
public:
	CBmp280Device(CBmp280LowLevelDriver *driver);
	float getPressure();
	float getTemperature();
	void getAll(float &pressure, float &temperature);
	void setMode(OperatingMode mode, StandbyTime sbt);
};

#endif /* SRC_CBMP280DEVICE_H_ */
