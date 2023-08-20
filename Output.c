/* Inclusion */
#include <stdio.h>
#include <stdlib.h>
#include "Output.h"

extern FILE * OutputFileHandler;
extern FullCoding_t * FirstLine;
extern char pureInputFile[MAX_FILE_NAME_SIZE];
extern ExternOut_t * FirstExtOut;
extern MemoryAllocData_t * MemoryStack;
extern ExternOut_t * FirstEntOut;

/* This function takes a pointer to a FullCoding_t structure (which contains information about an assembly instruction and its machine code equivalent), 
and prints out the binary representation of the machine code to an output file.
It has different formatting routines for R_TYPE, I_TYPE and J_TYPE instructions. */
void print_binary(FullCoding_t * data)
{
	char outData[18] = { 0 };

	/* check type of instruction and format with left/right shift + print the machine code */
	if (data->instruction_information.type == R_TYPE)
	{
		sprintf(outData, "%04d %02X %02X %02X %02X\n", data->Address,
			(unsigned int)(data->Machine_Code & 0xFF), (unsigned int)((data->Machine_Code >> 8) & 0xFF),
			(unsigned int)((data->Machine_Code >> 16) & 0xFF), (unsigned int)((data->Machine_Code >> 24) & 0xFF));

		fprintf(OutputFileHandler, "%s", outData);
	}
	else if (data->instruction_information.type == I_TYPE)
	{
		sprintf(outData, "%04d %02X %02X %02X %02X\n", data->Address,
			(unsigned int)(data->Machine_Code & 0xFF), (unsigned int)((data->Machine_Code >> 8) & 0xFF),
			(unsigned int)((data->Machine_Code >> 16) & 0xFF), (unsigned int)((data->Machine_Code >> 24) & 0xFF));

		fprintf(OutputFileHandler, "%s", outData);
	}
	else if (data->instruction_information.type == J_TYPE)
	{
		sprintf(outData, "%04d %02X %02X %02X %02X\n", data->Address,
			(unsigned int)(data->Machine_Code & 0xFF), (unsigned int)((data->Machine_Code >> 8) & 0xFF),
			(unsigned int)((data->Machine_Code >> 16) & 0xFF), (unsigned int)((data->Machine_Code >> 24) & 0xFF));
		fprintf(OutputFileHandler, "%s", outData);
	}
}

/*This function takes a pointer to a MemoryAllocData_t structure and prints out the memory data according to the right instruction formatting. 
This function deals with different instruction types such as DB, ASCIZ, DH, and DW.*/
void DisplayMemoryData(MemoryAllocData_t * Data)
{
	int BytesCount = 0;
	char OutData[4];
	int i;
	MemoryAllocData_t * temp = Data;
	signed int address = temp->Address;
	char outFileData[20] = { 0 };

	while (temp->nxtMemoryAlloc != NULL)
	{
		/*
		* As long as there is an allocated memory, run over each one and check it instruction type
		* according to the instruction type, check the bytes count and print the memory data 
		* Note to self (TODO - will be deleted): maybe change to switch for more readable for the professor
		*/
		if (temp->InstructionType == DB || temp->InstructionType == ASCIZ)
		{
			for (i = 0; i < temp->count; i++)
			{
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
				OutData[BytesCount] = (unsigned char)(temp->Data[i] & 0xFF);
				BytesCount++;
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
			}
		}
		else if (temp->InstructionType == DH)
		{
			for (i = 0; i < temp->count; i++)
			{
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
				OutData[BytesCount] = (unsigned char)(temp->Data[i] & 0xFF);
				BytesCount++;
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
				OutData[BytesCount] = (unsigned char)((temp->Data[i] >> 8) & 0xFF);
				BytesCount++;
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
			}
		}
		else if (temp->InstructionType == DW)
		{
			for (i = 0; i < temp->count; i++)
			{
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
				OutData[BytesCount] = (unsigned char)(temp->Data[i] & 0xFF);
				BytesCount++;
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
				OutData[BytesCount] = (unsigned char)((temp->Data[i] >> 8) & 0xFF);
				BytesCount++;
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
				OutData[BytesCount] = (unsigned char)((temp->Data[i] >> 16) & 0xFF);
				BytesCount++;
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
				OutData[BytesCount] = (unsigned char)((temp->Data[i] >> 24) & 0xFF);
				BytesCount++;
				if (BytesCount == 4)
				{
					OutMemoryData(address, OutData);
					address += 4;
					BytesCount = 0;
				}
			}
		}

		temp = temp->nxtMemoryAlloc;
	}



	if (BytesCount == 1)
	{
		sprintf(outFileData, "%04d %02X\n", address,
			(OutData[0] & 0xFF));

		fprintf(OutputFileHandler, "%s", outFileData);
	}
	else if (BytesCount == 2)
	{
		sprintf(outFileData, "%04d %02X %02X\n", address,
			(OutData[0] & 0xFF), (OutData[1] & 0xFF));

		fprintf(OutputFileHandler, "%s", outFileData);
	}
	else if (BytesCount == 3)
	{
		sprintf(outFileData, "%04d %02X %02X %02X\n", address,
			(OutData[0] & 0xFF), (OutData[1] & 0xFF),
			(OutData[2] & 0xFF));

		fprintf(OutputFileHandler, "%s", outFileData);
	}
	else if (BytesCount == 4)
	{
		OutMemoryData(address, OutData);
	}
}

