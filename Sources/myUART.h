/*
 * myUART.h
 *
 *  Created on: Oct 17, 2019
 *      Author: Michael
 */

#ifndef SOURCES_APPLICATION_H_
#define SOURCES_APPLICATION_H_

#include "PE_Types.h"
#include "PE_LDD.h"

typedef struct {
  LDD_TDeviceData *handle; /* LDD device handle */
  volatile uint8_t isSent; /* this will be set to 1 once the block has been sent */
  uint8_t rxChar; /* single character buffer for receiving chars */
  uint8_t (*rxPutFct)(uint8_t); /* callback to put received character into buffer */
} UART_Desc;

extern UART_Desc deviceData;
extern bool g_RxFlag;

void APP_Run(void);
void control_LEDs (bool R, bool G, bool B);
void SendChar(unsigned char ch, UART_Desc *desc);
void SendString(const unsigned char *str,  UART_Desc *desc);
void Serial_Init(void);

#endif /* SOURCES_APPLICATION_H_ */
