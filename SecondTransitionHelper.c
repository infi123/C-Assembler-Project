/* Inclusion */
#include "SecondTransitionHelper.h"
#include <stdio.h>

/* Shared Data */
char instructions_txt[NUMBER_OF_INSTRUCTIONS][5] = {
	"add\0\0",
	"sub\0\0",
	"and\0\0",
	"or\0\0\0",
	"nor\0\0",
	"move\0",
	"mvhi\0",
	"mvlo\0",
	"addi\0",
	"subi\0",
	"andi\0",
	"ori\0\0",
	"nori\0",
	"bne\0\0",
	"beq\0\0",
	"blt\0\0",
	"bgt\0\0",
	"lb\0\0\0",
	"sb\0\0\0",
	"lw\0\0\0",
	"sw\0\0\0",
	"lh\0\0\0",
	"sh\0\0\0",
	"jmp\0\0",
	"la\0\0\0",
	"call\0",
	"stop"
};
char memory_alloc_instruction_txt[NUMBER_OF_ALLOC_INSTRUCTIONS][7] = {
	"db\0",
	"dh\0",
	"dw\0",
	"asciz\0",
	"entry\0",
	"extern\0"
};
FullCoding_t * FirstLine;
FullCoding_t * CurrentLine;
FullCoding_t * CurrentDecoded;
FILE * InputFileHandler = NULL;
FILE * OutputFileHandler = NULL;
char LineTxt[MAX_LINE_SIZE] = { 0 };
char inputFileName[MAX_FILE_NAME_SIZE] = { 0 };
char pureInputFile[MAX_FILE_NAME_SIZE] = { 0 };
MemoryAllocData_t * MemoryStack;
MemoryAllocData_t * CurrentMemoryLocation;
ExternVarData_t * ExternFirst;
ExternVarData_t * CurrentExtern;
ExternVarData_t * EntryFirst;
ExternVarData_t * CurrentEntry;
ExternOut_t * FirstExtOut;
ExternOut_t * CurrentExtOut;
ExternOut_t * FirstEntOut;
ExternOut_t * CurrentEntOut;
int current_line_number = 0;
