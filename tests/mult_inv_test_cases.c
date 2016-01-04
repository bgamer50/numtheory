/*
Test Cases for mult_inv
*/

#include "../number_theory.h"
#include <stdio.h>
#include <assert.h>

int main(void) {
	check(2, 3, 2);
	check(3, 26, 9);
	check(5, 2, 1);
	check(5, 4, 1);
}

int check(int a, int m, int r) {
	int z = mult_inv(a, m);
	printf("mult_inv(%d) (mod %d) = %d\n", a, m, z);
	assert(positive_residue(z, m) == r);
}