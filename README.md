**Overview**

This Assembler project translates assembly code written in a custom assembly language into machine code. The assembler is implemented in C, performing a two-pass process that parses labels, instructions, and produces three specific output files:

-   **.ob**: Contains the machine code.
-   **.ent**: Lists entry labels and corresponding addresses.
-   **.ext**: Lists external labels and their addresses.

**File Structure**

-   **Assembler.c**: The main driver of the program.
-   **Parser.c/h**: Handles parsing of the assembly source file.
-   **SideFunctions.c/h**: Auxiliary functions supporting various operations.
-   **Output.c/h**: Handles writing to output files.
-   **InstructionsReader.c/h**, **RIJinstructions.c/h**, **SecondTransitionHelper.c/h**, **SecondTransition.c/h**: Specialize in reading and interpreting different instructions.
-   **Errors.c/h**: Handles error collection and reporting.

**How to Compile and Run**

1.  Make sure all the required files are in the same directory.
2.1.  Compile the project using the command:

    gcc -o Assembler main.c parse.c ...
2.2. Use the makefile
3.  Run the compiled Assembler with your **.as** file:

    ./Assembler inputfile.as

**Output**

The program will generate the following files based on the input:

-   **inputfile.ob**: Machine code representation.
-   **inputfile.ent**: Entry labels and addresses.
-   **inputfile.ext**: External labels used and their addresses.

**Error Handling**

Errors will be reported with line numbers and specific error messages to facilitate debugging.

**Dependencies**

No external dependencies other than standard C libraries.

**Contact**

Roy Ohana – roei141105@gmail.com
