#ifndef MEMORY_COMMANDS_HANDLER_H_
#define MEMORY_COMMANDS_HANDLER_H_
/* Inclusion */
#include "Configurations.h"
#include "SideFunctions.h"
#include "SecondTransition.h"
#include "RIJinstructions.h"
#include "InstructionsReader.h"
#include "SecondTransition.h"
#include "SecondTransitionHelper.h"
#include "SideFunctions.h"

/**
 * initialize all instruction data structures 
 * @param instruction - get the instruction
 * @param DataPtr - Data pointer
 */ 
void MemoryAllocInstruction(char * instruction, MemoryAllocData_t * DataPtr);

/**
 * returns the instructions structures data 
 * @param instruction - instruction
 * @param DataPtr - data pointer
 */ 
void MemoryGetData(char * instruction, MemoryAllocData_t * DataPtr);

/**
 * Get instruction and count how many params it has
 * @param instruction - instruction
 * @return count
 */ 
int count_parameters(char * instruction);

/**
 * allocate and assign a new memory line
 */ 
void NewMemoryLine();

/**
 * Handle memory allocation - initalize structures meant for second process
 */ 
void HandleMemoryAllocation();

/**
 * helper function to get the start address for memory allocation
 */ 
int GetStartAddressForMemory();

MemoryAllocationInstructions_t GetMemoryInstruction(char * instructionText);

/** 
 * Count asciz in a given data
 * @param DataTxt - the data
*/
int countAscizData(char * DataTxt);
#endif

