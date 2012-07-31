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
	printf("%d - %d = %d\n", squareofsum, sumofsquares, squareofsum-sumofsquares);
	return 0;
}
