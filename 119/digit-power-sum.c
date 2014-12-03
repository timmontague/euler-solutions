#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

long long sum_of_digits(long long n) {
    long long sum = 0;
    while(n) {
	lldiv_t d = lldiv(n,10ull);
	sum += d.rem;
	n = d.quot;
    }
    return sum;
}

#define MAX_FOUND 40
int main(void) {
    int i;
    long long a, b;
    long long found[MAX_FOUND];
    int nfound = 0;
    for (a = 1; a < 1000; a++) {
	for (b = 1; b < 1000; b++) {
	    long long ex = b;
	    long long x = a;
	    // calculate a^b
	    while (--ex) {
		// bail if we might overflow
		if (x & 0xFFC0000000000000) {
		    goto too_big;
		}
		x *= a;
	    }
	    if (x > 9 && sum_of_digits(x) == a) {
		// add to list of found numbers (sorted)
		for (i = 0; i < nfound; i++) {
		    if (x < found[i]) {
			long long temp = found[i];
			found[i] = x;
			x = temp;
		    }
		}
		found[nfound] = x;
		nfound++;
		assert(nfound < MAX_FOUND);
	    }
	}
too_big:
	;
    }
    for (i = 0; i < nfound; i++) {
	printf("a_%d: %lld\n", i+1, found[i]);
    }
    return 0;
}
