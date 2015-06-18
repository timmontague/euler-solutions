/*
 * A truncatable prime is a prime number that remains a prime number if any
 * number of digits are removed from the right side of the number, and from the
 * left side of the number.
 *
 * Find the sum of the only 11 truncatable primes
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
bool *numbers = NULL;
uint32_t max = 0;

#define PRIME 0
#define NOT_PRIME 1

void increase_size() {
	uint32_t i;
	numbers = realloc(numbers, max+SIEVE_INCREASE);
	if (!numbers) {
		perror("increase");
		exit(1);
	}
	// initialize numbers array
	memset(numbers+max, PRIME, SIEVE_INCREASE);
	for (i = 2; i < max;) {
		// i is a prime, mark all it's multipliers
		int n = i;
		while (n < max) {
			n += i;
		}
		while (n < max+SIEVE_INCREASE) {
			numbers[n] = NOT_PRIME;
			n += i;
		}
		// find next prime
		i++;
		while (i < max && numbers[i] == NOT_PRIME) {
			i++;
		}
	}
	max += SIEVE_INCREASE;
}

bool is_truncatable_prime(uint32_t n) {
	uint32_t i = n;
	if (n < 10) {
		return false;
	}
	assert (n < max);
	// remove digits from right
	while (i) {
		if (numbers[i] == NOT_PRIME) {
			//printf("not prime %u\n", i);
			return false;
		}
		i = i/10;
	}
	// remove digits from left
	i = n;
	while (i) {
		if (numbers[i] == NOT_PRIME) {
			return false;
		}
		// remove most significant digit
		i = i % ((int)pow(10,(int)log10(i)));
	}
	return true;
}

int main(int argc, const char *argv[]) {
	uint64_t sum = 0;
	uint32_t i;
	int number_truncatable = 0;

	// initialize numbers array
	increase_size();

	// mark all numbers that are not prime as '1'
	numbers[0] = NOT_PRIME;
	numbers[1] = NOT_PRIME;
	i = 2;
	while (number_truncatable < 11) {
		// i is next prime
		int n = i;
		if (is_truncatable_prime(i)) {
			sum += n;
			printf("Truncatable: %u\n", i);
			number_truncatable++;
		}
		// mark all multiplicands of i
		i += n;
		while(i < max) {
			numbers[i] = NOT_PRIME;
			i += n;
		}
		// find next prime
		n++;
		while (n < max && numbers[n] == NOT_PRIME) {
			n++;
		}
		i = n;
		if (i >= max) {
			increase_size();
		}
	}

	printf("sum: %lld\n", sum);
	printf("n: %d\n", number_truncatable);
	return 0;
}
