Assembler: Assembler.o Parser.o SideFunctions.o Output.o InstructionsReader.o RIJinstructions.o SecondTransitionHelper.o SecondTransition.o Errors.o
	gcc -g -Wall -ansi -pedantic Assembler.o Parser.o SideFunctions.o Output.o InstructionsReader.o RIJinstructions.o SecondTransitionHelper.o SecondTransition.o Errors.o -o Assembler

Assembler.o: Assembler.c Parser.h
	gcc -c -Wall -ansi -pedantic Assembler.c -o Assembler.o

Parser.o: Parser.c Parser.h
	gcc -c -Wall -ansi -pedantic Parser.c -o Parser.o

SideFunctions.o: SideFunctions.c SideFunctions.h
	gcc -c -Wall -ansi -pedantic SideFunctions.c -o SideFunctions.o

Output.o: Output.c Output.h
	gcc -c -Wall -ansi -pedantic Output.c -o Output.o

InstructionsReader.o: InstructionsReader.c InstructionsReader.h
	gcc -c -Wall -ansi -pedantic InstructionsReader.c -o InstructionsReader.o

RIJinstructions.o: RIJinstructions.c RIJinstructions.h
	gcc -c -Wall -ansi -pedantic RIJinstructions.c -o RIJinstructions.o

SecondTransitionHelper.o: SecondTransitionHelper.c SecondTransitionHelper.h
	gcc -c -Wall -ansi -pedantic SecondTransitionHelper.c -o SecondTransitionHelper.o

SecondTransition.o: SecondTransition.c SecondTransition.h
	gcc -c -Wall -ansi -pedantic SecondTransition.c -o SecondTransition.o

Errors.o: Errors.c Errors.h
	gcc -c -Wall -ansi -pedantic Errors.c -o Errors.o

