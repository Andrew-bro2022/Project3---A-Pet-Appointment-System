/*
*****************************************************************************
File: core.c
Full Name  : Yuchi Zheng
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

// System Libraries
#include <stdio.h>

// String Libraries
#include <string.h>

// Ctype Libraries
#include <ctype.h>

// include the user library "core" so we can use those functions
#include "core.h"


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// 1.Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// 2.Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

// 3.Display an array of 10-character digits as a formatted phone number.
void displayFormattedPhone(const char inputPhoneCString[])
{
	int i, digitalCount = 0;

	if (inputPhoneCString == NULL)
	{
		printf("(___)___-____");
	}
	else
	{
		for (i = 0; inputPhoneCString[i] != '\0'; i++)
		{
			if (isdigit(inputPhoneCString[i]))
			{
				digitalCount += 1;
			}
		}

		if (digitalCount != 10)
		{
			printf("(___)___-____");
		}
		else
		{
			for (i = 0; i < 6; i++)
			{
				if (i == 0)
				{
					printf("(");
				}
				else if (i == 3)
				{
					printf(")");
				}
				putchar(inputPhoneCString[i]);
			}

			printf("-");
			printf("%s", &inputPhoneCString[6]);   //ADD "&" MEANS FROM 6TH ADRRESS
		}
	}
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

//
// Copy your work done from Milestone #2 (core.c) into this file
// - Organize your functions in the same order as they are listed in the core.h file
// 
// 1.Get user input of int type and validate for  an integer value is entered.
// (return a valide integer value)
int inputInt(void)
{
	char newLine = 'x';
	int value;

	do {
		if (newLine != '\n')
		{
			scanf("%d%c", &value, &newLine);

			if (newLine != '\n')
			{
				clearInputBuffer();
				printf("Error! Input a whole number: ");
			}
		}
	} while (newLine != '\n');

	return value;
}

// 2.Get user input of int type and validate for  an positive integer value is entered.
// (return a positive valide integer value)
int inputIntPositive(void)
{
	int valuePositive = 0;

	do {
		valuePositive = inputInt();
		if (valuePositive <= 0)
		{
			printf("ERROR! Value must be > 0: ");
		}

	} while (valuePositive <= 0);

	return valuePositive;
}

// 3.Get user input of int type and validate for its value is within the range (inclusive). 
// (return a valide integer value in range)
int inputIntRange(const int lowerBound,
				  const int upperBound)
{
	int valueRange = 0;

	do {
		valueRange = inputInt();
		if (valueRange < lowerBound || valueRange > upperBound)
		{
			

			printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
		}

	} while (valueRange < lowerBound || valueRange > upperBound);

	return valueRange;
}

// 4.Get user input of char type and validate for its value is within the list of valid characters 
// (return a valide single character value in the lsit range)
char inputCharOption(const char valideCString[])
{
	char inputChar, newLine;
	int i, invalide;

	do {
		invalide = 1;

		scanf("%c%c", &inputChar, &newLine);
		//clearInputBuffer();

		if (newLine == '\n')
		{
			for (i = 0; valideCString[i] != '\0' && invalide != 0; i++)
			{
				if (inputChar == valideCString[i])
				{
					invalide = 0;
				}
			}

			if (invalide)
			{
				printf("ERROR: Character must be one of [%s]: ", valideCString);
			}
		}
		else
		{
			clearInputBuffer();
			printf("ERROR: Character must be one of [%s]: ", valideCString);
		}

		

	} while (invalide);

	return inputChar;
}

// 5.Get user input of a Cstring type and validate for its length is within the character range specified 
void inputCString(char inputCString[],
				  const int lowerBound,
				  const int upperBound)
{
	int length = 0;
	char tempCString[1000 + 1] = { '\0' };

	do {
		scanf("%1000[^\n]", tempCString);
		clearInputBuffer();

		length = strlen(tempCString);

		if ((length != lowerBound) && (lowerBound == upperBound))
		{
			printf("ERROR: String length must be exactly %d chars: ", lowerBound);
		}

		else if (length < lowerBound)
		{
			printf("ERROR: String length must be between %d and %d chars: ", lowerBound, upperBound);

		}
		else if (length > upperBound)
		{
			printf("ERROR: String length must be no more than %d chars: ", upperBound);
		}
		else
		{
			strcpy(inputCString, tempCString);
		}

	} while (length < lowerBound || length > upperBound);
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////


	



	
	

