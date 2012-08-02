#include <stdio.h>
#include <stdbool.h>

// find the largest prime factor of 600851475143

bool isPrime(unsigned long int i) {
	unsigned long int n;
	for (n = 2; n <= i/2; n++) {
		if (i%n == 0)
			return false;
	}
	return true;
}
int main(int argc, const char *argv[]) {
	unsigned long int n = 600851475143;
	unsigned long int i = 2;
	while(!isPrime(n)) {
		if (isPrime(i) && n%i == 0) {
			n /= i;
			printf("%d\n", i);
		} else {
			i++;
		}
	}
	printf("%d\n", n);
	return 0;
}
