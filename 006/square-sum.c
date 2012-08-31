/*
 * Find the difference between the sum of squares of the first 100 natural
 * numbers and the square of the sum
 */
#include <stdio.h>
#include <math.h>
int main(int argc, const char *argv[]) {
	int i;
	unsigned long int sumofsquares = 0;
	unsigned long int squareofsum = 0;

	for (i = 1; i <= 100; i++) {
		sumofsquares += (unsigned long int)powl(i, 2);
		squareofsum += i;
	}
	squareofsum = (unsigned long int)powl(squareofsum, 2);
	printf("%ld - %ld = %ld\n", squareofsum, sumofsquares, squareofsum-sumofsquares);
	return 0;
}
