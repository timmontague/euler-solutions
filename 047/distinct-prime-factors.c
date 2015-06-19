/*
 * The first two consecutive numbers to have two distinct prime factors are:
 *  14 = 2 × 7
 *  15 = 3 × 5
 * The first three consecutive numbers to have three distinct prime factors are:
 *  644 = 2² × 7 × 23
 *  645 = 3 × 5 × 43
 *  646 = 2 × 17 × 19.
 * Find the first four consecutive integers to have four distinct prime factors.
 * What is the first of these numbers?
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <error.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define SIEVE_INCREASE 1000
#define PRIME 0
#define NOT_PRIME 1
typedef struct _prime_sieve_t {
	bool *numbers;
	size_t n_numbers;
	uint32_t max_prime;
} prime_sieve_t;
prime_sieve_t prime_sieve = { .numbers = NULL, .n_numbers = 0, .max_prime = 2 };


void increase_size() {
	uint32_t i;
	prime_sieve.numbers = realloc(prime_sieve.numbers, prime_sieve.n_numbers+SIEVE_INCREASE);
	if (!prime_sieve.numbers) {
		perror("increase");
		exit(1);
	}
	// initialize numbers array
	memset(prime_sieve.numbers+prime_sieve.n_numbers, PRIME, SIEVE_INCREASE);
	if (prime_sieve.n_numbers == 0) {
		prime_sieve.numbers[0] = NOT_PRIME;
		prime_sieve.numbers[1] = NOT_PRIME;
		prime_sieve.numbers[2] = PRIME;
	}
	for (i = 2; i <= prime_sieve.max_prime;) {
		// i is a prime, mark all it's multipliers
		int n = i;
		while (n < prime_sieve.n_numbers) {
			n += i;
		}
		while (n < prime_sieve.n_numbers+SIEVE_INCREASE) {
			prime_sieve.numbers[n] = NOT_PRIME;
			n += i;
		}
		// find next prime
		i++;
		while (i < prime_sieve.max_prime && prime_sieve.numbers[i] == NOT_PRIME) {
			i++;
		}
	}
	prime_sieve.n_numbers += SIEVE_INCREASE;
}

bool is_prime(int n) {
	if (n < 2) {
		return false;
	}
	while (n > prime_sieve.max_prime || n > prime_sieve.n_numbers) {
		int i = prime_sieve.max_prime;
		// find next prime
		i++;
		while (i < prime_sieve.n_numbers && prime_sieve.numbers[i] == NOT_PRIME) {
			i++;
		}
		if (i >= prime_sieve.n_numbers) {
			increase_size();
		} else {
			prime_sieve.max_prime = i;
			// mark all multiplicands of the new largest prime found
			i += prime_sieve.max_prime;
			while(i < prime_sieve.n_numbers) {
				prime_sieve.numbers[i] = NOT_PRIME;
				i += prime_sieve.max_prime;
			}
		}
	}
	return prime_sieve.numbers[n] == PRIME;
}

int next_prime(int n) {
	while (!is_prime(++n));
	return n;
}

int n_distinct_prime_factors(int i) {
	int count = 0;
	int n;
	if (is_prime(i)) {
		return 0;
	}
	// check each prime number starting with 2
	for (n = 2; i > 1; n = next_prime(n)) {
		if (i % n == 0) {
			count++;
			while (i % n == 0) {
				i = i/n;
			}
		}
	}
	return count;
}

#define GOAL 4
int main(int argc, const char *argv[]) {
	bool done = false;
	int i, n;

	i = 1;
	while (!done) {
		for (n = 0; n < GOAL; n++) {
			if (n_distinct_prime_factors(i+n) == GOAL) {
			} else {
				break;
			}
		}
		if (n == GOAL) {
			printf("%d\n", i);
			done = true;
		}
		i += n+1;
	}
	return 0;
}
