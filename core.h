/*
*****************************************************************************
File: core.h
Full Name  : Yuchi Zheng
*****************************************************************************
*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.

// !!! DO NOT DELETE THE BELOW 2 LINES !!!
#ifndef CORE_H
#define CORE_H

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Copy your work done from Milestone #2 (core.h) into this file
// 
// NOTE:
// - Organize your functions into the below categories
// - Make sure the core.c file also lists these functions in the same order!
// - Be sure to provide a BRIEF comment for each function prototype
// - The comment should also be copied to the core.c function definition
//
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// 1/ Clear the standard input buffer
void clearInputBuffer(void);

// 2. Wait for user to input the "enter" key to continue
void suspend(void);

// 3. Display an array of 10-character digits as a formatted phone number.
void displayFormattedPhone(const char inputPhoneCString[]);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// 1. Get user input of int type and validate for  an integer value is entered.
// (return a valide integer value)
int inputInt(void);

// 2. Get user input of int type and validate for  an positive integer value is entered.
// (return a positive valide integer value)
int inputIntPositive(void);

// 3. Get user input of int type and validate for its value is within the range (inclusive) 
// (return a valide integer value in range)
int inputIntRange(const int lowerBound,
				  const int upperBound);

// 4. Get user input of char type and validate for its value is within the list of valid characters 
// (return a valide single character value in the lsit range)
char inputCharOption(const char valideCString[]);

// 5. Get user input of a Cstring type and validate for its length is within the character range specified 
void inputCString(char inputCString[],
				  const int lowerBound,
				  const int upperBound);



// !!! DO NOT DELETE THE BELOW LINE !!!
#endif // !CORE_H
