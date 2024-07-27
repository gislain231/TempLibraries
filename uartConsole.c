#include "usart.h"
#include "string.h"
#include "stm32f4xx_hal.h"

/*
 * This Function redirects data from the iostream to the Console
 */
int _write(int file, char *ptr, int len) {
	(void) file;
//	 Polling Mode
//	HAL_UART_Transmit(&huart2, (uint8_t*) ptr, len, 100);

	// Buffer for 100 local static characters
	static char buf[100];
	// control variable to ensure data(length) coherence
	int dataLen = 100;

	// actual length extraction
	if (len < dataLen) {
		dataLen = len;
	}
	// Wait till the UART is ready for transmission and previous
	// operation is finished
	while (HAL_UART_GetState(&huart2) != HAL_UART_STATE_READY) {
	}
	// copy all the data from the p_counter to the buffer
	memcpy(buf, ptr, dataLen);
	// Send Data to the Terminal
	HAL_UART_Transmit_DMA(&huart2, (uint8_t*) buf, dataLen);

	return dataLen;
}

/*
 * This Function reads data from the console
 */
int _read(int file, char *ptr, int len) {
	// Wait for an input character
	HAL_UART_Receive(&huart2, (uint8_t*) ptr, 1, HAL_MAX_DELAY);

	// Map return to newlin which expected as line termination by caller
	if (*ptr == '\r') {
		*ptr = '\n';
	}
	// Echo received character, newline (special case) as CR/NL.
	if (*ptr == '\n') {
		_write(1, "\r\n", 2);
	} else {
		_write(1, ptr, 1);
	}
	// One character has been received.
	return 1;

}
