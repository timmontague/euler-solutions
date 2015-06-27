/*
 * A perfect number is a number for which the sum of its proper divisors is
 * exactly equal to the number. For example, the sum of the proper divisors of
 * 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.
 *
 * A number n is called deficient if the sum of its proper divisors is less than
 * n and it is called abundant if this sum exceeds n.
 *
 * As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest
 * number that can be written as the sum of two abundant numbers is 24. By
 * mathematical analysis, it can be shown that all integers greater than 28123
 * can be written as the sum of two abundant numbers. However, this upper limit
 * cannot be reduced any further by analysis even though it is known that the
 * greatest number that cannot be expressed as the sum of two abundant numbers
 * is less than this limit.
 *
 * Find the sum of all the positive integers which cannot be written as the sum
 * of two abundant numbers.
 */

#include <stdio.h>
#include <stdbool.h>

#define UPPER_BOUND 28124
char numbers[UPPER_BOUND];
char non_abundant_sums[UPPER_BOUND];

int sum_proper_divisors(int n) {
	int sum = 0;
	int i;
	for (i = 1; i < n; i++) {
		if (n % i == 0) {
			sum += i;
		}
	}
	return sum;
}

bool is_abundant(int n) {
	return n > 1 && sum_proper_divisors(n) > n;
}


int main(void) {
	unsigned int sum = 0;
	int i, j;
	// populate non_abundant_sums
	for (i = 0; i < UPPER_BOUND; i++) {
		non_abundant_sums[i] = 0;
	}
	for (i = 0; i < UPPER_BOUND; i++) {
		if (is_abundant(i)) {
			numbers[i] = 1;
			for (j = 0; j <= i && i+j < UPPER_BOUND; j++) {
				if (numbers[j]) {
					non_abundant_sums[i+j] = 1;
				}
			}
		} else {
			numbers[i] = 0;
		}
	}
	// sum numbers that are not sums of abundant numbers
	for (i = 0; i < UPPER_BOUND; i++) {
		if (!non_abundant_sums[i]) {
			sum += i;
		}
	}
	printf("%u\n", sum);
	return 0;
}
