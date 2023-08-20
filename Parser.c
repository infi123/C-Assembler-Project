/* Inclusion */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parser.h"
#include "Errors.h"

/* Externed variables */
extern char instructions_txt[NUMBER_OF_INSTRUCTIONS][5];
extern char memory_alloc_instruction_txt[NUMBER_OF_ALLOC_INSTRUCTIONS][7];
extern FILE * InputFileHandler;
extern FILE * OutputFileHandler;
extern FullCoding_t * FirstLine;
extern FullCoding_t * CurrentLine;
extern FullCoding_t * CurrentDecoded;
extern MemoryAllocData_t * MemoryStack;
extern MemoryAllocData_t * CurrentMemoryLocation;
extern ExternVarData_t * ExternFirst;
extern ExternVarData_t * CurrentExtern;
extern ExternVarData_t * EntryFirst;
extern ExternVarData_t * CurrentEntry;
extern ExternOut_t * FirstExtOut;
extern ExternOut_t * CurrentExtOut;
extern ExternOut_t * FirstEntOut;
extern ExternOut_t * CurrentEntOut;
extern char inputFileName[MAX_FILE_NAME_SIZE];
extern char pureInputFile[MAX_FILE_NAME_SIZE];
extern char LineTxt[MAX_LINE_SIZE];
extern Error_t * errors_list;
extern Error_t * current_error;
extern int number_of_errors;
extern int current_line_number;

/* Functions */

/* This function initialize some variables and structures for the processing of a file. 
It allocates memory for a number of structs, initializes the values within, and opens the input file. */
void Initialize(char * FileName)
{
	strcpy(inputFileName, FileName);

	FirstLine = (FullCoding_t *)calloc(sizeof(FullCoding_t), 1);
	FirstLine->Address = 100;	/*starting from 100 address*/
	FirstLine->Machine_Code = 0;
	FirstLine->nxtCodeLine = NULL;
	memset(FirstLine->code, 0, 80);
	memset(FirstLine->label, 0, MAX_LABEL_SIZE);

	CurrentLine = FirstLine;
	CurrentDecoded = FirstLine;

	MemoryStack = (MemoryAllocData_t *)calloc(sizeof(MemoryAllocData_t), 1);
	MemoryStack->Data = NULL;
	MemoryStack->nxtMemoryAlloc = NULL;
	MemoryStack->Address = 0;
	MemoryStack->count = 0;

	CurrentMemoryLocation = MemoryStack;

	ExternFirst = (ExternVarData_t *)calloc(sizeof(ExternVarData_t), 1);
	ExternFirst->nxtVar = NULL;

	CurrentExtern = ExternFirst;

	EntryFirst = (ExternVarData_t *)calloc(sizeof(ExternVarData_t), 1);
	EntryFirst->nxtVar = NULL;

	CurrentEntry = EntryFirst;

	FirstExtOut = (ExternOut_t *)calloc(sizeof(ExternOut_t), 1);
	FirstExtOut->nxt = NULL;

	CurrentExtOut = FirstExtOut;

	FirstEntOut = (ExternOut_t *)calloc(sizeof(ExternOut_t), 1);
	FirstEntOut->nxt = NULL;

	CurrentEntOut = FirstEntOut;

	strcpy(pureInputFile, inputFileName);
	pureInputFile[strlen(inputFileName) - 3] = 0;

	InputFileHandler = fopen(inputFileName, "r");

	Error_InitErrorHandler();	/*errors counter*/
}

