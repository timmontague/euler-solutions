#include <stdio.h>
#include <assert.h>

unsigned long n_cubes(unsigned long layer, unsigned long w, unsigned long h, unsigned long d) {
    int ret;
    // fill faces
    ret = 2*w*h + 2*w*d + 2*h*d;
    // fill stairs between faces
    ret += (layer-1)*(4*w + 4*h + 4*d);
    // fill corners
    ret += 4*(layer-2)*(layer-1);
    return ret;
}

#define START_N	(1000000)
#define MAXN 	(1000000)

int main(void) {
    unsigned long h, w, d;
    unsigned long min = 1;
    unsigned long max = 20;
    int ncubes[MAXN] = {0};
    int done = 0;
    while (done == 0) {
	for (h = min; h <= max; h++) {
	    for (w = h; w <= max; w++) {
		for (d = w; d <= max; d++) {
		    int layer = 1;
		    unsigned long n;
		    while (1) {
			n = n_cubes(layer, w, h, d);
			layer++;
			if (n < START_N+MAXN && n > START_N) {
			    ncubes[n-START_N]++;
			    if (ncubes[n-START_N] == 1000 || ncubes[n-START_N] == 1001) {
				printf("c: %d n: %lu max:%lu\n", ncubes[n-START_N], n, max);
			    }
			} else {
			    break;
			}
		    }
		}
	    }
	}
	max += 20;
	min += 20;
	if (max+START_N > 6*MAXN) {
	    printf("min: %lu max: %lu\n", min, max);
	    done = 1;
	}
    }
    return 0;
}
