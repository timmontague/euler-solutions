/*
 * A palindromic number reads the same both ways. The largest palindrome made
 * from the product of two 2-digit numbers is 9009 = 91 × 99.
 *
 * Find the largest palindrome made from the product of two 3-digit numbers.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
bool isPalindrome(int);

int main(int argc, const char *argv[])
{
	int i, j;
	int max = 0;
	for (i = 999; i >= 0; i--) {
		for (j = 999; j >= 0; j--) {
			if (isPalindrome(i*j)) {
				if (i*j > max) {
					max = i*j;
					printf("%d\n", max);
				}
			}
		}
	}
	
	return 0;
}

bool isPalindrome(int i) {
	char buf[6]; // max number is 6 digits long (998001)
	int len = 0;
	int temp;
	// convert to base 10
	while (i) {
		temp = i;
		i /= 10;
		buf[len++] = temp - (i * 10);
	}
	// check if palindrome
	temp = 0;
	len--;
	while (len > temp) {
		if (buf[len--] != buf[temp++]) {
			return false;
		}
	}
	return true;
}
