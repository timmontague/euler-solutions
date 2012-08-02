/*
 * 2520 is the smallest number that can be divided by each of the numbers from 1
 * to 10 without any remainder.
 *
 * What is the smallest positive number that is evenly divisible by all of the
 * numbers from 1 to 20?
 */

#include <stdio.h>
#include <stdbool.h>

// checks to see if i is evenly divisible by all number 1-20
// only have to check 20, 19, 18, 17, 16, 15, 14, 13, 12, 11
bool isDivisible (int n) {
	int i;
	for (i = 11; i <= 20; i++) {
		if (n % i != 0)
			return false;
	}
	return true;
}
int main(int argc, const char *argv[])
{
	int i = 0;
	for (;;) {
		if (isDivisible(++i)) {
			printf("%d\n", i);
			return 0;
		}
	}
	return 0;
}
