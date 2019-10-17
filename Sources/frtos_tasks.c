
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/

/* Begin of <includes> initialization, DO NOT MODIFY LINES BELOW */

#include "TSK1.h"
#include "FRTOS1.h"
#include "frtos_tasks.h"

/* End <includes> initialization, DO NOT MODIFY LINES ABOVE */
#include "myUART.h"
#include "RxBuf.h"
#include "AS1.h"
#include "LEDR.h"
#include "LEDpin1.h"
#include "BitIoLdd1.h"
#include "LEDG.h"
#include "LEDpin2.h"
#include "BitIoLdd2.h"
#include "LEDB.h"
#include "LEDpin3.h"
#include "BitIoLdd3.h"

UART_Desc deviceData;
bool g_RxFlag = 0;

/* FRTOS Task for serial port echo */
static portTASK_FUNCTION(EchoTask, pvParameters) {

  /* Write your task initialization code here ... */

	// initialize serial port and send announcement
	Serial_Init();
	SendString((unsigned char*)"Hello World\r\n", &deviceData);

  for(;;) {
    /* Write your task code here ... */

  	// if the buffer is not empty and the flag has been set
  	// flag set when serial port receives carriage return
  	if ((RxBuf_NofElements()!=0) && g_RxFlag) {
			SendString((unsigned char*)"echo: ", &deviceData);
			while (RxBuf_NofElements()!=0) {
				unsigned char ch;
				(void)RxBuf_Get(&ch);
				SendChar(ch, &deviceData);
			}
			SendString((unsigned char*)"\r\n", &deviceData);
			g_RxFlag = 0; // reset flag
  	}

  	vTaskDelay(10/portTICK_RATE_MS);
  }
  /* Destroy the task */
  vTaskDelete(EchoTask);
}

/* toggle RGB state task */
static portTASK_FUNCTION(RGBTask, pvParameters) {

  /* Write your task initialization code here ... */

  for(;;) {
    /* Write your task code here ... */

  	for (char i=0; i<8; i++) {
  		control_LEDs(i&4,i&2,i&1);
  		vTaskDelay(500/portTICK_RATE_MS);
  	}
  }
  /* Destroy the task */
  vTaskDelete(RGBTask);
}

void CreateTasks(void) {
  if (FRTOS1_xTaskCreate(
     EchoTask,  /* pointer to the task */
      "Echo", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE + 0, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY + 0,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
  }
  if (FRTOS1_xTaskCreate(
     RGBTask,  /* pointer to the task */
      "RGB", /* task name for kernel awareness debugging */
      configMINIMAL_STACK_SIZE + 0, /* task stack size */
      (void*)NULL, /* optional task startup argument */
      tskIDLE_PRIORITY + 0,  /* initial priority */
      (xTaskHandle*)NULL /* optional task handle to create */
    ) != pdPASS) {
      /*lint -e527 */
      for(;;){}; /* error! probably out of memory */
      /*lint +e527 */
  }
}
