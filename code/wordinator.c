#include <stdio.h>

int get_num_digits(long number) {
	int num_digits = 0;

	while (number > 0) {
		number = number / 10;
		num_digits++;
	}

	return num_digits;
}

int get_next_number(long number) {
	if ((number / 10) == 0) {
		return number;
	} else {
		return number % ((number / 10) * 10);
	}
}

void wordinate_2() {
	long number = 10526;

	int mod = 10;
	int place = 1;

	while (number > 0) {
		int digit = number % mod;
		// first pass gives the 1s digit, then the 10s, 100s, etc.
		// search:  c insert character into char array
		// want to start from the 1s position here instead of the largest position for simplicity
		mod *= 10;
		place *= 10;
	}
}

void wordinate(long number, char *buffer, int bufflen) {

	int num_digits = get_num_digits(number);

	printf("Total digits in %ld is %d\n", number, num_digits);

	char digits[num_digits + 1];

	long temp = number;
	digits[num_digits] = '\0';
	for (int i = num_digits - 1; i >= 0; i--) {
		digits[i] = get_next_number(temp);
		//printf("digit[%d] = %d\n", i, digits[i]);
		temp = temp / 10;
	}

	int check;
	for (int i = 0; i < num_digits; i++) {
		if ((num_digits - i) % 3 == 1 || (num_digits - i) % 3 == 0) {
			if (digits[i] == 1) { check = snprintf(buffer, bufflen, "one"); buffer += check; bufflen -= check; }
			else if (digits[i] == 2) { check = snprintf(buffer, bufflen, "two"); buffer += check; bufflen -= check; }
			else if (digits[i] == 3) { check = snprintf(buffer, bufflen, "three"); buffer += check; bufflen -= check; }
			else if (digits[i] == 4) { check = snprintf(buffer, bufflen, "four"); buffer += check; bufflen -= check; }
			else if (digits[i] == 5) { check = snprintf(buffer, bufflen, "five"); buffer += check; bufflen -= check; }
			else if (digits[i] == 6) { check = snprintf(buffer, bufflen, "six"); buffer += check; bufflen -= check; }
			else if (digits[i] == 7) { check = snprintf(buffer, bufflen, "seven"); buffer += check; bufflen -= check; }
			else if (digits[i] == 8) { check = snprintf(buffer, bufflen, "eight"); buffer += check; bufflen -= check; }
			else if (digits[i] == 9) { check = snprintf(buffer, bufflen, "nine"); buffer += check; bufflen -= check; }
		}
		if ((num_digits - i) % 3 == 2) {	// tens
			if (i > 0 && (digits[i] > 0 || digits[i + 1] > 0)) { check = snprintf(buffer, bufflen, " and "); buffer += check; bufflen -= check; }
			if (digits[i] == 1) {
				if (digits[i + 1] == 0) { check = snprintf(buffer, bufflen, "ten"); buffer += check; bufflen -= check; }
				else if (digits[i + 1] == 1) { check = snprintf(buffer, bufflen, "eleven"); buffer += check; bufflen -= check; }
				else if (digits[i + 1] == 2) { check = snprintf(buffer, bufflen, "twelve"); buffer += check; bufflen -= check; }
				else if (digits[i + 1] == 3) { check = snprintf(buffer, bufflen, "thirteen"); buffer += check; bufflen -= check; }
				else if (digits[i + 1] == 4) { check = snprintf(buffer, bufflen, "fourteen"); buffer += check; bufflen -= check; }
				else if (digits[i + 1] == 5) { check = snprintf(buffer, bufflen, "fifteen"); buffer += check; bufflen -= check; }
				else if (digits[i + 1] == 6) { check = snprintf(buffer, bufflen, "sixteen"); buffer += check; bufflen -= check; }
				else if (digits[i + 1] == 7) { check = snprintf(buffer, bufflen, "seventeen"); buffer += check; bufflen -= check; }
				else if (digits[i + 1] == 8) { check = snprintf(buffer, bufflen, "eighteen"); buffer += check; bufflen -= check; }
				else if (digits[i + 1] == 9) { check = snprintf(buffer, bufflen, "nineteen"); buffer += check; bufflen -= check; }
				i++;
			}
			else if (digits[i] == 2) { check = snprintf(buffer, bufflen, "twenty"); buffer += check; bufflen -= check; }
			else if (digits[i] == 3) { check = snprintf(buffer, bufflen, "thirty"); buffer += check; bufflen -= check; }
			else if (digits[i] == 4) { check = snprintf(buffer, bufflen, "forty"); buffer += check; bufflen -= check; }
			else if (digits[i] == 5) { check = snprintf(buffer, bufflen, "fifty"); buffer += check; bufflen -= check; }
			else if (digits[i] == 6) { check = snprintf(buffer, bufflen, "sixty"); buffer += check; bufflen -= check; }
			else if (digits[i] == 7) { check = snprintf(buffer, bufflen, "seventy"); buffer += check; bufflen -= check; }
			else if (digits[i] == 8) { check = snprintf(buffer, bufflen, "eighty"); buffer += check; bufflen -= check; }
			else if (digits[i] == 9) { check = snprintf(buffer, bufflen, "ninety"); buffer += check; bufflen -= check; }

			if (num_digits - i > 0 && digits[i] > 0 && digits[i + 1] > 0) { check = snprintf(buffer, bufflen, " "); buffer += check; bufflen -= check; }
		} else if ((num_digits - i) % 3 == 0) {	// hundreds
			check = snprintf(buffer, bufflen, " hundred");
			buffer += check;
			bufflen -= check;
		}
		if ((num_digits - i) % 3 == 1) {
			float group = (num_digits - i) / 3.0;
			if (group <= 2.0 && group > 1.0) { check = snprintf(buffer, bufflen, " thousand"); buffer += check; bufflen -= check; }
			if (group <= 3.0 && group > 2.0) { check = snprintf(buffer, bufflen, " million"); buffer += check; bufflen -= check; }
			if (group <= 4.0 && group > 3.0) { check = snprintf(buffer, bufflen, " billion"); buffer += check; bufflen -= check; }
		}
		if ((num_digits - i) % 3 == 1) {
			if (i < (num_digits - 1)) { check = snprintf(buffer, bufflen, ", "); buffer += check; bufflen -= check; }
		}
	}
}