/*This helper function takes an address and a data pointer, formats them into a string, and writes this string to the output file. 
It's used within DisplayMemoryData to output individual memory lines.*/
void OutMemoryData(signed int address, char * Data)
{
	char outData[20] = { 0 };

	sprintf(outData, "%04d %02X %02X %02X %02X\n", address,
		(Data[0] & 0xFF), (Data[1] & 0xFF),
		(Data[2] & 0xFF), (Data[3] & 0xFF));

	fprintf(OutputFileHandler, "%s", outData);
}

/*This function iterates over a linked list of ExternOut_t structures and prints out each element's variable name and address to the output file.*/
void displayExtern()
{
	ExternOut_t * temp = FirstExtOut;
	char OutData[MAX_LABEL_SIZE + 6];

	while (temp->nxt != NULL)
	{
		sprintf(OutData, "%s %04d\n", temp->varName, temp->Address);
		fprintf(OutputFileHandler, "%s", OutData);
		temp = temp->nxt;
	}
}

/*This function is similar to displayExtern, but it operates on a list of entries rather than externals.*/
void displayEntry()
{
	ExternOut_t * temp = FirstEntOut;
	char OutData[MAX_LABEL_SIZE + 6];

	while (temp->nxt != NULL)
	{
		sprintf(OutData, "%s %04d\n", temp->varName, temp->Address);
		fprintf(OutputFileHandler, "%s", OutData);
		temp = temp->nxt;
	}
}

/*This function coordinates the overall output to the .ob, .ext, and .ent files. 
It iterates over the FullCoding_t linked list, calling print_binary on each element, then calls DisplayMemoryData and displayExtern to output the memory and extern data.*/
void displayTable()
{
	FullCoding_t * temp = FirstLine;

	/* .ob file */
	sprintf(pureInputFile, "%s.ob", pureInputFile);
	OutputFileHandler = fopen(pureInputFile, "w");

	while (temp->nxtCodeLine != NULL)
	{
		print_binary(temp);
		temp = temp->nxtCodeLine;
	}

	DisplayMemoryData(MemoryStack);

	fclose(OutputFileHandler);
	pureInputFile[strlen(pureInputFile) - 3] = 0;

	/* .ext file */
	sprintf(pureInputFile, "%s.ext", pureInputFile);
	OutputFileHandler = fopen(pureInputFile, "w");
	displayExtern();
	fclose(OutputFileHandler);
	pureInputFile[strlen(pureInputFile) - 4] = 0;

	/* .ent file */
	sprintf(pureInputFile, "%s.ent", pureInputFile);
	OutputFileHandler = fopen(pureInputFile, "w");
	displayEntry();
	fclose(OutputFileHandler);
	pureInputFile[strlen(pureInputFile) - 4] = 0;
}
