#ifndef GENERATE_OUTPUT_H_
#define GENERATE_OUTPUT_H_
/* Inclusion */
#include "SecondTransitionHelper.h"
#include "Configurations.h"
#include "SideFunctions.h"
#include "SecondTransition.h"
#include "RIJinstructions.h"
#include "InstructionsReader.h"
#include "Output.h"

/**
 * Print binary code as hex to the ob file
 * @param data - the coding data to print
 */ 
void print_binary(FullCoding_t * data);

/**
 * Display the memory data according to the right instruction formatting
 * @param data - the memory data
 */ 
void DisplayMemoryData(MemoryAllocData_t * Data);


/**
 * helper function to print the memory data
 * @param address - the memoery data address
 * @param data - the data itself
 */ 
void OutMemoryData(signed int address, char * Data);

/**
 * print entry stuff (with the right formatting for entry)
 */ 
void displayEntry();

/**
 * print external stuff (with the right formatting for external)
 */ 
void displayExtern();

/**
 * Write all of the data to files (.ob, .ext, .ent) 
 */ 
void displayTable();

#endif

