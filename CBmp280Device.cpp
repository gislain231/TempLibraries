/*
 * CBmp280Device.cpp
 *
 *  Created on: Jun 13, 2023
 *      Author: Kuete Konwo
 */

#include "CBmp280Device.h"

CBmp280Device::CBmp280Device(CBmp280LowLevelDriver *driver) {
	// init. selected Driver
	m_driver = driver;

	uint8_t dataBuffer[24];
	for (int i = 0; i < 24; i++) {
		dataBuffer[i] = 0;
	}
	// init. of fine resolution temp. value
	m_t_fine = 0;
	// read the trimming values and store them in ROM(NVM)
	m_driver->readRegisters(0x88, dataBuffer, 24);
	m_dig_T1 = (dataBuffer[1] << 8) | dataBuffer[0];
	m_dig_T2 = (dataBuffer[3] << 8) | dataBuffer[2];
	m_dig_T3 = (dataBuffer[5] << 8) | dataBuffer[4];
	m_dig_P1 = (dataBuffer[7] << 8) | dataBuffer[6];
	m_dig_P2 = (dataBuffer[9] << 8) | dataBuffer[8];
	m_dig_P3 = (dataBuffer[11] << 8) | dataBuffer[10];
	m_dig_P4 = (dataBuffer[13] << 8) | dataBuffer[12];
	m_dig_P5 = (dataBuffer[15] << 8) | dataBuffer[14];
	m_dig_P6 = (dataBuffer[17] << 8) | dataBuffer[16];
	m_dig_P7 = (dataBuffer[19] << 8) | dataBuffer[18];
	m_dig_P8 = (dataBuffer[21] << 8) | dataBuffer[20];
	m_dig_P9 = (dataBuffer[23] << 8) | dataBuffer[22];

}

float CBmp280Device::getPressure() {
	float temperature, pressure;
	getAll(pressure, temperature);

	return pressure;
}

float CBmp280Device::getTemperature() {
	float temperature, pressure;
	getAll(pressure, temperature);

	return temperature;
}

void CBmp280Device::getAll(float &pressure, float &temperature) {
	// variables to store value for temperature and Pressure
	int32_t var1, var2, T;

	// buffer to retrieve temp. & Pressure from Raw data
	uint8_t buffer[6] = { 0, 0, 0, 0, 0, 0 };

	// variable to store raw data from the device
	int32_t adc_T = 0, adc_P = 0;

	// read raw data from the BMP280
	m_driver->readRegisters(0xf7, buffer, 6);

	// store the raw temperature data
	adc_P = (buffer[0] << 12) | (buffer[1] << 4) | (buffer[2] >> 4);
	adc_T = ((buffer[3] << 16) | (buffer[4] << 8) | buffer[5]) >> 4;

	var1 = ((((adc_T >> 3) - ((int32_t) m_dig_T1 << 1))) * ((int32_t) m_dig_T2))
			>> 11;
	var2 = (((((adc_T >> 4) - ((int32_t) m_dig_T1))
			* ((adc_T >> 4) - ((int32_t) m_dig_T1))) >> 12)
			* ((int32_t) m_dig_T3)) >> 14;
	m_t_fine = var1 + var2;
	T = (m_t_fine * 5 + 128) >> 8;
	temperature = T / 100.0;

	int64_t var1P, var2P,p;
	var1P = ((int64_t) m_t_fine) - 128000;
	var2P = var1P * var1P * (int64_t) m_dig_P6;
	var2P = var2P + ((var1P * (int64_t) m_dig_P5) << 17);
	var2P = var2P + (((int64_t) m_dig_P4) << 35);
	var1P = ((var1P * var1P * (int64_t) m_dig_P3) >> 8)
			+ ((var1P * (int64_t) m_dig_P2) << 12);
	var1P = (((((int64_t) 1) << 47) + var1P)) * ((int64_t) m_dig_P1) >> 33;

	if (var1P == 0) {
		pressure = 0;
	} else {
		p = 1048576 - adc_P;
		p = (((p << 31) - var2P) * 3125) / var1P;
		var1P = (((int64_t) m_dig_P9) * (p >> 13) * (p >> 13)) >> 25;
		var2P = (((int64_t) m_dig_P8) * p) >> 19;
		p = ((p + var1P + var2P) >> 8) + (((int64_t) m_dig_P7) << 4);
		pressure = p / 25600.0;

	}
}

void CBmp280Device::setMode(OperatingMode mode, StandbyTime sbt) {
	// Sets the address for different Addresses
	uint8_t config = 0xf5;
	uint8_t ctrl_measReg = 0xf4;

	// declaration of ctrl parameters for Pressure,mode and temperature
	uint8_t osrs_t = 0;
	uint8_t osrs_p = 0;
	uint8_t ctrl_mode = 0;
	uint8_t resetReg = 0xe0;

	// reset device
	m_driver->writeRegister(resetReg, 0xb6);

	// set Modes according to datasheet
	switch (mode) {
	case HighResolution:
		ctrl_mode = 0x3;
		osrs_t = 0x1;
		osrs_p = 0x1;
		break;
	case LowPower:
		ctrl_mode = 0x3;
		osrs_t = 0x1;
		osrs_p = 0x2;
		break;
	case StandardResolution:
		ctrl_mode = 0x3;
		osrs_t = 0x1;
		osrs_p = 0x3;

		break;
	case UltraHighresolution:
		ctrl_mode = 0x3;
		osrs_t = 0x2;
		osrs_p = 0x7;
		break;
	case UltraLowPower:
		ctrl_mode = 0x1;
		osrs_t = 0x1;
		osrs_p = 0x1;
		break;
	case Unintialized:
		ctrl_mode = 0x0;
		osrs_t = 0x0;
		osrs_p = 0x0;
		break;
	default:
		break;
	}
	// write the standby time and IIR filter coeff to 0xf5(control Register)
	uint8_t dataToWrite;
	m_driver->readRegisters(ctrl_measReg, &dataToWrite, 1);
	m_driver->writeRegister(config,
			(((uint8_t) sbt) << 5) | (dataToWrite & 0x1f));

	// configurate pressure and temperature oversampling along
	// with the Mode to address 0xf4(according to the giving Mode)
	m_driver->writeRegister(ctrl_measReg,
			(osrs_t << 5) | (osrs_p << 2) | ctrl_mode);

}
