#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <error.h>

#define N 9

/* Returns 1 if a*b == c and c hasn't been seen before */
int check(int a, int b, int c) {
    static int *seen = NULL;
    static int seenlen = 0;
    static int maxseenlen = 0;
    int h, l;
    if (a*b != c) {
	return 0;
    }
    // binary search for c
    l = 0;
    h = seenlen-1;
    while (h >= l) {
	int mid = ((h-l)/2)+l;
	if (seen[mid] == c) {
	    goto found;
	} else if (seen[mid] < c) {
	    l = mid + 1;
	} else {
	    h = mid - 1;
	}
    }
    // add to list of seen sets
    seenlen++;
    if (seenlen > maxseenlen) {
	maxseenlen += 1000;
	seen = realloc(seen, sizeof(int)*maxseenlen);
	if(!seen) {
	    perror("check");
	    exit(1);
	}
    }
    while (l < seenlen) {
	int temp = seen[l];
	seen[l] = c;
	c = temp;
	l++;
    }
    return 1;
found:
    return 0;
}

/* Check a pandigital array to see if any division of it will satisfy a*b=c,
 * returns the sum of unique products */
int check_set(char *array) {
    int i,j;
    int ret = 0;
    for (i = 1; i <= 7; i++) {
	for (j = 1; j < 8-i; j++) {
	    int a,b,c,k;
	    a=b=c=0;
	    for (k = 0; k < i; k++) {
		a *= 10;
		a += array[k];
	    }
	    for (k = i; k < i+j; k++) {
		b *= 10;
		b += array[k];
	    }
	    for (k = i+j; k < 9; k++) {
		c *= 10;
		c += array[k];
	    }
	    if(check(a,b,c)) {
		ret += c;
	    }
	}
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
    ret += check_set(array);
    for (i = 1; i < N; ) {
	if (c[i] < i) {
	    int j = i % 2 ? c[i] : 0;
	    int temp = array[j];
	    array[j] = array[i];
	    array[i] = temp;
	    c[i]++;
	    i = 1;
	    ret += check_set(array);
	} else {
	    c[i] = 0;
	    i++;
	}
    }
    printf("%d\n", ret);
    return 0;
}
