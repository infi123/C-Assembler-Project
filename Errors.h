#ifndef ERROR_HANDLER_H_
#define ERROR_HANDLER_H_

/* Error Types */
enum ErrorType_t
{
	ERROR_NOT_AN_INSTRUCTION = 0,
	ERROR_NOT_A_REGISTER,
	ERROR_IMMIDIATE_VALUE,
	ERROR_SYNTAX_ERROR,
	ERROR_NOT_A_LABEL
};

typedef enum ErrorType_t ErrorType_t;

/**
contains error data
*/
struct Error_t
{
	int line_number;
	char * error_message;
	ErrorType_t error_type;
	struct Error_t * nxt_error;
	struct Error_t * pre_error;
};
typedef struct Error_t Error_t;

/* functions prototype */

/**
 * Initialize error handler
 */
void Error_InitErrorHandler();

/**
 * "Report" errors will add the error to the struct with their line number, cause וכו׳...
 */ 
void Error_ReportError(ErrorType_t errorType, int lineNumber);

/**
 * Print error message to the user
 */ 
void Error_DisplayErrorMessages();


/**
 * Simple helper to get the number of errors
 */ 
int Error_GetErrorsCount();

#endif

