#ifndef SHARED_HEADER_H_
#define SHARED_HEADER_H_
#define MAX_COMMAND_LENGTH 80
/* Inclusion */
#include "Configurations.h"

/* User-defined data types */
enum Instruction_Name_t
{
	ADD = 0,
	SUB,
	AND,
	OR,
	NOR,
	MOVE,
	MVHI,
	MVLO,
	ADDI,
	SUBI,
	ANDI,
	ORI,
	NORI,
	BNE,
	BEQ,
	BLT,
	BGT,
	LB,
	SB,
	LW,
	SW,
	LH,
	SH,
	JMP,
	LA,
	CALL,
	STOP
};
typedef enum Instruction_Name_t Instruction_Name_t;

enum MemoryAllocationInstructions_t
{
	DB = 0,
	DH,
	DW,
	ASCIZ,
	ENTRY,
	EXTERN
};
typedef enum MemoryAllocationInstructions_t MemoryAllocationInstructions_t;

struct MemoryAllocData_t
{
	signed int Address;	/*the address*/
	signed char count;
	char label[MAX_LABEL_SIZE];	/*contains a label if there is*/
	char code[MAX_LINE_SIZE];	/*the code itself*/
	signed long * Data;	/*data that was sent along with the instruction*/
	MemoryAllocationInstructions_t InstructionType;	/*instruction type */
	struct MemoryAllocData_t * nxtMemoryAlloc;	/*pointer to the next one - linked list*/
};
typedef struct MemoryAllocData_t MemoryAllocData_t;


enum Instruction_Type_t {
	R_TYPE = 0,
	I_TYPE,
	J_TYPE
};
typedef enum Instruction_Type_t Instruction_Type_t;

struct Instruction_t
{
	signed int immidiateValue;	/*in case of I instruction*/
	unsigned char RS;	/*in case of R or I instruction*/
	unsigned char RT;	/*in case of R or I instruction*/
	unsigned char RD;	/*in case of R instruction*/
	unsigned char function;	/*in case of R instruction*/
	unsigned char opCode;	/*in case of all three kind of instructions*/
	Instruction_Name_t Instruction_Name;	/*the instruction name*/
	Instruction_Type_t type;	/*the instruction type R, I, J*/
	signed long Address;	/*in case of J instruction*/
	int lineNumber;	/*the number of the line at the code*/
	unsigned int Reg : 1;
};
typedef struct Instruction_t Instruction_t;

/*struct to keep all command line content*/
struct FullCoding_t
{
	signed int Address;	/*the adress of command line - start from 100*/
	signed long Machine_Code;	/*the consider command line in machine code*/
	char code[MAX_COMMAND_LENGTH];	/*the actuall command line*/
	char label[MAX_LABEL_SIZE];	/*contains command line's label if there is one*/
	struct FullCoding_t * nxtCodeLine;	/*pointer to next command line - linked list*/
	Instruction_t instruction_information;	/*contains an instruciton if there is*/
};
typedef struct FullCoding_t FullCoding_t;

struct ExternVarData_t
{
	char varName[MAX_VAR_NAME];
	char label[MAX_LABEL_SIZE];
	char code[MAX_LINE_SIZE];
	struct ExternVarData_t * nxtVar;
};
typedef struct  ExternVarData_t ExternVarData_t;

struct ExternOut_t
{
	char varName[MAX_VAR_NAME];
	signed int Address;

	struct ExternOut_t * nxt;
};
typedef struct ExternOut_t ExternOut_t;

#endif

