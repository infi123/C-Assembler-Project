/* Inclusion */
#include <stdlib.h>
#include <stdio.h>
#include "SideFunctions.h"
#include "SecondTransition.h"

extern FullCoding_t* FirstLine;
extern MemoryAllocData_t * MemoryStack;
extern ExternVarData_t * ExternFirst;
extern ExternVarData_t * EntryFirst;
extern FullCoding_t * CurrentDecoded;
extern FILE * InputFileHandler;
extern FullCoding_t * CurrentLine;
extern int current_line_number;

int GetLine(char * RetLine)
{
	int index = 0;
	char data = 0;

	fscanf(InputFileHandler, "%c", &data);
	current_line_number++;
	if (data != EOF && data != '\0')
	{
		if (data == '\n')
		{
			
			return 0;
		}
		do
		{
			RetLine[index] = data;
			index++;
			fscanf(InputFileHandler, "%c", &data);
		} while (data != '\n' && data != EOF && data != '\0' && data != 13);
	}
	else
	{
		return -1;
	}

	return index;
}

int ContainsALabel(char * Line, char * RetLabel)
{
	int index = 0;
	while (Line[index] != ' ' && Line[index] != '\t' && Line[index] != '\n' && Line[index] != '\0' && Line[index] != 13 && Line[index] != ':')
	{
		RetLabel[index] = Line[index];
		index++;
	}

	if (Line[index] != ':') /* Doesn't contain a label */
	{
		memset(RetLabel, 0, index);
		index = 0;
	}

	return index;
}

void NewCodeLine()
{
	CurrentLine->nxtCodeLine = (FullCoding_t *)calloc(sizeof(FullCoding_t), 1);
	CurrentLine->nxtCodeLine->Address = CurrentLine->Address + 4;
	CurrentLine->nxtCodeLine->Machine_Code = 0;
	CurrentLine->nxtCodeLine->nxtCodeLine = NULL;
	memset(CurrentLine->nxtCodeLine->code, 0, 80);
	CurrentLine->instruction_information.lineNumber = GetLineNumber();
	CurrentLine = CurrentLine->nxtCodeLine;
}

int GetLabelAddress(char * labelName)
{
	FullCoding_t * temp = FirstLine;
	MemoryAllocData_t * tempMemory = MemoryStack;
	ExternVarData_t * tempExtern = ExternFirst;
	ExternVarData_t * tempEntry = EntryFirst;



	while (temp->nxtCodeLine != NULL)
	{
		if (strcmp(labelName, temp->label) == 0)
		{
			while (tempEntry->nxtVar != NULL)
			{
				if (strcmp(labelName, tempEntry->varName) == 0)
				{
					AddEntryOut(tempEntry->varName, temp->Address);
					break;
				}
				tempEntry = tempEntry->nxtVar;
			}
			return temp->Address;
		}
		temp = temp->nxtCodeLine;
	}

	while (tempMemory->nxtMemoryAlloc != NULL)
	{
		if (strcmp(labelName, tempMemory->label) == 0)
		{
			while (tempEntry->nxtVar != NULL)
			{
				if (strcmp(labelName, tempEntry->varName) == 0)
				{
					AddEntryOut(tempEntry->varName, tempMemory->Address);
					break;
				}
				tempEntry = tempEntry->nxtVar;
			}
			return tempMemory->Address;
		}
		tempMemory = tempMemory->nxtMemoryAlloc;
	}

	while (tempExtern->nxtVar != NULL)
	{
		if (strcmp(labelName, tempExtern->varName) == 0)
		{
			AddExternOut(tempExtern->varName, CurrentDecoded->Address);
			return 0;
		}
		tempExtern = tempExtern->nxtVar;
	}

	return -1;
}

int GetLineAddress(char * linetxt)
{
	FullCoding_t * temp = FirstLine;
	while (temp->nxtCodeLine != NULL)
	{
		if (strcmp(linetxt, temp->code) == 0)
		{
			return temp->Address;
		}
		temp = temp->nxtCodeLine;
	}

	return -1;
}

int ParseUntil(char * Line, char stopChar)
{
	int index = 0;
	while (Line[index] != stopChar)
	{
		index++;
	}

	return index + 1;
}

int ParseUntilNumber(char * Line)
{
	int index = 0;
	while ((Line[index] < '0' || Line[index] > '9') && Line[index] != '-')
	{
		index++;
	}

	return index;
}

int RemoveWhiteSpaces(char * Line)
{
	int index = 0;
	while (Line[index] == ' ' || Line[index] == '\t')
	{
		index++;
	}

	return index;
}

void GetMachine(FullCoding_t * DataPtr)
{
	if (DataPtr->instruction_information.type == R_TYPE)
	{
		DataPtr->Machine_Code = (DataPtr->instruction_information.opCode << 26) |
			(DataPtr->instruction_information.RS << 21) |
			(DataPtr->instruction_information.RT << 16) |
			(DataPtr->instruction_information.RD << 11) |
			(DataPtr->instruction_information.function << 6);
	}
	else if (DataPtr->instruction_information.type == I_TYPE)
	{
		DataPtr->Machine_Code = (DataPtr->instruction_information.opCode << 26) |
			(DataPtr->instruction_information.RS << 21) |
			(DataPtr->instruction_information.RT << 16) |
			((DataPtr->instruction_information.immidiateValue & 0xFFFF));
	}
	else if (DataPtr->instruction_information.type == J_TYPE)
	{
		if (DataPtr->instruction_information.Instruction_Name == STOP)
		{
			DataPtr->Machine_Code = (DataPtr->instruction_information.opCode << 26);
		}
		else
		{
			DataPtr->Machine_Code = (DataPtr->instruction_information.opCode << 26) |
				(((DataPtr->instruction_information.Reg & 0x1) << 25)) |
				((DataPtr->instruction_information.Address) & 0xFFFFFF);
		}
	}
}

int GetLineNumber()
{
	return current_line_number;
}

