#include <stdio.h>
#include <string.h>
#include <assert.h>
/*
 * If the numbers 1 to 5 are written out in words: one, two, three, four, five,
 * then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
 *
 * If all the numbers from 1 to 1000 (one thousand) inclusive were written out
 * in words, how many letters would be used? 
 */

int count_ones(int n) {
    switch(n) {
	case 4:  // four
	case 5:  // five
	case 9:  // nine
	    return 4;
	case 1:  // one
	case 2:  // two
	case 6:  // six
	    return 3;
	case 3:  // three
	case 7:  // seven
	case 8:  // eight
	    return 5;
	default:
	    assert(0);
    }
}

int count_teens(int n) {
    switch(n) {
	case 10: // ten
	    return 3;
	case 11: // eleven
	case 12: // twelve
	    return 6;
	case 15: // fifteen
	case 16: // sixteen
	    return 7;
	case 13: // thirteen
	case 14: // fourteen
	case 18: // eighteen
	case 19: // nineteen
	    return 8;
	case 17: // seventeen
	    return 9;
	default:
	    assert(0);
    }
}

int count_tens(int n) {
    switch(n) {
	case 1: // ten
	    return 3;
	case 4: // forty
	case 5: // fifty
	case 6: // sixty
	    return 5;
	case 2: // twenty
	case 3: // thirty
	case 8: // eighty
	case 9: // ninety
	    return 6;
	case 7: // seventy
	    return 7;
	default:
	    assert(0);
    }
}

int count(int n) {
    int c = 0;
    if (n == 1000)
	return 11; // one thousand
    if (n < 10)
	return count_ones(n);
    if (n < 20)
	return count_teens(n);

    // hundreds place
    if (n / 100) {
	c += count_ones(n / 100);
	c += 7; // hundred
	n -= ((n/100)*100);
	if (n) {
	    c += 3; // and
	}
    }

    // tens place
    if (n / 10) {
	if (n < 20) {
	    c += count_teens(n);
	    n = 0;
	} else {
	    c += count_tens(n / 10);
	    n -= ((n/10)*10);
	}
    }
 
    // ones place
    if (n) {
	c += count_ones(n);
    }
    return c;
}

int main(void) {
    int c = 0;
    int i;
    for (i = 1; i <= 1000; i++) {
	c += count(i);
    }
    printf("%d\n", c);
    return 0;
}
