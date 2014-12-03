#include <stdio.h>

int n_cubes(int layer, int w, int h, int d) {
    int ret;
    // fill faces
    ret = 2*w*h + 2*w*d + 2*h*d;
    // fill stairs between faces
    ret += (layer-1)*(4*w + 4*h + 4*d);
    // fill corners
    ret += 4*(layer-2)*(layer-1);
    return ret;
}

int main(void) {
    int h, w, d;
    int n = 0;
    int max;
    int c = 4;
    int maxn = 0;
    while (n != 147) {
	n = 0;
	c += 2;
	max = ((c-2)/4)+1;
	for (h = 1; h < max; h++) {
	    for (w = h; w < max; w++) {
		for (d = w; d < max; d++) {
		    int layer = 1;
		    int ncubes;
		    do {
			ncubes = n_cubes(layer, w, h, d);
			layer++;
		    } while (ncubes < c);
		    if (ncubes == c) {
			n++;
		    } else if (layer == 1) {
			break;
		    }
		}
	    }
	}
	if (n > maxn) {
	    printf("c: %d n: %d\n", c, n);
	    maxn = n;
	}
    }
    printf("c: %d n: %d\n", c, n);
    return 0;
}
