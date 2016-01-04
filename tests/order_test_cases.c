/*
Test Cases for order
*/

#include "../number_theory.h"
#include <stdio.h>
#include <assert.h>

int main(void) {
	int primes1[] = {5, 0};
	int powers1[] = {1, 0};
	int primes2[] = {2, 0};
	int powers2[] = {4, 0};
	int primes3[] = {2, 3, 0};
	int powers3[] = {3, 1, 0};

	check(3, 5, 4, primes1, powers1);
	check(4, 5, 2, primes1, powers1);
	check(2, 5, 4, primes1, powers1);
	check(9, 16, 2, primes2, powers2);
	check(8, 16, -1, primes2, powers2);
	check(11, 24, 2, primes3, powers3);
}

int check(int a, int m, int r, int *primes, int *powers) {
	int z = order(a, m, primes, powers);
	printf("order(%d) (mod %d) = %d\n", a, m, z);

	assert(z == r);
}