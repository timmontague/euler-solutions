#include <stdio.h>
#include <stdint.h>
#include <gmp.h>

// find sum of digits in 100!
int main(int argc, const char *argv[]) {
	mpz_t n;
	uint64_t sum = 0;

	mpz_init(n);
	mpz_fac_ui(n, 100); // n = 100!

	while (mpz_sgn(n) != 0) { // while n != 0
		sum+=mpz_fdiv_q_ui(n, n, 10); // return remainder of n/10
	}
	printf("%lld\n", sum);
	return 0;
}
