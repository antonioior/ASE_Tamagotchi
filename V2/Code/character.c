#include <stdio.h>
#include "character.h"
#include "printLCDShape.h"
#include "timer/timer.h"

//EXTRA POINT 1
void deleteCharacter(void);
void batteryLife(int xL, int yL, int level);

int xC = 120, xOffset=0;
int yC = 225, yOffset=0;
int rMin = 14;
uint16_t colorLife[6]= {0xF800, 0xF800, 0xFFE0, 0xFFE0, 0x07E0, 0x07E0};
int eat = 0;

extern int happinessLevel;
extern int satietyLevel;
extern int ageS;
extern char selected;
extern int fiveSHappiness;
extern int fiveSSatiety;
extern int numberNote;

//EXTRA POINT 2
int xMoveCuddles= 0, yMoveCuddles = 0, xBaseCuddles = 40, yBaseCuddles = 200;
volatile int levelSoundIcon=3;

//EXTRA POINT 1
void startConfiguration(void){
	//EXTRA POINT 1
	happinessLevel = 6;
	satietyLevel = 6;
	ageS = 0;
	eat = 0;
	fiveSHappiness = 0;
	fiveSSatiety = 0;
	mealStringColor(Black);
	snackStringColor(Black);
	printCharacter();
	age();
	GUI_Text(40, 5, (uint8_t *) "Age: ", Black, White);
	GUI_Text(20, 20, (uint8_t *) "Happiness", Black, White);
	GUI_Text(150, 20, (uint8_t *) "Satiety", Black, White);
	printRectangularEmpty(20, 40, 60, 30, Black);
	printRectangularFull(80, 50, 5, 10, Black);
	printRectangularEmpty(150, 40, 60, 30, Black);
	printRectangularFull(210, 50, 5, 10, Black);
	batteryLife(22, 42, happinessLevel);
	batteryLife(152, 42, satietyLevel);
	
	//EXTRA POINT 2
	deleteCuddles();
	printSpeaker();
	increaseLevelSpeaker();
	enable_timer(0);
	return;
}

void printCharacter(void){
	int angleStart = 0, angleStop = 360;
	if(eat == 1){						//eat snack
		angleStart = 45;
		angleStop = 360 - 45;
		printRectangularFull(xC+xOffset-7, yC+yOffset-105, 3,3, Black);
	}
	else if(eat == 2){    //eat meal
		angleStart = 180 + 45;
		angleStop = 180 - 45 + 360;
		printRectangularFull(xC+xOffset+4, yC+yOffset-105, 3, 3, Black);
	}
	else {
		printTriangleRectangularFull(xC+xOffset+ 2, yC+yOffset - 100, 20, 5, 0xE602);  				//naso
		printRoundCrown(xC+xOffset, yC+yOffset-98+2, rMin-5, rMin-6, 270-50, 270+50, Black);  //bocca
		printRectangularFull(xC+xOffset-7, yC+yOffset-105, 3,3, Black); 											//occhio sinistro
		printRectangularFull(xC+xOffset+4, yC+yOffset-105, 3, 3, Black);											//occhio destro
	}
	printRoundCrown(xC+xOffset, yC+yOffset-98, rMin+1, rMin, angleStart, angleStop, Black);
	printRectangularFull(xC+xOffset-2,yC+yOffset-59, 4, 4, Blue);
	printRoundCrown(xC+xOffset, yC+yOffset-59, rMin+1+10, rMin+10, 0, 360, Black);
	printRectangularFull(xC+xOffset-2,yC+yOffset-10, 4, 4, Blue);
	printRectangularFull(xC+xOffset-2,yC+yOffset+10, 4, 4, Blue);
	printRoundCrown(xC+xOffset, yC+yOffset, rMin+1+20, rMin+20, 0, 360, Black);
	return;
}

void mealStringColor(int color){
	LCD_DrawLine(0, 260, 120, 260, color);
	LCD_DrawLine(120, 260, 120, 320, color);
	GUI_Text(40, 280, (uint8_t *) "MEAL", color, White);
	return;
}
void snackStringColor(int color){
	LCD_DrawLine(120, 260, 240, 260, color);
	LCD_DrawLine(120, 260, 120, 320, color);
	GUI_Text(160, 280, (uint8_t *) "SNACK", color, White);
	return;
}

