/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../character.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


int valueJump = 0;
volatile int fiveSHappiness = 0;
volatile int fiveSSatiety = 0;
volatile int happinessLevel = 6;
volatile int satietyLevel = 6;
volatile int ageS = 0;

void TIMER0_IRQHandler (void)
{
	disable_timer(0);
	ageS++;
	age();
	fiveSHappiness++;
	fiveSSatiety++;
	if(fiveSHappiness >= 5){
		happinessLevel--;
		decreaseHappinessLevel();
		fiveSHappiness = 0;
	}
	if(fiveSSatiety >= 5){
		satietyLevel--;
		decreaseSatietyLevel();
		fiveSSatiety = 0;
	}
	if(happinessLevel == 0 || satietyLevel == 0){
			diedCharacter();
			LPC_TIM0->IR = 1;			/* clear interrupt flag */
			return;
		}
	if(valueJump == 0){
		printCharacterJump(-20);
		valueJump = 1;
	}
	else {
		printCharacterJump(0);
		valueJump = 0;
	}
	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
	enable_timer(0);
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
