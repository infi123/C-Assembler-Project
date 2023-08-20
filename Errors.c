/* Inclusion */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Errors.h"
#include "Configurations.h"

/* Private variables */
Error_t * errors_list = NULL;
Error_t * current_error = NULL;

static char * error_messages[][50] = {{
"Unrecognized assembly instruction\0",
"Unrecognized register number\0",
"Immidiate value MUST be integer\0",
"Syntax error\0",
"Unrecognized label\0"
}};

int number_of_errors = 0;
extern char inputFileName[MAX_FILE_NAME_SIZE];

void Error_InitErrorHandler()
{
	errors_list = (Error_t *)malloc(sizeof(Error_t));
	errors_list->line_number = 0;
	errors_list->nxt_error = NULL;
	errors_list->pre_error = NULL;
	current_error = errors_list;

}

void Error_ReportError(ErrorType_t errorType, int lineNumber)
{
	lineNumber = (lineNumber + 1) / 2;

	number_of_errors++; /* increase number of errors */

	if (Error_GetErrorsCount() == 1)
	{
		/* if there is only one error, assign*/
		errors_list->line_number = lineNumber;
		errors_list->error_type = errorType;
		errors_list->error_message = error_messages[0][errorType];
		errors_list->nxt_error = NULL;

		current_error = errors_list->nxt_error;
	}


}

void Error_DisplayErrorMessages()
{
	Error_t * temp = errors_list;
	int count = 1;
	
	printf("%d Errors found in %s\n", Error_GetErrorsCount(), inputFileName);
	while (temp != NULL)
	{
		/* while temp (next error) exist, print them.*/
		printf("%-4d%s in line: %d\n", count, temp->error_message, temp->line_number);

		temp = temp->nxt_error;
		count++;
	}
}

int Error_GetErrorsCount()
{
	return number_of_errors;
}

