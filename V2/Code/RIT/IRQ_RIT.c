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
#include "../ADC/adc.h"
#include "../timer/timer.h"
#include "../TouchPanel/TouchPanel.h"
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/



void touchFunction(void);

//EXTRA POINT 1
volatile char selected = '0';
extern int happinessLevel;
extern int satietyLevel;

//EXTRA POINT 2
volatile char numberNote = 1;
extern int cuddlesPrinted;

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
		numberNote = '1';		
		
	}
	else if((LPC_GPIO1->FIOPIN & (1<<28)) == 0 && selected != 'D'){ //JOYSTICK A DESTRA
		selected = 'R';
		mealStringColor(0x0000);								
		snackStringColor(0xF800); 	
		numberNote = '1';
	}
	touchFunction();						//verifica se schermo toccato
	ADC_start_conversion();	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
  return;
}


//FUNCTION
void touchFunction(void){
	if(getDisplayPoint(&display, Read_Ads7846(), &matrix) && cuddlesPrinted == 0){
		if(display.x > 85 && display.x < 155 && display.y > 92 && display.y < 260){
			printCuddles(0xF800);  //red
			cuddlesPrinted = 1;
			numberNote = '4';
		}
	}
	return;
}



/******************************************************************************
**                            End Of File
******************************************************************************/

