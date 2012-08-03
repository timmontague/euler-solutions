/*
 * Find the sum of all numbers which are equal to the sum of the factorial of
 * their digits.
 *
 * Note: as 1! = 1 and 2! = 2 are not sums they are not included.
 */
#include <stdio.h>
int main(int argc, const char *argv[]) {
	int fac [10] = {
		1,
		1,
		2,
		6,
		24,
		120,
		720,
		5040,
		40320,
		362880
	};
	int i;
	int sum = 0;;
	int tempi;
	int tempsum;
	// 9,999,999 is an upperbound (sum of factorial of digits is only 2,540,160)
	for (i = 10; i < 9999999; i++) {
		tempsum = 0;
		tempi = i;
		while (tempi > 0) {
			tempsum += fac[tempi%10];
			tempi /= 10;
		}
		if (tempsum == i) {
			sum += i;
		}
	}
	printf("%d\n", sum);
	
	return 0;
}
