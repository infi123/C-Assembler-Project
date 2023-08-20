#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_
/* Inclusion */
#include "SecondTransitionHelper.h"
#include <string.h>

/**
 * Read line from the file
 * @param RetLine - line
 */ 
int GetLine(char * RetLine);

/**
 * Check if line contains a label, and checking from where the label starts and finishes
 * @param line - line
 * @param RetLabel
 */
int ContainsALabel(char * Line, char * RetLabel);

/**
 * function to set a new line of code to the struct
 */ 
void NewCodeLine();

/**
 * Get the address of the label
 * @param labelName - the label to get the address of
 */ 
int GetLabelAddress(char * labelName);

/**
 * get line address
 * @param linetxt - the line t get the address from
 */ 
int GetLineAddress(char * linetxt);

/**
 * helper function to parse until a certain char
 * @param line - line to parse
 * @param stopChar - a char to stop parsing when getting to it
 */ 
int ParseUntil(char * Line, char stopChar);

/**
 * helper function to parse until a number is shown
 * @param line - line to parse
 */ 
int ParseUntilNumber(char * Line);

/**
 * Remove white spaces from a certain line
 * @param Line - line to remoe spaces from
 */ 
int RemoveWhiteSpaces(char * Line);

/**
 * Get machine code from data ptr(coding)
 * @param DataPtr - the "full coding" to get the machine code from
 */ 
void GetMachine(FullCoding_t * DataPtr);

/**
 * Simple function to get line number
 */ 
int GetLineNumber();

#endif
