/*
 * Find sum of all even fibonacci numbers below 4,000,000
 */
#include <stdio.h>
int main(int argc, const char *argv[]) {
	int prev = 1;
	int fib = 2;
	int temp;
	int sum = 0;
	while (fib < 4000000) {
		if (fib%2 == 0) { // if even
			sum += fib;
		}
		temp = fib;
		fib += prev;
		prev = temp;
	}
	printf("%d\n", sum);
	return 0;
}
