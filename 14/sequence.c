#include <stdio.h>
#include <stdint.h>
int main(int argc, const char *argv[]) {
	uint32_t i;
	uint64_t n;
	uint32_t count;
	uint32_t max = 0;
	uint32_t maxi;
	for (i = 1; i < 1000000; i++) {
		n = (uint64_t)i;
		count = 1;
		while (n != 1) {
			if (n&1) { // n is odd
				n = n*3+1;
			} else {
				n /= 2;
			}
			count++;
		}
		if (count > max) {
			max = count;
			maxi = i;
			printf("%d\n", max);
		}
	}
	printf("%d\n", maxi);
	
	return 0;
}
