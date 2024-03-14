/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../character.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile char selected = '0';
extern int happinessLevel;
extern int satietyLevel;


void RIT_IRQHandler (void){
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){//	PREMUTO QUANDO JOYSTICK DOWN
		switch(selected){
			case 'L':{
				disable_RIT();
				eatMeal();
				if(satietyLevel < 6){ 
					increaseSatietyLevel();
					satietyLevel++;
				}
				enable_RIT();
				break;
			}
			case 'R':{
				disable_RIT();
				eatSnack();
				if(happinessLevel < 6){
					increaseHappinessLevel();
					happinessLevel++;
				}
				enable_RIT();
				break;
			}
			case 'D':{
				clearDiedCharacter();
				startConfiguration();
				break;
			}
			default: break;
		}
	}
	else if((LPC_GPIO1->FIOPIN & (1<<27)) == 0 && selected != 'D'){ //JOYSTICK A SINISTRA
		selected = 'L';
		snackStringColor(0x0000); //color Black
		mealStringColor(0xF800);	//color Red							
	}
	else if((LPC_GPIO1->FIOPIN & (1<<28)) == 0 && selected != 'D'){ //JOYSTICK A DESTRA
		selected = 'R';
		mealStringColor(0x0000);								
		snackStringColor(0xF800); 
	}
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
