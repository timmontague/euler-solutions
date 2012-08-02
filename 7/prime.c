/*
 * Find the 1001st prime number
 */
#include <stdio.h>
#include <stdbool.h>

bool isPrime(unsigned int i) {
	unsigned int n;
	for (n = 2; n <= i/2; n++) {
		if (i%n == 0)
			return false;
	}
	return true;
}
int main(int argc, const char *argv[]) {
	unsigned int n = 0;
	unsigned int i = 1;
	while(n < 10001) {
		if (isPrime(++i)) {
			n++;
		}
	}
	printf("%d\n", i);
	return 0;
}
