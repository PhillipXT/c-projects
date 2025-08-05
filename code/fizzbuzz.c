#include <stdio.h>

#include "../headers/lib.h"

char snprintf_success(int check, int bufflen) {
	return check >= 0 && check < bufflen;
}

int get_buffer_length(int count) {
	int buffer_length = 0;

	// Get the length of each item, which may be 'fizz', 'buzz', 'fizzbuzz', or a number
	for (int i = 1; i < (count + 1); i++) {
		if (i % 15 == 0) { buffer_length += 8; }
		else if (i % 5 == 0) { buffer_length += 4; }
		else if (i % 3 == 0) { buffer_length += 4; }
		else { buffer_length += get_digit_length(i); }
	}
	buffer_length += count - 1;			// Add one space for a comma after each item except the last
	buffer_length += count;				// Add one space after each entry, plus period at the end
	return buffer_length + 1;			// Add one for the null terminator
}

void fizzbuzz(int max, char *buffer, int bufflen) {
	for (int i = 1; i <= max; i++) {
		
		int check = 0;

		if (i % 15 == 0) {
			check = snprintf(buffer, bufflen, "fizzbuzz");
		} else if (i % 3 == 0) {
			check = snprintf(buffer, bufflen, "fizz");
		} else if (i % 5 == 0) {
			check = snprintf(buffer, bufflen, "buzz");
		} else {
			check = snprintf(buffer, bufflen, "%d", i);
		}

		if (!snprintf_success(check, bufflen)) { return; }

		buffer += check;
		bufflen -= check;

		if (i < max) {
			check = snprintf(buffer, bufflen, "%s", ", ");
			if (!snprintf_success(check, bufflen)) { return; }
			buffer += check;
			bufflen -= check;
		}
	}

	snprintf(buffer, bufflen, "%s", ".");
}
