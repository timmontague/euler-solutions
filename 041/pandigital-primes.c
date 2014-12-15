#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/* 
 * We shall say that an n-digit number is pandigital if it makes use of all the
 * digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is
 * also prime.
 *
 * What is the largest n-digit pandigital prime that exists?
 */

/* Assumes that n is greater than 0 */
bool is_prime(int n) {
    int i, max;
    if ((n&(~3)) == 0) { // if n is 1,2 or 3
	return (n != 1); // return false for 1, and true for 2 or 3
    }
    if ((n&1) == 0) { // if n is an even number
	return false;
    }
    // calculate
    max = sqrt(n)+1;
    for (i = 3; i < max; i++) {
	if (n%i == 0)
	    return false;
    }
    return true;
}

/* Converts array of digits into integer, returns 0 if not prime, or integer if
 * is prime */
int check_array(char *a, int len) {
    int n = 0;
    while (len--) {
	n = n*10 + a[len];
    }
    if(is_prime(n)) {
	return n;
    }
    return 0;
}

int main(void) {
    char array[9];
    int largest = 0;
    int i, n, temp;
    char c[9];
    for (n = 1; n < 10; n++) {
	/* generate all permutations of array using non-recursive implementation of
	 * Heap's method */
	for (i = 0; i < n; i++) {
	    c[i] = 0;
	    array[i] = i+1;
	}
	temp = check_array(array, n);
	if (temp > largest) {
	    largest = temp;
	}
	for (i = 1; i < n; ) {
	    if (c[i] < i) {
		int j = i % 2 ? c[i] : 0;
		temp = array[j];
		array[j] = array[i];
		array[i] = temp;
		c[i]++;
		i = 1;
		temp = check_array(array, n);
		if (temp > largest) {
		    largest = temp;
		}
	    } else {
		c[i] = 0;
		i++;
	    }
	}
    }
    printf("largest: %d\n", largest);
    return 0;
}
