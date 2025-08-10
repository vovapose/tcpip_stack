#ifndef INPUTVALIDATION_H
#define INPUTVALIDATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int isStrOnlyLetters(char* ch);
char* isStrInputCorrect(unsigned int strLen);
int isIntInputCorrect(int floorInt, int ceilInt);
#endif // INPUTVALIDATION_H