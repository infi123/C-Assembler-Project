#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Parser.h"
#include "Errors.h"

int main(int argc, char *argv[])
{
	int i;
	
	if(argc < 2) {	/*if the user didn't mention a filename correctly or didn't mention at all then generate this message*/
		printf("Usage: ./assembler filename.as\n");
		exit(1);	/*stops the program*/
	}

	/*run over all of the arguments and execute methods */
	for (i = 1; i < argc; i++)
	{
		Initialize(argv[i]);	/*initialize all data structures*/
		FirstProcess();	/*ran over all commands and saves and executes lables, variables and more - actually first process*/
		ParseAllLines();	/*second process */
		GetMachineCode();	/*getting the machine code of the code that received*/
		if (Error_GetErrorsCount() == 0)	/*if the code was succesfully compiled without errors*/
		{
			displayTable();	/*then execute output files*/
		}
		else
		{
			Error_DisplayErrorMessages();	/*then if there was atleast one error means the code was unsuccessfully compiled and prints the errors*/
		}
		deleteAll();
	}
	return 0;
}

