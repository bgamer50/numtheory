/*
Test Cases for solve_linear_diophantine
*/

#include "../number_theory.h"
#include <stdio.h>
#include <assert.h>

int main(void) {
	check(3, 4, 5);
	check(4, 8, 16);
}

int check(int a, int b, int c, int *r) {
	int *z = solve_linear_diophantine(a, b, c);
	printf("Solution to %dx + %dy = %d is x = %d + %dt; y = %d + %dt\n", a, b, c, z[0], z[1], z[2], z[3]);
}