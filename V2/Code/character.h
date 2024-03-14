#ifndef __character_H 
#define __character_H


//EXTRA POINT 1
void startConfiguration(void);
void printCharacter(void);
void mealStringColor(int color);
void snackStringColor(int color);
void printCharacterJump(int jumpDir);
void increaseHappinessLevel(void);
void decreaseHappinessLevel(void);
void increaseSatietyLevel(void);
void decreaseSatietyLevel(void);
void age(void);
void eatMeal(void);
void eatSnack(void);
void diedCharacter(void);
void clearDiedCharacter(void);

//EXTRA POINT 2
void printCuddles(int color);
void deleteCuddles(void);
void moveCuddles(int xMove, int yMove);
void printSpeaker(void);
void increaseLevelSpeaker(void);
void deleteLevelSpeaker(void);
#endif 
