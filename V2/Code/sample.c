/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "timer/timer.h"
#include "printLCDShape.h"
#include "character.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"
#include "touchPanel/TouchPanel.h"
#include "ADC/adc.h"
#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


int main(void)
{	
	//Inizializzazione
	SystemInit();  														/* System Initialization (i.e., PLL)  */
  LCD_Initialization();
	TP_Init();
	TouchPanel_Calibrate();
	ADC_init();
	joystick_init();
	LCD_Clear(White);
	
	//EXTRA POINT 1
	startConfiguration();
	init_timer(0, 0, 0, 3, 25000000); 						//1s = 1 * 25*10^6		
	init_RIT(0x004C4B40);	
	enable_timer(0);
	enable_RIT();
	
	//EXTRA POINT 2
	init_timer(2, 0, 0, 3, 12500000);
	enable_timer(2);
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
	//speaker
	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);

  while (1)	
  {
		//__ASM("wfi");
  }
}

/*********************************************************************************************************
      END MAIN
*********************************************************************************************************/
