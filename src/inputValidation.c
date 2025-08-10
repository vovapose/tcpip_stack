#include "../include//inputValidation.h"
#include "ctype.h"
#include <stdio.h>

int isStrOnlyLetters(char* ch)
{
    char* ptr ;
	ptr = strchr(ch, '\n');
    if (ptr)
        *ptr = '\0';
    ptr = ch;
	while (*ptr != '\0')
	{
		if (isdigit(*ptr) && *ptr != ' ')
		{
			return 0;
		}
		ptr++;
	}
	return 1;
}
char* isStrInputCorrect(unsigned int strLen)
{
    char* ptr;
    char* input = (char*)malloc(strLen * sizeof(char));
    if (!input)
    {
        perror("Error allocating memory for new element");
        return NULL;
    }

    while (fgets(input, strLen, stdin))
    {

        if (!isStrOnlyLetters(input) || input[0] == '\0')
        {
            puts("Something went wrong, try writing without numbers try after pressing enter . . . ");
            while (getchar() != '\n');
        
        }
        else
        {
            ptr = strchr(input, '\n');
            if (ptr)
                *ptr = '\0';
            else
                while (getchar() != '\n');
            return input;
        }
    }
    free(input);
    return NULL;
}


int isIntInputCorrect(int floorInt, int ceilInt)
{
    int check;
    while (scanf("%d", &check) != 1 || check < floorInt || check > ceilInt)
    {
        while (getchar() != '\n');
        printf("������������ ������ ������ �����, ���� ����� �� ����� � �������� �� %d �� %d. ��������� ������� ����� ... \n", floorInt, ceilInt);
    }
    return check;
}