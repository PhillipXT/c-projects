#include <stdio.h>

int add(int a, int b) {
	return a + b;
}

// Currently only works for numbers >= 0
int get_digit_length(int i) {
	int len = 0;
	
	if (i == 0) { return 1; }
	
	while (i > 0) {
		i /= 10;
		len += 1;
	}

	return len;
}

void concat(char buffer[], size_t bufflen, char a[], char b[]) {
	snprintf(buffer, bufflen, "%s%s", a, b);
}
