#include <stdio.h>
#include <stdlib.h>

int main() {
	char *string = "Hello";
	// I am not sure what &string points to here.  It prints an address, but an address to what?
	printf("Pointers: %p %p %p\n", string, &string, &string[0]);
	char **string_array = malloc(sizeof(char *) * 3);
	string_array[0] = "Hello,";
	string_array[1] = "world";
	string_array[2] = "!";
	printf("Pointers: %p > %p\n", *string_array, string_array);
	printf("%s %s%s\n", string_array[0], string_array[1], string_array[2]);
	printf("%p %p %p\n", &string_array[0], &string_array[1], &string_array[2]);
	return 0;
}