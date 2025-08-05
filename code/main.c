#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../headers/fizzbuzz.h"
#include "../headers/primes.h"
#include "../headers/rosetta.h"
#include "../headers/wordinator.h"

// Write a program to read input from the user, and print a statement if the input was the letter Q.
// Compile the program:
//		gcc -O0 -g -o main main.c
// Now edit the binary executable.  First, use objdump to print the assembly code:
//		objdump -d main > main.asm
// Review the code and figure out a way to change it to always print the statement no matter the input
// Useful tools:
//		The radare2 Git repo:	https://github.com/radareorg/radare2?tab=readme-ov-file
// 		Hex editor (radare2):	https://rada.re/n/radare2.html
//		Instruction list:		https://www.felixcloutier.com/x86/
//		Conversion tool:		https://shell-storm.org/online/Online-Assembler-and-Disassembler/?opcodes=90&arch=x86-64&endianness=little&baddr=0x00000000&dis_with_addr=True&dis_with_raw=True&dis_with_ins=True#disassembly
// Command line utilities:
//		ldd ./myprogram			Get a list of libraries linked into your project

// Data types				Size            Signed Range  Unsigned Range
// ==============           =======     ================  ==============
//		char				1 byte		   -127     +128      0      256
//		short				2 bytes		-32,767  +32,767      0  +65,535
//		int					2 bytes		-32,767  +32,767      0  +65,535
//		long				4 bytes		  ~-2bn    ~+2bn      0    ~+4bn
//		long long			8 bytes		 ~-2^63   ~+2^63      0   ~+2^64
//		* These sizes may differ per machine

// Format specifiers:
//		%d - signed decimal integer :: 99, -42
//		%f - decimal floating point :: 3.14159, -0.01
//		%s - string :: Hello
//		%% - literal %
//		%p - pointer address
//		\n - newline character

void get_input() {
	puts("Press any key:");
	int key = getchar();

	if (key == 'Q') {
		puts("You got it!");	// puts() automatically adds \n to the end of the line
	}

	printf("You entered: %c (%d||%x)\n", key, key, key);
}

int main(int argc, char **argv) {
	
	printf("First arg is %s\n", argv[0]);

	if (argc > 1) {
		for (int i = 1; i < argc; i++) {
			printf("Checking arg %d: [%s]\n", i, argv[i]);
			if (strcmp(argv[i], "/?") == 0) {
				puts("Available flags:");
				puts("\t--getchar\tTakes input from the user and displays the value.");
				puts("\t-f [number]\tDisplays fizzbuzz up to the specified number");
				puts("\t-p [number]\tCounts the number of primes in the specified number");
				puts("\t-r [string]\tDisplays the values of each character in the text string");
				puts("\t-w [number]\tDisplays the text interpretation of the specified number");
			} else if (strcmp(argv[i], "--getchar") == 0) {
				get_input();
			} else if (strcmp(argv[i], "-f") == 0) {
				if (argc > i + 1) {
					int num = atoi(argv[i + 1]);
					if (num > 0) {
						int bufflen = get_buffer_length(num);
						printf("Buffer length is %d\n", bufflen);
						char buffer[bufflen];
						fizzbuzz(num, buffer, bufflen);
						puts(buffer);
					} else {
						puts("You must specify a valid number!");
					}
					i += 1;
				} else {
					puts("You must specify a number with the -f option.");
				}
			} else if (strcmp(argv[i], "-p") == 0) {
				if (argc > i + 1) {
					int num = atoi(argv[i + 1]);
					if (num > 0) {
						printf("Number of primes found is %d\n", get_primes(num));
					} else {
						puts("You must specify a number with the -p option.");
					}
					i += 1;
				} else {
					puts("You must specify a number with the -p option.");
				}
			} else if (strcmp(argv[i], "-r") == 0) {
				if (argc > i + 1) {
					rosetta(argv[i + 1]);
					i += 1;
				} else {
					puts("You must specify text with the -r option.");
				}
			} else if (strcmp(argv[i], "-w") == 0) {
				if (argc > i + 1) {
					int num = atoi(argv[i + 1]);
					char buffer[256] = {};
					wordinate(num, buffer, 256);
					printf("Your number is %s\n", buffer);
					i += 1;
				} else {
					puts("You must specify a number with the -w option.");
				}
			}
		}
	}

	return 0;
}
