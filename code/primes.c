#include <stdio.h>
#include <stdlib.h>

int get_primes(int num) {
	
	//printf("Processing primes of %d\n", num);

	if (num > 1) {
		int primes[num - 1];
		for (int i = 0; i < (num - 1); i++) {
			primes[i] = i + 2;
			//printf("Array item %d is %d\n", i, primes[i]);
		}
		for (int i = 2; i * i <= num; i++) {
			//printf("Removing multiples of %d\n", i);
			for (int j = i - 2; j < (num - 1); j++) {
				if (primes[j] != i && primes[j] != 0 && primes[j] % i == 0) {
					//printf("Removing value %d\n", primes[j]);
					primes[j] = 0;
				}
			}
		}
		int prime_count = 0;
		for (int i = 0; i < (num - 1); i++) {
			if (primes[i] != 0) {
				prime_count += 1;
			}
		}
		
		return prime_count;
	} else {
		puts("Please enter a number greater than 1.");
		return 0;
	}
}