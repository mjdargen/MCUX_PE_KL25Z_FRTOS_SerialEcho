/*
 * myUART.c
 *
 *  Created on: Oct 17, 2019
 *      Author: Michael
 */

#include "myUART.h"

/* initialize OpenSDA UART port */
void Serial_Init(void) {
  /* initialize struct fields */
  deviceData.handle = AS1_Init(&deviceData);
  deviceData.isSent = FALSE;
  deviceData.rxChar = '\0';
  deviceData.rxPutFct = RxBuf_Put;
  /* set up to receive RX into input buffer */
  RxBuf_Init(); /* initialize RX buffer */
  /* Set up ReceiveBlock() with a single byte buffer. We will be called in OnBlockReceived() event. */
  while(AS1_ReceiveBlock(deviceData.handle, (LDD_TData *)&deviceData.rxChar, sizeof(deviceData.rxChar))!=ERR_OK) {} /* initial kick off for receiving data */
}

/* send char out serial port */
void SendChar(unsigned char ch, UART_Desc *desc) {
  desc->isSent = FALSE;  /* this will be set to 1 once the block has been sent */
  while(AS1_SendBlock(desc->handle, (LDD_TData*)&ch, 1)!=ERR_OK) {} /* Send char */
  while(!desc->isSent) {} /* wait until we get the green flag from the TX interrupt */
}

/* send string out serial port */
void SendString(const unsigned char *str,  UART_Desc *desc) {
  while(*str!='\0') {
    SendChar(*str++, desc);
  }
}

/* control onboard RGB LED */
void control_LEDs (bool R, bool G, bool B) {
	if (R) LEDR_On();
	else LEDR_Off();
	if (G) LEDG_On();
	else LEDG_Off();
	if (B) LEDB_On();
	else LEDB_Off();
}
