/* Inclusion */
#include "SecondTransition.h"
#include <stdlib.h>
#include <string.h>

/* Externed variables */
extern ExternVarData_t * CurrentExtern;
extern ExternVarData_t * CurrentEntry;
extern ExternOut_t * CurrentExtOut;
extern ExternOut_t * CurrentEntOut;

void AddExtern(char * var)
{
	memset(CurrentExtern->varName, 0, sizeof(CurrentExtern->varName));
	strcpy(CurrentExtern->varName, var);

	CurrentExtern->nxtVar = (ExternVarData_t *)calloc(sizeof(ExternVarData_t), 1);

	CurrentExtern = CurrentExtern->nxtVar;
}

void AddEntry(char * var)
{
	memset(CurrentEntry->varName, 0, sizeof(CurrentEntry->varName));
	strcpy(CurrentEntry->varName, var);

	CurrentEntry->nxtVar = (ExternVarData_t *)calloc(sizeof(ExternVarData_t), 1);

	CurrentEntry = CurrentEntry->nxtVar;
}

void AddExternOut(char * var, signed int address)
{
	CurrentExtOut->Address = address;
	strcpy(CurrentExtOut->varName, var);

	CurrentExtOut->nxt = (ExternOut_t*)calloc(sizeof(ExternOut_t), 1);

	CurrentExtOut = CurrentExtOut->nxt;
}

void AddEntryOut(char * var, signed int address)
{
	CurrentEntOut->Address = address;
	strcpy(CurrentEntOut->varName, var);

	CurrentEntOut->nxt = (ExternOut_t*)calloc(sizeof(ExternOut_t), 1);

	CurrentEntOut = CurrentEntOut->nxt;
}

