#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/*
 * The number, 1406357289, is a 0 to 9 pandigital number because it is made up
 * of each of the digits 0 to 9 in some order, but it also has a rather
 * interesting sub-string divisibility property.
 *
 * Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note
 * the following:
 *
 *  d2d3d4=406 is divisible by 2
 *  d3d4d5=063 is divisible by 3
 *  d4d5d6=635 is divisible by 5
 *  d5d6d7=357 is divisible by 7
 *  d6d7d8=572 is divisible by 11
 *  d7d8d9=728 is divisible by 13
 *  d8d9d10=289 is divisible by 17
 *
 * Find the sum of all 0 to 9 pandigital numbers with this property.
 */

#define N 10

bool check(char *a) {
    int i;
    int divisors[] = {2,3,5,7,11,13,17};
    for (i = 1; i < 8; i++) {
	int n = a[i]*100 + a[i+1]*10 + a[i+2];
	if (n % divisors[i-1] != 0) {
	    return false;
	}
    }
    return true;
}

unsigned long long get_num(char *a) {
    int i;
    unsigned long long sum = 0;
    for (i = 0; i < N; i++) {
	sum *= 10;
	sum += a[i];
    }
    return sum;
}
int main(void) {
    unsigned long long sum = 0;
    char array[N];
    /* generate all permutations of array using non-recursive implementation of
     * Heap's method */
    int i;
    char c[N];
    for (i = 0; i < N; i++) {
	c[i] = 0;
	array[i] = i;
    }
    if (check(array)) {
	sum += get_num(array);
    }
    for (i = 1; i < N; ) {
	if (c[i] < i) {
	    int j = i % 2 ? c[i] : 0;
	    int temp = array[j];
	    array[j] = array[i];
	    array[i] = temp;
	    c[i]++;
	    i = 1;
	    if (check(array)) {
		sum += get_num(array);
	    }
	} else {
	    c[i] = 0;
	    i++;
	}
    }
    printf("%llu\n", sum);
    return 0;
}
