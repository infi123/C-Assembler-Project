/* Inclusion */
#include <stdlib.h>
#include <string.h>
#include "RIJinstructions.h"
#include "SideFunctions.h"
#include "Errors.h"

/*This function is used to parse R-type instructions. It reads the instruction from a string, extracting parameters such as registers 
(designated by a $ symbol followed by a number), and checking that the syntax of the instruction is correct 
(e.g., there should be no spaces, commas, etc. in incorrect locations).*/
void R_Instruction(char * Line, Instruction_t * instruction)
{
	/* Needed variables */
	char text[5] = { 0 };
	int Line_index = 0;
	int Text_index = 0;

	/* Get the first parameter of the line */
	/* Prepare for extracting the first parameter */
	Line_index += RemoveWhiteSpaces(&Line[Line_index]);
	if (Line[Line_index] != '$')
	{
		Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
		return;
	}
	Line_index++;
	memset(text, 0, sizeof(text));
	Text_index = 0;

	/* Get the first argument */
	while (Line[Line_index] >= '0' && Line[Line_index] <= '9') /* Stil have numbers */
	{
		text[Text_index] = Line[Line_index];
		Line_index++;
		Text_index++;
	}
	if (Text_index == 0)
	{
		Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
		return;
	}

	instruction->RS = atoi(text);
	if (atoi(text) >= 32)
	{
		Error_ReportError(ERROR_NOT_A_REGISTER, instruction->lineNumber);
	}

	if (instruction->Instruction_Name != MOVE && instruction->Instruction_Name != MVHI &&
		instruction->Instruction_Name != MVLO)
	{
		/* Prepare for extracting RT */
		memset(text, 0, sizeof(text));
		Text_index = 0;
		/* RT Parameter */
		Line_index += RemoveWhiteSpaces(&Line[Line_index]);
		if (Line[Line_index] != ',')
		{
			Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
			return;
		}
		Line_index++;

		Line_index += RemoveWhiteSpaces(&Line[Line_index]);
		if (Line[Line_index] != '$')
		{
			Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
			return;
		}
		Line_index++;

		while (Line[Line_index] >= '0' && Line[Line_index] <= '9') /* Stil have numbers */
		{
			text[Text_index] = Line[Line_index];
			Line_index++;
			Text_index++;
		}
		if (Text_index == 0)
		{
			Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
			return;
		}
		


		instruction->RT = atoi(text);
		if (atoi(text) >= 32)
		{
			Error_ReportError(ERROR_NOT_A_REGISTER, instruction->lineNumber);
		}
	}
	else
	{
		instruction->RT = 0;
	}

	/* Prepare for extracting RD  */
	memset(text, 0, sizeof(text));
	Text_index = 0;

	/* Extracting RD */
	Line_index += RemoveWhiteSpaces(&Line[Line_index]);
	if (Line[Line_index] != ',')
	{
		Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
		return;
	}
	Line_index++;

	Line_index += RemoveWhiteSpaces(&Line[Line_index]);
	if (Line[Line_index] != '$')
	{
		Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
		return;
	}
	Line_index++;
	while (Line[Line_index] >= '0' && Line[Line_index] <= '9') /* Stil have numbers */
	{
		text[Text_index] = Line[Line_index];
		Line_index++;
		Text_index++;
	}
	if (Text_index == 0)
	{
		Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
		return;
	}

	Line_index += RemoveWhiteSpaces(&Line[Line_index]);
	if (Line[Line_index] != '\n' && Line[Line_index] != '\0')
	{
		Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
		return;
	}

	instruction->RD = atoi(text);
	if (atoi(text) >= 32)
	{
		Error_ReportError(ERROR_NOT_A_REGISTER, instruction->lineNumber);
	}

	instruction->function = (instruction->Instruction_Name % 5) + 1;
	instruction->opCode = instruction->Instruction_Name / 5;
}