/* This function processes the first pass of an assembly language file. 
The first pass typically involves identifying labels and calculating their addresses, as well as other preprocessing tasks.*/
void FirstProcess()
{
	char label[MAX_LABEL_SIZE] = { 0 };
	int tempData; 
	int LineIndex = 0;
	MemoryAllocationInstructions_t funcRet;

	memset(LineTxt, 0, MAX_LINE_SIZE);

	tempData = GetLine(LineTxt);

	while (tempData != -1)
	{
		LineIndex = 0;
		if (tempData != 0) /* Not an empty Line */
		{
			LineIndex = ContainsALabel(LineTxt, label);
			LineIndex += (LineIndex != 0);
			if (LineIndex != 0) /* Contains a label */
			{
				LineIndex += RemoveWhiteSpaces(&LineTxt[LineIndex]);
				if (LineTxt[LineIndex] != '.') /* Not a memory allocation instruction */
				{
					strcpy(CurrentLine->label, label);
					memset(label, 0, sizeof(label));
					if (LineTxt[LineIndex] != '\0' && LineTxt[LineIndex] != '\n' && LineTxt[LineIndex] != 13)
					{
						LineIndex += RemoveWhiteSpaces(&LineTxt[LineIndex]);
						strcpy(CurrentLine->code, &LineTxt[LineIndex]);
					}
					NewCodeLine();
				}
				else /* Memory allocation instruction */
				{
					funcRet = GetMemoryInstruction(&LineTxt[LineIndex + 1]);
					if (funcRet >= DB && funcRet <= ASCIZ)
					{
						strcpy(CurrentMemoryLocation->label, label);
						strcpy(CurrentMemoryLocation->code, &LineTxt[LineIndex]);
						MemoryAllocInstruction(&LineTxt[LineIndex + 1], CurrentMemoryLocation);
						NewMemoryLine();
					}
					else if (funcRet == EXTERN)
					{
						if (strchr(&LineTxt[LineIndex], ',') != NULL)
						{
							Error_ReportError(ERROR_SYNTAX_ERROR, GetLineNumber());
						}
						strcpy(CurrentExtern->label, label);
						strcpy(CurrentExtern->code, &LineTxt[LineIndex]);

						LineIndex += strlen(memory_alloc_instruction_txt[EXTERN]) + 1;
						LineIndex += RemoveWhiteSpaces(&LineTxt[LineIndex]);

						AddExtern(&LineTxt[LineIndex]);
					}
					else if (funcRet == ENTRY)
					{
						if (strchr(&LineTxt[LineIndex], ',') != NULL)
						{
							Error_ReportError(ERROR_SYNTAX_ERROR, GetLineNumber());
						}
						strcpy(CurrentEntry->label, label);
						strcpy(CurrentEntry->code, &LineTxt[LineIndex]);

						LineIndex += strlen(memory_alloc_instruction_txt[ENTRY]) + 1;
						AddEntry(&LineTxt[LineIndex]);
					}
				}
			}
			else
			{
				LineIndex += RemoveWhiteSpaces(&LineTxt[LineIndex]);
				if(LineTxt[LineIndex] == '.')	/*checking for label after '.'*/
				{
					funcRet = GetMemoryInstruction(&LineTxt[LineIndex + 1]);
					if (funcRet >= DB && funcRet <= ASCIZ)
					{
						strcpy(CurrentMemoryLocation->code, &LineTxt[LineIndex]);
						MemoryAllocInstruction(&LineTxt[LineIndex + 1], CurrentMemoryLocation);
						NewMemoryLine();
					}
					else if (funcRet == EXTERN)
					{
						if (strchr(&LineTxt[LineIndex], ',') != NULL)
						{
							Error_ReportError(ERROR_SYNTAX_ERROR, GetLineNumber());
						}
						strcpy(CurrentExtern->code, &LineTxt[LineIndex]);

						LineIndex += strlen(memory_alloc_instruction_txt[EXTERN]) + 1;
						LineIndex += RemoveWhiteSpaces(&LineTxt[LineIndex]);

						AddExtern(&LineTxt[LineIndex]);
					}
					else if (funcRet == ENTRY)
					{
						if (strchr(&LineTxt[LineIndex], ',') != NULL)
						{
							Error_ReportError(ERROR_SYNTAX_ERROR, GetLineNumber());
						}
						strcpy(CurrentEntry->code, &LineTxt[LineIndex]);

						LineIndex += strlen(memory_alloc_instruction_txt[ENTRY]) + 1;
						LineIndex += RemoveWhiteSpaces(&LineTxt[LineIndex]);

						AddEntry(&LineTxt[LineIndex]);
					}
					
				}
				else if (LineTxt[LineIndex] != '\0' && LineTxt[LineIndex] != '\n' && LineTxt[LineIndex] != 13)
				{
					LineIndex += RemoveWhiteSpaces(&LineTxt[LineIndex]);
					strcpy(CurrentLine->code, &LineTxt[LineIndex]);
					NewCodeLine();
				}
				else
				{
					NewCodeLine();
				}
			}
		}
		memset(LineTxt, 0, sizeof(LineTxt));
		tempData = GetLine(LineTxt);
	}
}

/*This function execute a second pass of the file, where actual instructions are parsed. 
The ParseLine() function is used in this process, which parses an individual line and updates the instruction based on its content.*/
void ParseAllLines()
{
	FullCoding_t * tempData = FirstLine;

	HandleMemoryAllocation();
	while (tempData->nxtCodeLine != NULL)
	{
		ParseLine(tempData->code, &tempData->instruction_information);
		tempData = tempData->nxtCodeLine;
		CurrentDecoded = CurrentDecoded->nxtCodeLine;
	}
}

