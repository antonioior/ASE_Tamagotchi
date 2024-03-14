#include <math.h>
#include "printLCDShape.h"
#include "GLCD/GLCD.h" 

extern int eat;

//EXTRA POINT 1
void printCircleEmpty(int xC, int yC, int r, int angleStart, int angleStop, uint16_t color){
	int x, y, teta, i;
	float pi = 3.1416;
	if(angleStart == angleStop-360){
		for(teta=angleStart+1; teta<angleStop/2; teta++){
			y = (int) r*sin(teta * pi /180);
			x = (int) r*cos(teta * pi /180);
			LCD_SetPoint(xC+x,yC-y, color);
			LCD_SetPoint(xC+x,yC+y, color);
		}
	}
	else {
		for(teta=angleStart+1; teta<angleStop; teta++){
			y = (int) r*sin(teta * pi /180);
			x = (int) r*cos(teta * pi /180);
			LCD_SetPoint(xC+x,yC-y,color);
		}
	}
	if(angleStart != angleStop-360 && eat!=0){
		for(i=0; i<r; i++){
			LCD_SetPoint(xC+i*cos(angleStart*pi/180), yC-i*sin(angleStart*pi/180), color);
			LCD_SetPoint(xC+i*cos(angleStop*pi/180), yC-i*sin(angleStop*pi/180), color);
		}
	}
	return;
}

void printRoundCrown(int xC, int yC, int rMax, int rMin, int angleStart, int angleStop, uint16_t color){
	int i;
	for(i=rMax; i>=rMin; i--)
		printCircleEmpty(xC, yC, i, angleStart, angleStop, color);
	return;
}

void printCircleFull(int xC, int yC, int r, int angleStart, int angleStop, uint16_t color){
	printRoundCrown(xC, yC, r, 0, angleStart, angleStop, color);
	return;
}

void printRectangularEmpty(int x, int y, int dimO, int dimV, uint16_t color){
	LCD_DrawLine(x, y, x+dimO,y, color);
	LCD_DrawLine(x, y+dimV, x+dimO, y+dimV, color);
	LCD_DrawLine(x,y, x, y+dimV, color);
	LCD_DrawLine(x+dimO, y, x+dimO, y+dimV, color);
	return;
}

void printRectangularFull(int x, int y, int dimO, int dimV, uint16_t color){
	int i;
	for(i=0; i<dimV; i++)
		LCD_DrawLine(x,y+i,x+dimO,y+i, color);
	return;
}

void printTriangleRectangularEmpty(int x, int y, int base, int height, uint16_t color){
	LCD_DrawLine(x, y, x, y+height, color);
	LCD_DrawLine(x, y+height, x+base, y+height, color);
	LCD_DrawLine(x, y, x+base, y+height, color);
	return;
}
void printTriangleRectangularFull(int x, int y, int base, int height, uint16_t color){
	int i=0;
	for(i = 0; i<=height; i++)
		LCD_DrawLine(x, y+i, x+base, y+height, color);
	return;
}

void deleteCircleFull(int xC,int yC,int r,int angleStart, int angleStop){
	printCircleFull(xC, yC, r, angleStart, angleStop, White);
	return;
}

void deleteRoundCrown(int xC, int yC, int rMax, int rMin, int angleStart, int angleStop){
	printRoundCrown(xC, yC, rMax, rMin, angleStart, angleStop, White);
}

void deleteRectangularEmpty(int x, int y, int dimO, int dimV){
	printRectangularEmpty(x, y, dimO, dimV, White);
	return;
}
void deleteRectangularFull(int x, int y, int dimO, int dimV){
	printRectangularFull(x, y, dimO, dimV, White);
	return;
}

void deleteTriangleRectangularEmpty(int x, int y, int base, int height){
	printTriangleRectangularEmpty(x,y,base, height, White);
	return;
}
void deleteTriangleRectangularFull(int x, int y, int base, int height){
	printTriangleRectangularFull(x,y, base, height, White);
	return;
}


//EXTRA POINT 2
void printHeart(int x, int y, uint16_t color){
	printRectangularFull(x, y, 5, 5, color);
	printRectangularFull(x+10, y, 5, 5, color);
	printRectangularFull(x, y+5, 15, 5, color);
	printRectangularFull(x+5, y+10, 5, 5, color);
	return;
}

void deleteHeart(int x, int y){
	printHeart(x,y, White);
	return;
}
