/*
Test Cases for euclidean_ext
*/

#include "../number_theory.h"
#include <stdio.h>
#include <assert.h>

int main(void) {
	check(2, 3, 1);
	check(3, 27, 3);
	check(9, 27, 9);
	check(15, 25, 5);
	check(8, 27, 1);
	check(6, 19, 1);
	check(19, 6, 1);
	check(29, 37, 1);
}

int check(int a, int b, int r) {
	int *z = euclidean_ext(a, b);
	printf("extended_euc(%d, %d) = %d; %d; %d\n", a, b, z[0], z[1], z[2]);
	assert(z[0] == r);
	if(r == 1)
		assert(z[1] * a + z[2] * b == 1);
}