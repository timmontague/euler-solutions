#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <gmp.h>

// find the unit fraction with the longest repeating cycle of decimal digits
int main(int argc, const char *argv[]) {
	mpf_t n;
	mpf_t d;
	int i;
	char s[10000];
	char *p;

	int offset, len;
	int slen;
	int count;

	int max = 0;

	mpf_init2(d, 19510L); // lots of precision!
	mpf_init_set_d(n, 1); // n = 1

	for (i = 0; i < 1000; i++) {
		mpf_add_ui(n, n, 1); // n++
		mpf_ui_div(d, 1, n); // d = 1/n

		gmp_sprintf(s, "%.Ff", d);

		// ignore if less than 50 digits long
		slen = strlen(s);
		if (slen < 50) {
			continue;
		}

		// start and end of string, don't offset too far
		for (offset = slen-1; offset > slen/3; offset--) {
			// start with smallest possible string
			for (len = 1; len < (slen-4)/2 && len+offset < slen; len++) {
				count = 1;
				while (memcmp(s+offset, s+offset-(count*len), len) == 0) {
					count++;
				}
				if (count > 4) {
					if (len > max) {
						max = len;
						gmp_printf("%Ff ", n);
						printf(":%d %s\n", len, s);
					}
					goto NEXT;
				}
			}
		}
NEXT:;

	}
	return 0;
}
