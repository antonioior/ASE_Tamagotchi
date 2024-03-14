#ifndef __printLCDShape_H 
#define __printLCDShape_H

#include "GLCD/GLCD.h" 


//EXTRA POINT 1
void printCircleEmpty(int xC, int yC, int r, int angleStart, int angleStop, uint16_t color);
void printRoundCrown(int xC, int yC, int rMax, int rMin, int angleStart, int angleStop, uint16_t color);
void printCircleFull(int xC, int yC, int r, int angleStart, int angleStop, uint16_t color);
void printRectangularEmpty(int x, int y, int dimO, int dimV, uint16_t color);
void printRectangularFull(int x, int y, int dimO, int dimV, uint16_t color);
void printTriangleRectangularEmpty(int x, int y, int base, int height, uint16_t color);
void printTriangleRectangularFull(int x, int y, int base, int height, uint16_t color);
void deleteCircleFull(int xC,int yC,int r,int angleStart, int angleStop);
void deleteRoundCrown(int xC, int yC, int rMax, int rMin, int angleStart, int angleStop);
void deleteRectangularEmpty(int x, int y, int dimO, int dimV);
void deleteRectangularFull(int x, int y, int dimO, int dimV);
void deleteTriangleRectangularEmpty(int x, int y, int base, int height);
void deleteTriangleRectangularFull(int x, int y, int base, int height);

//EXTRA POINT 2
void printHeart(int x, int y, uint16_t color);
void deleteHeart(int x, int y); 
#endif 
