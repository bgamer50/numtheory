/*
Test Cases for primitive_root and all_primitive_roots
*/

#include "../number_theory.h"
#include <stdio.h>
#include <assert.h>

int main(void) {
	int primes1[] = {2, 3, 0};
	int powers1[] = {2, 1, 0};
	int *r1 = NULL;

	int primes2[] = {13, 0};
	int powers2[] = {1, 0};
	int r2[] = {2, 6, 7, 11, -1};

	int primes3[] = {23, 2, 0};
	int powers3[] = {1, 1, 0};
	int r3[] = {5, 7, 11, 15, 17, 19, 21, 33, 37, 43, -1};

	check(12, primes1, powers1, r1);
	check(13, primes2, powers2, r2);
	check(46, primes3, powers3, r3);
}

int check(int a, int *primes, int *powers, int *r) {
	int *z = all_primitive_roots(a, primes, powers);

	int k = 0;
	if(z == NULL) {
		printf("No primitive roots for %d\n", a);
		assert(r == NULL);
	}
	else {
		printf("Primitive roots of %d: ", a);
		while(z[k] != -1) {
			printf("%d\t", z[k]);
			k++;
		}
		printf("\n");

		printf("Primitive roots of %d: ", a);
		k = 0;
		while(r[k] != -1) {
			printf("%d\t", r[k]);
			k++;
		}
		printf("\n");
	}
}