void batteryLife(int xL, int yL, int level){
	int i;
	for(i = 0; i<level; i++)
		printRectangularFull(xL+10*i, 42, 7, 27, colorLife[i]); 
	return;
}

void printCharacterJump(int jumpDir){
	deleteCharacter();
	yOffset = jumpDir;
	printCharacter();
	return;
}

void increaseHappinessLevel(void){
	printRectangularFull(22+10*happinessLevel, 42, 7, 27, colorLife[happinessLevel]); 
	return;
}

void decreaseHappinessLevel(void){
	printRectangularFull(22+10*happinessLevel, 42, 7, 27, White); 
	return;
}

void increaseSatietyLevel(void){
	printRectangularFull(152+10*satietyLevel, 42, 7, 27, colorLife[satietyLevel]); 
	return;
}

void decreaseSatietyLevel(void) {
	printRectangularFull(152+10*satietyLevel, 42, 7, 27, White); 
	return;
}

void age(void){
	char time[5];
	int second, minute, hour;
	second = ageS%60;
	minute = ageS/60;
	minute = minute%60;
	hour = ageS/(60*60);
	sprintf(time, "%02d:%02d:%02d", hour, minute, second);
	GUI_Text(90, 5, (uint8_t *) time, Black, White);
	return;
}



void deleteCharacter(void){
	int angleStart = 0, angleStop = 360;
	if(eat == 1){						//eat snack
		angleStart = 45;
		angleStop = 360 - 45;
		deleteRectangularFull(xC+xOffset-7, yC+yOffset-105, 3,3);
	}
	else if(eat == 2){    //eat meal
		angleStart = 180 + 45;
		angleStop = 180 - 45 + 360;
		deleteRectangularFull(xC+xOffset+4, yC+yOffset-105, 3, 3);
	}
	else{
		deleteTriangleRectangularFull(xC+xOffset+ 2, yC+yOffset - 100, 20, 5);  				//naso
		deleteRoundCrown(xC+xOffset, yC+yOffset-98+2, rMin-5, rMin-6, 270-50, 270+50); //bocca
		deleteRectangularFull(xC+xOffset-7, yC+yOffset-105, 3,3); 										//occhio sinistro
		deleteRectangularFull(xC+xOffset+4, yC+yOffset-105, 3, 3);										//occhio destro
	}
	deleteRoundCrown(xC+xOffset, yC+yOffset-98, rMin+1, rMin, angleStart, angleStop);
	deleteRectangularFull(xC+xOffset-2,yC+yOffset-59, 4, 4);
	deleteRoundCrown(xC+xOffset, yC+yOffset-59, rMin+1+10, rMin+10, 0, 360);
	deleteRectangularFull(xC+xOffset-2,yC+yOffset-10, 4, 4);
	deleteRectangularFull(xC+xOffset-2,yC+yOffset+10, 4, 4);
	deleteRoundCrown(xC+xOffset, yC+yOffset, rMin+1+20, rMin+20, 0, 360);
}

void eatMeal(void){
	int i, dimMoveLeft = 45;
	numberNote = '2';
	printRoundCrown(50,yOffset+123, 15, 13, 0, 360, 0xFF53);
	printCircleFull(50,yOffset+123, 12, 0, 360, Red);
	deleteCharacter();
	for(i = -15; i>= -1*dimMoveLeft; i-=15){
		xOffset = i;
		if (i == -1*dimMoveLeft)
			eat = 2;
		printCharacter();
		if (i != -1*dimMoveLeft)
			deleteCharacter();
	}
	deleteCircleFull(50,yOffset+123,15,0,360);
	ageS++;
	age();
	deleteCharacter();
	eat = 0;
	for(i = 15; i<= dimMoveLeft; i+=15){
		xOffset += 15;
		printCharacter();
		if(i != dimMoveLeft)
				deleteCharacter();
		}
	fiveSHappiness++;
	fiveSSatiety = 0;
	return;
}

