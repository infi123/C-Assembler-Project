#ifndef PARSE_MAIN_COMMANDS_H_
#define PARSE_MAIN_COMMANDS_H_
/* Inclusion */
#include "SecondTransitionHelper.h"

/**
 * Parse an R Instruction
 */ 
void R_Instruction(char * Line, Instruction_t * instruction);

/**
 * Parse an I Instruction
 */ 
void I_Instruction(char * Line, Instruction_t * instruction, int index);

/**
 * Parse an J Instruction
 */ 
void J_Instruction(char * Line, Instruction_t * instruction, int index);
#endif
