// Reference: https://www.0de5.net/stimuli/a-reintroduction-to-programming/essentials/just-enough-c-to-have-fun

// === INCLUDES ===
#include <stdio.h>
#include <string.h>

#include "lib.c"
// The contents of `lib.c` are inlined into this file.
// Note that including `.c` files in this way is typically bad practice - use headers instead.

// === FUNCTIONS ===
int mul(int a, int b) {
	int result = a * b;
	return result;
}

// Recursion
int fib(int n) {
	if (n <= 1) {
		return n;
	}
	return fib(n - 1) + fib(n - 2);
}

// === PRINTING ===
void printing() {
	printf("3 * 4 = %d\n", mul(3, 4));
	printf("Fibonacci number 10 is %d\n", fib(10));
	// Quick specifier reference:
	// %d - signed decimal integer (e.g. 99, -42)
	// %f - decimal floating point  (e.g. 3.14, -0.01)
	// %s - string (e.g. "hello")
	// %% - literal % (e.g. %)
	// %p - pointer address (if given "hello" will print something like 0x7ffeefbff718)
	// \n - newline character, NOT automatically added to printf
}

// === LOOPS ===
void looping() {
	// You can use puts to print strings without values interpolated (auto adds the \n)
	puts("Counting down from 100 by 7s:");

	int c = 100;
	while (c > 0) {
		printf("%d ", c);
		c = c - 7;
	}
	puts("");

	puts("Counting up from 0 by 7s:");

	for (int i = 0; i < 100; i += 7) {
		printf("%d ", i);
		// break: exit a loop early
		// continue: skip the rest of the current iteration
	}
	puts("");
}

// === CONDITIONALS ===
void conditionals() {
	puts("Fizzbuzzing up to 20:");

	for (int i = 1; i <= 20; i++) {
		if (i % 15 == 0) {
			printf("Fizzbuzz ");
		} else if (i % 3 == 0) {
			printf("Fizz ");
		} else if (i % 5 == 0) {
			printf("Buzz ");
		} else {
			printf("%d ", i);
		}
	}
	puts("");

	// Logical operators:
	if (1 && !0 || 1) {
		puts("We made it!");
	}

	// Comparison operators:
	if (1 == 1 && 2 != 1 && 2 > 1 && 1 < 2 && 1 <= 1 && 2 >= 1) {
		puts("We made it again!");
	}
}

// === BASIC DATA TYPES ===
void data_types() {
	int integer = 42;
	float decimal = 3.14;
	char character = 'a';

	printf("size of char = %ld\n", sizeof(char));
	printf("size of short = %ld\n", sizeof(short));
	printf("size of int = %ld\n", sizeof(int));
	printf("size of long = %ld\n", sizeof(long));
	printf("size of long long = %ld\n", sizeof(long long));

	size_t whatever = 100;
	// This type is essentially "an unsigned integer big enough to store the size
	// of, or reference to, any object in memory on this system".
}

// === ARRAYS & STRINGS ===
void arrays_and_strings() {
	// C arrays & strings are a lot more basic than the lists you may be used to.
	// C strings are arrays of characters, terminated by a null character '�'.

	char string[6] = "hello"; // 6 characters, including the null terminator
	int numbers1[5]; // This allocates the memory for 5 ints but does not clear it.
	int numbers2[] = {1, 2, 3, 4, 5}; // This allocates the memory for 5 ints and initialises them.
}

// === STRUCTS ===
struct Person {
	char name[50];
	int height;
};

void structs() {
	struct Person me = {"Kay", 176};
	struct Person you = {.height = 180, .name = "Someone"};

	printf("Person %s, height %dcm\n", me.name, me.height);
	printf("Person %s, height %dcm\n", you.name, you.height);
}

// === MAIN FUNCTION ===
// main(int argc, char **argv)		> Generally more cross-platform compatible
// main(int argc, char *argv[])		> Gets interpreted by the compiler as **argv
int main(int argc, char **argv) {
	if (argc > 1) {
		printf("Hello, %s!\n", argv[1]);
	} else {
		puts("No greeting for you!");
	}

	printing();
	looping();
	conditionals();
	data_types();
	arrays_and_strings();
	structs();

	// Printing coloured blocks to the terminal window:
	//		\033[	Escape sequence for ANSI escape codes
	//		1		Sets the text attribute to bold
	//		31		Sets the text colour to red (from the ANSI colour code table)
	//		\033[0m	Sets the text colour to default
    printf("\033[1;31m+++++++++++++++\033[0m\n");
	// https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
	printf("\033[48;2;%d;%d;%dmTHIS IS A COLOURED BLOCK\033[0m\n", 128, 48, 48);
}