/*This function is for I-type instructions. It follows a similar pattern to R_Instruction, but also handles immediate values 
(i.e., constants) and label references for branching instructions.*/
void I_Instruction(char * Line, Instruction_t * instruction, int index)
{
	/* Needed variables */
	char text[MAX_LABEL_SIZE] = { 0 };
	int Line_index = index;
	int Text_index = 0;
	int currentAddress;
	int targetAddress;

	/* Get the first parameter of the line */
	/* Prepare for extracting the first parameter */
	Line_index += RemoveWhiteSpaces(&Line[Line_index]);
	if (Line[Line_index] != '$')
	{
		Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
		return;
	}
	Line_index++;
	memset(text, 0, MAX_LABEL_SIZE);
	Text_index = 0;

	/* Get the first argument */
	while (Line[Line_index] >= '0' && Line[Line_index] <= '9') /* Stil have numbers */
	{
		text[Text_index] = Line[Line_index];
		Line_index++;
		Text_index++;
	}
	if (Text_index == 0)
	{
		Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
		return;
	}

	instruction->RS = atoi(text);
	if (atoi(text) >= 32)
	{
		Error_ReportError(ERROR_NOT_A_REGISTER, instruction->lineNumber);
	}

	instruction->opCode = 10 + instruction->Instruction_Name - ADDI;

	if (instruction->Instruction_Name == BEQ || instruction->Instruction_Name == BNE ||
		instruction->Instruction_Name == BLT || instruction->Instruction_Name == BGT) /* Branching instructions */
	{
		/* Prepare for extracting RT(The second register to compare) */
		memset(text, 0, MAX_LABEL_SIZE);
		Text_index = 0;
		/* RT Parameter */
		Line_index += RemoveWhiteSpaces(&Line[Line_index]);
		if (Line[Line_index] != ',')
		{
			Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
			return;
		}
		Line_index++;
		
		Line_index += RemoveWhiteSpaces(&Line[Line_index]); 
		if (Line[Line_index] != '$')
		{
			Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
			return;
		}
		Line_index++;
		while (Line[Line_index] >= '0' && Line[Line_index] <= '9') /* Stil have numbers */
		{
			text[Text_index] = Line[Line_index];
			Line_index++;
			Text_index++;
		}
		if (Text_index == 0)
		{
			Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
			return;
		}

		instruction->RT = atoi(text);
		if (atoi(text) >= 32)
		{
			Error_ReportError(ERROR_NOT_A_REGISTER, instruction->lineNumber);
		}

		/* get the label */
		Line_index += RemoveWhiteSpaces(&Line[Line_index]);
		if (Line[Line_index] != ',')
		{
			Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
			return;
		}
		Line_index++;
		Line_index += RemoveWhiteSpaces(&Line[Line_index]);
		if (strchr(&Line[Line_index], ',') != NULL)
		{
			Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
			return;
		}
		memset(text, 0, MAX_LABEL_SIZE);
		Text_index = 0;
		while (Line[Line_index] != ' ' && Line[Line_index] != '\t' && Line[Line_index] != '\n' && Line[Line_index] != '\0')
		{
			text[Text_index] = Line[Line_index];
			Text_index++;
			Line_index++;
		}
		if (Text_index == 0)
		{
			Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
			return;
		}

		Line_index += RemoveWhiteSpaces(&Line[Line_index]);
		if (Line[Line_index] != '\n' && Line[Line_index] != '\0')
		{
			Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
			return;
		}
		targetAddress = GetLabelAddress(text);
		currentAddress = GetLineAddress(Line);
		if (targetAddress == -1)
		{
			/* Not exit */
			Error_ReportError(ERROR_NOT_A_LABEL, instruction->lineNumber);
			return;
		}
		else
		{
			instruction->immidiateValue = targetAddress - currentAddress;
		}
	}
	else
	{	/* Immidiate value instruction */
		/* Prepare for immidiate value */
		Line_index += RemoveWhiteSpaces(&Line[Line_index]);
		if (Line[Line_index] != ',')
		{
			Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
			return;
		}
		Line_index ++;
		Line_index += RemoveWhiteSpaces(&Line[Line_index]);
		memset(text, 0, sizeof(text));
		Text_index = 0;

		/* Extract immidiate value */
		if (Line[Line_index] == '-')
		{
			text[Text_index] = '-';
			Text_index++;
			Line_index++;
		}
		if (Line[Line_index] >= '0' && Line[Line_index] <= '9')
		{
			while (Line[Line_index] >= '0' && Line[Line_index] <= '9') /* Stil have numbers */
			{
				text[Text_index] = Line[Line_index];
				Line_index++;
				Text_index++;
			}
			if ((text[0] == '-' && text[1] == '\0') || text[0] == '\0')
			{
				Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
				return;
			}

			instruction->immidiateValue = atoi(text);
		}
		else
		{
			Error_ReportError(ERROR_IMMIDIATE_VALUE, instruction->lineNumber);
			return;
		}
		

		/* prepare for RT Parameter */
		Line_index += RemoveWhiteSpaces(&Line[Line_index]);
		if (Line[Line_index] != ',')
		{
			Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
			return;
		}
		Line_index++;
		Line_index += RemoveWhiteSpaces(&Line[Line_index]);
		if (Line[Line_index] != '$')
		{
			Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
			return;
		}
		Line_index++;

		memset(text, 0, sizeof(text));
		Text_index = 0;

		/* Extract RT */
		while (Line[Line_index] >= '0' && Line[Line_index] <= '9') /* Stil have numbers */
		{
			text[Text_index] = Line[Line_index];
			Line_index++;
			Text_index++;
		}
		if (Text_index == 0)
		{
			Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
			return;
		}

		instruction->RT = atoi(text);
		if (atoi(text) >= 32)
		{
			Error_ReportError(ERROR_NOT_A_REGISTER, instruction->lineNumber);
		}

		Line_index += RemoveWhiteSpaces(&Line[Line_index]);
		if (Line[Line_index] != '\n' && Line[Line_index] != '\0')
		{
			Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
			return;
		}
	}
}

