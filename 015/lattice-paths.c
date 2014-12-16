#include <stdio.h>
#include <gmp.h>
/*
 * Starting in the top left corner of a 2×2 grid, and only being able to move to
 * the right and down, there are exactly 6 routes to the bottom right corner.
 *
 * How many such routes are there through a 20×20 grid?
 */

int main(void) {
    /* The answer is found using multisubsets. Assume 21 distinct types of
     * items, and choosing 20 of them. The answer is the number of ways to
     * choose the items using repetition.
     *
     * The equation is ((n k)) = (n+k-1 k) = (n+k-1)!/(k!^2)
     * This becomes:
     * ((21 20) = (21+20-1 20) = (40 20) = 40!/(20!^2)
     */
    mpz_t numerator, denominator, answer;
    mpz_init(numerator);
    mpz_init(denominator);
    mpz_init(answer);
    mpz_fac_ui(numerator, 40); // 40!
    mpz_fac_ui(denominator, 20); // 20!
    mpz_pow_ui(denominator, denominator, 2); // 20!^2
    mpz_cdiv_q(answer, numerator, denominator); // 40!/20!^2
    gmp_printf("answer: %Zd\n", answer);
    return 0;
}
