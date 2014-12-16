#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define N 10

/*
 * A permutation is an ordered arrangement of objects. For example, 3124 is one
 * possible permutation of the digits 1, 2, 3 and 4. If all of the permutations
 * are listed numerically or alphabetically, we call it lexicographic order. The
 * lexicographic permutations of 0, 1 and 2 are:
 *
 * 012   021   102   120   201   210
 *
 * What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4,
 * 5, 6, 7, 8 and 9?
 */

static long long *seen = NULL;
static int seenlen = 0;
static int maxseenlen = 0;
/* a is an array of integers with exactly 1 of every digit from 1 to N */
void add(char *a) {
    int i;
    long long n = 0;
    for (i = 0; i < N; i++) {
	n *= 10;
	n += a[i];
    }
    // add to list of seen sets
    seenlen++;
    if (seenlen > maxseenlen) {
	maxseenlen += 100000;
	seen = realloc(seen, sizeof(long long)*maxseenlen);
	if(!seen) {
	    perror("check");
	    exit(1);
	}
    }
    seen[seenlen-1] = n;
}

static int cmp(const void *a, const void *b) {
    long long a1, b1;
    a1 = *(long long*)a;
    b1 = *(long long*)b;
    if (a1 < b1) {
	return -1;
    } else if (a1 > b1) {
	return 1;
    } else {
	return 0;
    }
}


int main(void) {
    char array[N];
    /* generate all permutations of array using non-recursive implementation of
     * Heap's method */
    int i;
    char c[N];
    for (i = 0; i < N; i++) {
	c[i] = 0;
	array[i] = i;
    }
    add(array);
    for (i = 1; i < N; ) {
	if (c[i] < i) {
	    int j = i % 2 ? c[i] : 0;
	    int temp = array[j];
	    array[j] = array[i];
	    array[i] = temp;
	    c[i]++;
	    i = 1;
	    add(array);
	} else {
	    c[i] = 0;
	    i++;
	}
    }
    assert(seenlen > 1000000);
    qsort(seen, seenlen, sizeof(seen[0]), cmp);
    printf("%lld\n", seen[999999]);
    return 0;
}
