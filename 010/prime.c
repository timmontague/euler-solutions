/*
 * Find the sum of all primes below 2 million
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX 2000000

int main(int argc, const char *argv[]) {
	bool numbers[MAX] = {0};
	uint64_t sum = 0;
	int i;

	// mark all numbers that are not prime as '1'
	numbers[0] = 1;
	numbers[1] = 1;
	i = 2;
	while (i < MAX) {
		// i is next prime
		int n = i;
		sum += n;
		// mark all multiplicands of i
		while(i < MAX) {
			numbers[i] = 1;
			i += n;
		}
		// find next prime
		while (n < MAX && numbers[n]) {
			n++;
		}
		i = n;
	}

	printf("%lld\n", sum);
	return 0;
}