/*This  function is used for J-type instructions. It also checks for the presence of a $ symbol to determine 
if it's a register or an address, and also handles a special case of a "STOP" instruction.*/
void J_Instruction(char * Line, Instruction_t * instruction, int index)
{
	int index_line = index;
	char text[3] = { 0 };
	int textIndex = 0;

	if (instruction->Instruction_Name == STOP)
	{
		instruction->opCode = 63;
		instruction->Address = 0;
		instruction->Reg = 0;
	}
	else
	{
		instruction->opCode = 30 + (instruction->Instruction_Name - JMP);
		index_line += RemoveWhiteSpaces(&Line[index_line]);

		if (Line[index_line] == '$')
		{
			index_line++;
			instruction->Reg = 1;

			memset(text, 0, 3);
			while (Line[index_line] != ' ' && Line[index_line] != '\n' && Line[index_line] != '\0')
			{
				text[textIndex] = Line[index_line];
				textIndex++;
				index_line++;
			}
			if (textIndex == 0)
			{
				Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
				return;
			}
			instruction->Address = atoi(text);
			if (instruction->Address >= 32)
			{
				Error_ReportError(ERROR_NOT_A_REGISTER, instruction->lineNumber);
				return;
			}
			index_line += RemoveWhiteSpaces(&Line[index_line]);
			if (Line[index_line] != '\n' && Line[index_line] != '\0')
			{
				Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
				return;
			}
		}
		else
		{
			instruction->Reg = 0;
			instruction->Address = GetLabelAddress(&Line[index_line]);
			if (instruction->Address == -1) /* Not a label */
			{
				Error_ReportError(ERROR_SYNTAX_ERROR, instruction->lineNumber);
				return;
			}
		}
	}
}

