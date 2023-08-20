#ifndef PARSER_H_
#define PARSER_H_
/* Inclusion */
#include <stdint.h>
#include "SecondTransitionHelper.h"
#include "Configurations.h"
#include "SideFunctions.h"
#include "SecondTransition.h"
#include "RIJinstructions.h"
#include "InstructionsReader.h"
#include "Output.h"

/**
 * Initialize parsing (variables, callocs and more)
 * @param FileName - file
 */ 
void Initialize(char * FileName);

/**
 * Get all labels in file ("first process")
 */ 
void FirstProcess();

/**
 * Parse all lines ("second process")
 */ 
void ParseAllLines();

/**
 * Parse a line (helper to parse all lines)
 * @param Line - line to parse
 * @param instruction - instruction
 */ 
void ParseLine(char * Line, Instruction_t * instruction);

/**
 * Get machine code
 */ 
void GetMachineCode();

/**
 * Free allocated memory of everything in our program
 */ 
void deleteAll();
#endif

