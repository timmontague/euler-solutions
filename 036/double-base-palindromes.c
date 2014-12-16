#include <stdio.h>
/*
 * The decimal number, 585 = 1001001001 (binary), is palindromic in both bases.
 *
 * Find the sum of all numbers, less than one million, which are palindromic in
 * base 10 and base 2.
 *
 * (Please note that the palindromic number, in either base, may not include
 * leading zeros.)
 */
int nth_digit(int i, int n) {
    while(i--) {
	n /= 10;
    }
    return n%10;
}

int is_palindrome_d(int n) {
    int n_digits = 0;
    int temp = n;
    int i,j;
    while (temp) {
	n_digits++;
	temp /= 10;
    }
    i = 0;
    j = n_digits-1;
    while (i < j) {
	if (nth_digit(i,n) != nth_digit(j,n)) {
	    return 0;
	}
	i++;
	j--;
    }
    return 1;
}

int is_palindrome_b(int n) {
    int n_digits = 0;
    int temp = n;
    int i,j;
    while (temp) {
	n_digits++;
	temp >>= 1;
    }
    i = 0;
    j = n_digits-1;
    while (i < j) {
	if (((n >> i)&1) != ((n >> j)&1)) {
	    return 0;
	}
	i++;
	j--;
    }
    return 1;
}

int main(void) {
    int i;
    int sum = 0;
    for (i = 1; i < 1000000; i++) {
	if (is_palindrome_d(i) && is_palindrome_b(i)) {
	    sum+=i;
	}
    }
    printf("%d\n", sum);
    return 1;
}

