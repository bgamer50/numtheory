/*
Test Cases for tau, phi, and sigma
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

	check(5, 2, 4, 6, primes1, powers1);
	check(16, 5, 8, 31, primes2, powers2);
	check(24, 8, 8, 60, primes3, powers3);
}

int check(int a, int r1, int r2, int r3, int *primes, int *powers) {
	int z1 = tau(powers);
	int z2 = phi(primes, powers);
	int z3 = sigma(primes, powers);

	printf("tau(%d) = %d; phi(%d) = %d; sigma(%d) = %d\n", a, z1, a, z2, a, z3);

	assert(z1 == r1);
	assert(z2 == r2);
	assert(z3 == r3);
}