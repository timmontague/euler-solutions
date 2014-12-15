#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

/* 
 * Take the number 192 and multiply it by each of 1, 2, and 3:
 *
 *     192 × 1 = 192
 *     192 × 2 = 384
 *     192 × 3 = 576
 *
 * By concatenating each product we get the 1 to 9 pandigital,
 * 192384576. We will call 192384576 the concatenated product of 192
 * and (1,2,3)
 *
 * The same can be achieved by starting with 9 and multiplying by 1,
 * 2, 3, 4, and 5, giving the pandigital, 918273645, which is the
 * concatenated product of 9 and (1,2,3,4,5).
 *
 * What is the largest 1 to 9 pandigital 9-digit number that can be
 * formed as the concatenated product of an integer with (1,2,...,n)
 * where n > 1?
 */

bool is_pandigital(int n) {
    bool digits[9] = {false};
    int i;
    while (n) {
	if (n%10 == 0 || digits[(n%10)-1]) {
	    return false;
	}
	digits[(n%10)-1] = true;
	n /= 10;
    }
    for (i = 0; i < 9; i++) {
	if (!digits[i]) {
	    return false;
	}
    }
    return true;
}

/* Returns i*(1,..,n) concated together, or 0 if larger than 987654321 */
int concat_product(int i, int n) {
    int j;
    int ret = 0;
    for (j = 1; j <= n; j++) {
	int temp = i*j;
	while (temp) {
	    temp /= 10;
	    if (ret > 98765432 || ret < 0) {
		return 0;
	    }
	    ret *= 10;
	}
	ret += i*j;
    }
    if (ret > 987654321 || ret < 0) {
	return 0;
    }
    return ret;
}

int main(void) {
   int n, i, test;
   int largest = 0;
   for (i = 1; i < 10000; i++) {
       n = 2;
       test = concat_product(i,n);
       while(test) {
	   test = concat_product(i,n++);
	   if (test > largest && is_pandigital(test)) {
	       largest = test;
	   }
       }
   }
   printf("%d\n", largest);
   return 0;
}
