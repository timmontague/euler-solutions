/*
 * Starting with the number 1 and moving to the right in a clockwise direction a
 * 5 by 5 spiral is formed as follows:
 *
 * 21 22 23 24 25
 * 20  7  8  9 10
 * 19  6  1  2 11
 * 18  5  4  3 12
 * 17 16 15 14 13
 *
 * It can be verified that the sum of the numbers on the diagonals is 101.
 *
 * What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral
 * formed in the same way?
 */
#define SIZE 1001
#include <stdio.h>
int main(void) {
	unsigned int sum = 1; // include middle number '1'
	unsigned int i = 3; // start in first corner
	int skip = 1;
	while (i < SIZE*SIZE) {
		sum += i;
		i += skip+1;
		sum += i;
		i += skip+1;
		sum += i;
		i += skip+1;
		sum += i;
		skip+=2;
		i += skip+1;
	}
	printf("%u\n", sum);
	return 0;
}
