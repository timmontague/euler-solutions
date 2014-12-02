#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define N 9

void print_set(int *a) {
    int i;
    for (i = 0; i < N && a[i]; i++) {
	printf("%d ", a[i]);
    }
    printf("\n");
}

#define CACHE_SIZE (0x3ffffff)
#define EMPTY (0)
#define	PRIME (1)
#define NOT_PRIME (2)
/* Assumes that n is greater than 0 */
bool is_prime(int n) {
    static char cache[CACHE_SIZE] = {0};
    int cachen;
    int i, max;
    if ((n&(~3)) == 0) { // if n is 1,2 or 3
	return (n != 1); // return false for 1, and true for 2 or 3
    }
    if ((n&1) == 0) { // if n is an even number
	return false;
    }
    // lookup value in cache
    cachen = n>>1;
    if (cachen < CACHE_SIZE) {
	if (cache[cachen] == NOT_PRIME) {
	    return false;
	} else if (cache[cachen] == PRIME) {
	    return true;
	} else {
	    // calculate
	    max = sqrt(n)+1;
	    for (i = 3; i < max; i++) {
		if (n%i == 0) {
		    cache[cachen] = NOT_PRIME;
		    return false;
		}
	    }
	    cache[cachen] = PRIME;
	    return true;
	}
    }
    // calculate
    max = sqrt(n)+1;
    for (i = 3; i < max; i++) {
	if (n%i == 0)
	    return false;
    }
    return true;
}

/* *a is a null terminated array of integers */
bool is_set_prime(int *a) {
    while (*a) {
	if (!is_prime(*a))
	    return false;
	a++;
    }
    return true;
}

/* returns a set for a given code
 * *a is an array of integers with exactly 1 of every digit from 1 to N
 * code is an integer from 0 to (1<<(N-1))-1 (a number with N-1 bits set), each
 * 1 indicates a break between sets */

int *generate_set(char *a, int code) {
    static int sets[N+1];
    int i, n = 0;
    sets[0] = a[0];
    for (i = 1; i < N; i++) {
	if (code&1) {
	    n++;
	    sets[n] = 0;
	}
	code >>= 1;
	sets[n] *= 10;
	sets[n] += a[i];
    }
    sets[n+1] = 0;
    return sets;
}

#define SEEN_SIZE (100000)
/* a is an array of integers with exactly 1 of every digit from 1 to N */
int check_all_sets(char *a) {
    static int seen[SEEN_SIZE];
    static int seenlen = 0;
    int ret = 0;
    int code;
    int max_code = (1<<(N-1))-1;
    for (code = 0; code <= max_code; code++) {
	int *set = generate_set(a, code);
	if (is_set_prime(set)) {
	    // check if set was already seen
	    int *s = set;
	    int h, l, n;
	    n = 1;
	    // calcuate product of every number in set
	    while (*s) {
		n *= *s;
		s++;
	    }
	    // binary search for the product
	    l = 0;
	    h = seenlen-1;
	    while (h >= l) {
		int mid = ((h-l)/2)+l;
		if (seen[mid] == n) {
		    goto found;
		} else if (seen[mid] < n) {
		    l = mid + 1;
		} else {
		    h = mid - 1;
		}
	    }
	    // add to list of seen sets
	    seenlen++;
	    while (l < seenlen) {
		int temp = seen[l];
		seen[l] = n;
		n = temp;
		l++;
	    }
	    
	    ret++;
	}
found:
	;
    }
    return ret;
}

int main(void) {
    char array[N];
    /* generate all permutations of array using non-recursive implementation of
     * Heap's method */
    int ret = 0;
    int i;
    char c[N];
    for (i = 0; i < N; i++) {
	c[i] = 0;
	array[i] = i+1;
    }
    ret += check_all_sets(array);
    for (i = 1; i < N; ) {
	if (c[i] < i) {
	    int j = i % 2 ? c[i] : 0;
	    int temp = array[j];
	    array[j] = array[i];
	    array[i] = temp;
	    c[i]++;
	    i = 1;
	    ret += check_all_sets(array);
	} else {
	    c[i] = 0;
	    i++;
	}
    }
    printf("number of all-prime sets: %d\n", ret);
    return 0;
}
