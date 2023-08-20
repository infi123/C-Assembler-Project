#ifndef UPDATE_OUTPUT_DATA_H_
#define UPDATE_OUTPUT_DATA_H_
/* Inclusion */
#include "SecondTransitionHelper.h"


/**
 * Add extern variable
 * @param var - variable
 */ 
void AddExtern(char * var);

/**
 * Add entry variable
 * @param var - variable
 */ 
void AddEntry(char * var);

/**
 * Add extern out variable
 * @param var - variable
 */ 
void AddExternOut(char * var, signed int address);

/**
 * Add entry out variable
 * @param var - variable
 */ 
void AddEntryOut(char * var, signed int address);
#endif
