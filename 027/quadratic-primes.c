#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

// find the quadratic sequence with the most sequential prime numbers of the
// form x^2+ax+b where -1000>a>1000 and -1000>b>1000

bool isPrime(int i) {
	int n;
	if (i < 0)
		return false;
	for (n = 2; n <= i/2; n++) {
		if (i%n == 0)
			return false;
	}
	return true;
}
int main(int argc, const char *argv[]) {
	int a, b;
	int count;
	int n;
	int i;
	int maxa, maxb;
	int max = 0;
	for (a = -999; a < 1000; a++) {
		for (b = -999; b < 1000; b++) {
			i = 0;
			count = -1;
			do {
				n = (i*i)+(a*i)+b;
				count++;
				i++;
			} while (isPrime(n));
			if (count > max) {
				max = count;
				maxa = a;
				maxb = b;
				printf("a:%d b:%d count:%d n:%ld\n", a, b, count, n);
			}
		}
	}
	printf("a:%d b:%d count:%d a*b:%d\n", maxa, maxb, max, maxa*maxb);

	return 0;
}