void ParseLine(char * Line, Instruction_t * instruction)
{
	/* Needed variables */
	char text[MAX_LABEL_SIZE] = { 0 };
	int Line_index = 0;
	int Text_index = 0;
	int i;

	/* Function logic */
	/* Remove white spaces from the first characters of the line if exists */
	Line_index += RemoveWhiteSpaces(Line);
getTheInstruction:
	memset(text, 0, MAX_LABEL_SIZE);
	Text_index = 0;
	/* Get the instruction name */
	if (Line[Line_index] == '.')
	{
		strcpy(CurrentMemoryLocation->code, &LineTxt[Line_index]);
		MemoryAllocInstruction(&Line[Line_index + 1], CurrentMemoryLocation);
	}
	else
	{
		while (Line[Line_index] != ' ' && Line[Line_index] != '\n' && Line[Line_index] != '\0' && Line[Line_index] != 13)
		{
			text[Text_index] = Line[Line_index];
			Line_index++;
			Text_index++;
		}
		for (i = 0; i < NUMBER_OF_INSTRUCTIONS; i++)
		{
			if (strcmp(text, instructions_txt[i]) == 0)
			{
				break;
			}
		}
		if (i == NUMBER_OF_INSTRUCTIONS)
		{
			/* Not an instruction */
			/* Check if memory allocation instruction */
			if (text[0] == '.')
			{
				text[Text_index - 1] = 0;
				Line_index += RemoveWhiteSpaces(&Line[Line_index]);
				strcpy(CurrentLine->label, text);
				/* Handle the label - using goto because of a suggestion on stackoverflow that it might help here */
				goto getTheInstruction;

			}
			else /* Not an instruction */
			{
				Error_ReportError(ERROR_NOT_AN_INSTRUCTION, instruction->lineNumber);
			}
		}
		else
		{
			instruction->Instruction_Name = i;
		}

		/* Get the type of instruction */
		if (i <= MVLO)
		{
			/* R-Type */
			instruction->type = R_TYPE;
			R_Instruction(&Line[Line_index], instruction);
		}
		else if (i >= ADDI && i <= SH)
		{
			/* I-Type */
			instruction->type = I_TYPE;
			I_Instruction(Line, instruction, Line_index);
		}
		else if(i >= JMP && i <= STOP)
		{
			/* J-Type */
			instruction->type = J_TYPE;
			J_Instruction(Line, instruction, Line_index);
		}
	}
}

/*This function gets the final machine code representation of the parsed assembly code.*/
void GetMachineCode()
{
	FullCoding_t * tempData = FirstLine;
	while (tempData->nxtCodeLine != NULL)
	{
		GetMachine(tempData);
		tempData = tempData->nxtCodeLine;
	}
}

/*This function free all the allocated memory, presumably after the file has been processed. 
This is to avoid memory leaks and clean up all the resources the program has used.*/
void deleteAll()
{
	MemoryAllocData_t * tempMem = MemoryStack->nxtMemoryAlloc;
	MemoryAllocData_t * toDeleteMem = MemoryStack;
	FullCoding_t * tempInst = FirstLine->nxtCodeLine;
	FullCoding_t * toDeleteInst = FirstLine;
	ExternVarData_t * tempExtern = ExternFirst->nxtVar;
	ExternVarData_t * toDeleteExtern = ExternFirst;
	ExternVarData_t * tempEntry = EntryFirst->nxtVar;
	ExternVarData_t * toDeleteEntry = EntryFirst;
	ExternOut_t * tempExtOut = FirstExtOut->nxt;
	ExternOut_t * toDeleteExtOut = FirstExtOut;
	ExternOut_t * tempEntOut = FirstEntOut->nxt;
	ExternOut_t * toDeleteEntOut = FirstEntOut;

	Error_t * tempError = errors_list->nxt_error;
	Error_t * toDeleteError = errors_list;

	while (tempMem != NULL)
	{
		free(toDeleteMem);
		toDeleteMem = tempMem;
		tempMem = tempMem->nxtMemoryAlloc;
	}
	free(toDeleteMem);
	
	while (tempInst != NULL)
	{
		free(toDeleteInst);
		toDeleteInst = tempInst;
		tempInst = tempInst->nxtCodeLine;
	}
	free(toDeleteInst);

	while (tempExtern != NULL)
	{
		free(toDeleteExtern);
		toDeleteExtern = tempExtern;
		tempExtern = tempExtern->nxtVar;
	}
	free(toDeleteExtern);
	
	while (tempEntry != NULL)
	{
		free(toDeleteEntry);
		toDeleteEntry = tempEntry;
		tempEntry = tempEntry->nxtVar;
	}
	free(toDeleteEntry);

	while (tempExtOut != NULL)
	{
		free(toDeleteExtOut);
		toDeleteExtOut = tempExtOut;
		tempExtOut = tempExtOut->nxt;
	}
	free(toDeleteExtOut);
	
	while (tempEntOut != NULL)
	{
		free(toDeleteEntOut);
		toDeleteEntOut = tempEntOut;
		tempEntOut = tempEntOut->nxt;
	}
	free(toDeleteEntOut);

	while (toDeleteError->nxt_error != NULL)
	{
		free(toDeleteError);
		toDeleteError = tempError;
		tempError = tempError->nxt_error;
	}
	free(toDeleteError);
	number_of_errors = 0;
	current_line_number = 0;

	FirstLine = NULL;
	CurrentLine = NULL;

	MemoryStack = NULL;
	CurrentMemoryLocation = NULL;

	ExternFirst = NULL;
	CurrentExtern = NULL;

	EntryFirst = NULL;
	CurrentEntry = NULL;

	FirstExtOut = NULL;
	CurrentExtOut = NULL;

	FirstEntOut = NULL;
	CurrentEntOut = NULL;

	toDeleteError = NULL;
	tempError = NULL;
}