void eatSnack(void){
	int i, dimMoveRight = 45;
	numberNote = '2';
	printRectangularEmpty(180, yOffset+112, 20, 30, Black);
	printRectangularFull(181, yOffset+113, 19, 29, 0xAC20); //Marrone
	LCD_DrawLine(180, yOffset+122, 200, yOffset+122, Black); 
	LCD_DrawLine(180, yOffset+132, 200, yOffset+132, Black);
	LCD_DrawLine(190, yOffset+112, 190, yOffset+142, Black);
	deleteCharacter();
	for(i = 15; i<= dimMoveRight; i+=15){
		xOffset = i;
		if (i == dimMoveRight)	
			eat = 1;
		printCharacter();
		if(i != dimMoveRight)
			deleteCharacter();
	}
	deleteRectangularFull(180, yOffset+112, 20, 31);
	ageS++;
	age();
	deleteCharacter();
	for(i = -15; i>= -1*dimMoveRight; i-=15){
		eat = 0;
		xOffset -= 15;
		printCharacter();
		if(i != -1*dimMoveRight)
				deleteCharacter();
		}
	fiveSSatiety++;
	fiveSHappiness = 0;
	return;
}

void diedCharacter(void){
	int i;
	numberNote = '3';
	deleteCharacter();
	for(i=0; i<=50; i++)
		LCD_SetPoint(70+i, 260-i, Black);
	for(i=0; i<=50; i++)
		LCD_SetPoint(70+50+i, 260-50+i, Black);
	printTriangleRectangularFull(xC+4, yC+20, 20, 5, 0xE602);  //arancione
	printRectangularFull(xC-20,yC+25, 4, 4, Blue);
	printRectangularFull(xC-10,yC+5, 4, 4, Blue);
	printRectangularFull(xC+30,yC+20, 4, 4, Blue);
	mealStringColor(White);
	snackStringColor(White);
	LCD_DrawLine(0, 260, 240, 260, Red);
	GUI_Text(100, 280, (uint8_t *) "RESET", Red, White);
	selected = 'D';
	return;
}

void clearDiedCharacter(void){
	int i;
	selected = '0';
	for(i=0; i<=50; i++)
		LCD_SetPoint(70+i, 260-i, White);
	for(i=0; i<=50; i++)
		LCD_SetPoint(70+50+i, 260-50+i, White);
	deleteTriangleRectangularFull(xC+4, yC+20, 20, 5);  //arancione
	deleteRectangularFull(xC-20,yC+25, 4, 4);
	deleteRectangularFull(xC-10,yC+5, 4, 4);
	deleteRectangularFull(xC+30,yC+20, 4, 4);
	LCD_DrawLine(0, 260, 240, 260, Red);
	GUI_Text(100, 280, (uint8_t *) "RESET", White, White);
	return;
}

//EXTRA POINT 2
void printCuddles(int color){
	printHeart(xBaseCuddles+xMoveCuddles, yBaseCuddles+yMoveCuddles, color);
	printHeart(xBaseCuddles+xMoveCuddles+20, yBaseCuddles+yMoveCuddles+20, color);
	return;
}

void deleteCuddles(void){
	printCuddles(White);
	xMoveCuddles= 0;
	yMoveCuddles = 0;
	return;
}

void moveCuddles(int xMove, int yMove){
	deleteCuddles();
	xMoveCuddles = xMove;
	yMoveCuddles = yMove;
	printCuddles(Red);
	return;
}

void printSpeaker(void){
	int i;
	printRectangularFull(5,11, 6, 6, Black);
	for(i = 0; i<5; i++)
		LCD_DrawLine(11+i,11-i,11+i, 17+i, Black);
	return;
}

void increaseLevelSpeaker(void){
	int i;
	for(i=0; i<levelSoundIcon; i++)
		printRectangularFull(18+6*i, 11-2*i, 3, 6+4*i, Black);
	return;
}
void deleteLevelSpeaker(void){
	deleteRectangularFull(18, 6, 15, 15);
	return;
}

