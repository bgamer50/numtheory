/*
Test Cases for legendre and legendre_prime
*/

#include "../number_theory.h"
#include <stdio.h>
#include <assert.h>

int main(void) {
	check(5, 3, -1);
	check(4, 7, 1);
	check2(5, 31, 1);
}

int check(int a, int p, int r) {
	int z = legendre(a, p);
	if(z == 1)
		printf("%d is a quadratic root mod %d\n", a, p);
	else if(z == -1)
		printf("%d is not a quadratic root mod %d\n", a, p);
	else
		printf("Error! %d\n", z);

	assert(z == r);
}

int check2(int a, int p, int r) {
	int z = legendre_prime(a, p);
	if(z == 1)
		printf("%d is a quadratic root mod %d\n", a, p);
	else if(z == -1)
		printf("%d is not a quadratic root mod %d\n", a, p);
	else
		printf("Error! %d\n", z);

	assert(z == r);
}