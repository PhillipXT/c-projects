#include <stdio.h>

// ==================================================
// EXAMPLE 1:
// ==================================================

// This version won't work at all, because you can't define char[].  The []
// is part of the variable, not the type, ie. char a[].  Functions in C cannot
// return a string or an array.

/*
TEST_1(test_concat) {
	char result[] = string_concat_1(result, "Hello", "world");
	ASSERT_STR_EQ(result, "Hello world");
}

char[] string_concat_1(char a[], char b[]) {
	char buffer[12] = {0};
	sprintf(buffer, "%s %s", a, b);
	return buffer;
}
*/

// ==================================================
// EXAMPLE 2:
// ==================================================

// This version is syntactically correct, but it still won't work.  In the function,
// buffer is filled with the data we want, but it gets put on the stack and then
// that memory space is invalidated when the function returns.  That memory space
// may be used by other processes which then alter the data.
TEST_2(test_concat) {
	char *result = string_concat_2("Hello", "world");
	ASSERT_STR_EQ(result, "Hello world");
}

char *string_concat_2(char *a, char *b) {
	char buffer[12] = {0};
	sprintf(buffer, "%s %s", a, b);
	return buffer;
}

// ==================================================
// EXAMPLE 3:
// ==================================================

// This version declares the result variable in the caller, passes it to the
// function, and it gets filled in, making it available to the caller.  The
// problem with this version is when you pass strings that are longer than the
// variable we declared, in which case we will get a buffer overflow error.
TEST_3(test_concat) {
	char result[12] = {0};
	string_concat_3(result, "Hello", "world");
	ASSERT_STR_EQ(result, "Hello world");
}

// C has a concept called string-to-pointer decay, which means that when you
// pass a string, it changes it to actually pass a pointer instead.  So the
// signature we are using here:
//		char string_concat_3(char buffer[], char a[], char b[])
// actually becomes:
//		char string_concat_3(char *buffer, char *a, char *b)
char string_concat_3(char buffer[], char a[], char b[]) {
	sprintf(buffer, "%s %s", a, b);
}

// ==================================================
// EXAMPLE 4: (RECOMMENDED METHOD)
// ==================================================

// This version uses snprintf(), which takes a buffer size, instead of sprintf().
// The snprintf() function also returns data about how much memory it used.  This
// is the preferred approach to string concatenation.
TEST_4(test_concat) {
	char result[12] = {0};
	string_concat_4(result, sizeof(result), "Hello", "world");
	ASSERT_STR_EQ(result, "Hello world");
}

char string_concat_4(char buffer[], size_t bufflen, char a[], char b[]) {
	snprintf(buffer, bufflen, "%s %s", a, b);
}

// ==================================================
// EXAMPLE 5:
// ==================================================

// This version uses the heap instead of the stack to store the result.  Heap
// memory must be deallocated manually, so it doesn't disappear when the function
// has completed.  We can free() the memory after we're done with it, but the
// problem with this method is that the caller needs to know the function
// used malloc() and that we need to clean up the memory afterwards.
TEST_5(test_concat) {
	char *result = string_concat_5("Hello", "world");
	ASSERT_STR_EQ(result, "Hello world");
	free(result);
}

#include <stdlib.h>
#include <string.h>
char *string_concat_5(char a[], char b[]) {
	// Size: +1 for the space we're adding, and +1 for the null terminator.
	char *result = malloc((strlen(a) + 1 + strlen(b) + 1) * sizeof(char));
	sprintf(result, "%s %s", a, b);
	return result;
}
