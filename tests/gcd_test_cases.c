/*
Test Cases for GCD
*/

#include "../number_theory.h"
#include <stdio.h>

int main(void) {
	printf("gcd(10, 11) = %d\n", gcd(10, 11));
	printf("gcd(11, 11) = %d\n", gcd(11, 11));
	printf("gcd(5, 10) = %d\n", gcd(5, 10));
	printf("gcd(10, 5) = %d\n", gcd(10, 5));
	printf("gcd(61, 11) = %d\n", gcd(61, 11));
	printf("gcd(11, 61) = %d\n", gcd(11, 61));
	printf("gcd(4, 61) = %d\n", gcd(4, 61));
	printf("gcd(12, 36) = %d\n", gcd(12, 36));
	printf("gcd(12, 18) = %d\n", gcd(12, 18));
	printf("gcd(144, 2) = %d\n", gcd(144, 2));
	printf("gcd(128, 33) = %d\n", gcd(128, 33));
	printf("gcd(99, 33) = %d\n", gcd(99, 33));
	printf("gcd(99, 66) = %d\n", gcd(99, 66));
}