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
#include "../TouchPanel/TouchPanel.h"
#include "../ADC/adc.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


//EXTA POINT 1
int valueJump = 0;
volatile int fiveSHappiness = 0;
volatile int fiveSSatiety = 0;
volatile int happinessLevel = 6;
volatile int satietyLevel = 6;
volatile int ageS = 0;


//EXTRA POINT 2
volatile int cuddlesPrinted = 0, cuddlesTime = 0;
extern char numberNote;
volatile int levelSound = 12;
int note3=0, note5=0, note8 = 0;
const int freqSound = 2120;
const int vetTre[3]={2120,1890,1684};
const int vetCin[5]={1592,1417,1263,1125,1062};
const int vetOtt[8]={2120,1890,1684,1592,1417,1263,1125,1062};
uint16_t SinTable[45] =                                     
{
    410, 467, 523, 576, 627, 673, 714, 749, 778,
    799, 813, 819, 817, 807, 789, 764, 732, 694, 
    650, 602, 550, 495, 438, 381, 324, 270, 217,
    169, 125, 87 , 55 , 30 , 12 , 2  , 0  , 6  ,   
    20 , 41 , 70 , 105, 146, 193, 243, 297, 353
};

void TIMER0_IRQHandler (void)
{
	//EXTRA POINT 1
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
	
	//EXTRA POINT 2
	if(cuddlesPrinted){
		cuddlesTime++;
		if(cuddlesTime == 1)
			moveCuddles(10, -30);
		else{
			deleteCuddles();
			cuddlesPrinted = 0;
			cuddlesTime = 0;
			if(happinessLevel < 6){
				increaseHappinessLevel();
				happinessLevel++;
			}
		}
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
	static int ticks=0;
	LPC_DAC->DACR = (SinTable[ticks]<<4)*levelSound;
	ticks++;
	if(ticks==45)
		ticks=0;	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER2_IRQHandler (void){
	switch(numberNote){
		case '1': {
			disable_timer(1);
			reset_timer(1);
			init_timer(1,0,0,3, freqSound);
			enable_timer(1);
			numberNote = '0';
			break;
		}
		
		case '2':{
			disable_timer(1);
			reset_timer(1);
			init_timer(1,0,0,3, vetTre[note3]);
			enable_timer(1);
			if(note3 == 3){
				note3 = 0; 
				numberNote = '0';
			}
			else
				note3++;
			break;
		}
		
		case '3':{
			disable_timer(1);
			reset_timer(1);
			init_timer(1,0,0,3, vetCin[note5]);
			enable_timer(1);
			if(note5 == 5){
				note5 = 0; 
				numberNote = '0';
			}
			else
				note5++;
			break;
		}
		
		case '4': {
			disable_timer(1);
			reset_timer(1);
			init_timer(1,0,0,3, vetOtt[note8]);
			enable_timer(1);
			if(note8 == 8){
				note8 = 0; 
				numberNote = '0';
			}
			else
				note8++;
			break;
		}
		
		default: {
			disable_timer(1);
			break;
		}
	}
	LPC_TIM2->IR = 1;			/* clear interrupt flag */
	return;
	
}

void TIMER3_IRQHandler (void){	
	LPC_TIM3->IR = 1;			/* clear interrupt flag */
	return;
}



/******************************************************************************
**                            End Of File
******************************************************************************/
