#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "../headers/lib.h"
#include "../headers/fizzbuzz.h"
#include "../headers/primes.h"
#include "../headers/wordinator.h"

int failed = 0;

#define TEST(name) void name()
#define RUN_TEST(name) printf("\n\033[1m%s\n\033[0m", #name); name()

#define ASSERT(expr) if (!(expr)) { failed = 1; printf("\033[0;31mFAIL: %s\n\033[0m", #expr); } else { printf("\033[0;32mPASS: %s\n\033[0m", #expr); }

// Original definition of ASSERT_STR_EQ():
// #define ASSERT_STR_EQ(str1, str2) ASSERT(strcmp(str1, str2) == 0)

#define ASSERT_STR_EQ(str1, str2) if (!(strcmp(str1, str2) == 0)) { \
	failed = 1; \
	printf("\033[0;31mFAIL: '%s' == '%s'\n\033[0m", str1, str2); \
} else { \
	printf("\033[0;32mPASS: '%s' == '%s'\n\033[0m", str1, str2); \
}

TEST(test_add) {
	ASSERT(add(1, 2) == 3);
	ASSERT(add(0, 0) == 0);
	ASSERT(add(-1, -1) == -2);
	ASSERT(add(5, 5) == 5);
}

TEST(test_string_assert) {
	ASSERT_STR_EQ("hello", "hello");
	ASSERT_STR_EQ("hello", "goodbye");
}

TEST(test_fizzbuzz) {
	int num = 5;
	int bufflen = get_buffer_length(num);
	char buffer5[bufflen];
	fizzbuzz(num, buffer5, bufflen);
	ASSERT_STR_EQ(buffer5, "1, 2, fizz, 4, buzz.")
	num = 15;
	bufflen = get_buffer_length(num);
	char buffer15[bufflen];
	fizzbuzz(num, buffer15, bufflen);
	ASSERT_STR_EQ(buffer15, "1, 2, fizz, 4, buzz, fizz, 7, 8, fizz, buzz, 11, fizz, 13, 14, fizzbuzz.")
}

TEST(test_primes) {
	ASSERT(get_primes(1000) == 168);
	ASSERT(get_primes(10000) == 1229);
	ASSERT(get_primes(100000) == 9592);
	//ASSERT(get_primes(1000000) == 78498);
}

TEST(test_wordinator) {
	char word[256] = {};
	wordinate(400, word, 256);
	ASSERT_STR_EQ(word, "four hundred")
	wordinate(54321, word, 256);
	ASSERT_STR_EQ(word, "fifty four thousand, three hundred and twenty one")
	wordinate(617, word, 256);
	ASSERT_STR_EQ(word, "six hundred and seventeen");
	wordinate(245309, word, 256);
	ASSERT_STR_EQ(word, "two hundred and forty five thousand, three hundred and nine");
	wordinate(3880256, word, 256);
	ASSERT_STR_EQ(word, "three million, eight hundred and eighty thousand, two hundred and fifty six");
	wordinate(7563872501, word, 256);
	ASSERT_STR_EQ(word, "seven billion, five hundred and sixty three million, eight hundred and seventy two thousand, five hundred and one");
}

int main() {
	RUN_TEST(test_add);
	RUN_TEST(test_string_assert);
	RUN_TEST(test_fizzbuzz);
	RUN_TEST(test_primes);
	RUN_TEST(test_wordinator);
	return failed;
}