/*
 * Sum all numbers below 1000 that are multiples of 3 and 5
 */
#include <stdio.h>
int main(int argc, const char *argv[]) {
	int sum = 0;
	int i;
	for (i = 0; i < 1000; i++) {
		if (i%5 == 0 || i%3 == 0)
			sum += i;
	}
	printf("%d\n",sum);
	return 0;
}
