/*
Test Cases for solve_linear_congruence
*/

#include "../number_theory.h"
#include <stdio.h>
#include <assert.h>

int main(void) {
	check(4, 1, 5, 4);
	check(10, 2, 7, 3);
}

int check(int a, int b, int m, int r) {
	int z = solve_linear_congruence(a, b, m);
	printf("Solution to %dx cong. %d (mod %d) is x = %d\n", a, b, m, z);
	assert(positive_least_residue(z, m) == r);
}