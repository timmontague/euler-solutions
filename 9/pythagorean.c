/**
 *
 * A Pythagorean triplet is a set of three natural numbers, a < b < c, for
 * which,
 * a^2 + b^2 = c^2
 *
 * For example, 3^2 + 4^2 = 9 + 16 = 25 = 52.
 *
 * There exists exactly one Pythagorean triplet for which a + b + c = 1000.
 * Find the product abc.
 */
 
#include <stdio.h>
#include <math.h>
int main(int argc, const char *argv[]) {
	int a, b, c;

	for (c = 0; c < 1000; c++) {
		for (b = 0; b < c; b++) {
			for (a = 0; a < b; a++) {
				if (a+b+c == 1000 && pow(a,2) + pow(b,2) == pow(c,2)) {
					printf("%d\n", a*b*c);
					return 0;
				}
			}
		}
	}
	return 0;
}
