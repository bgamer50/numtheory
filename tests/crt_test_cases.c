/*
Test Cases for crt_decompose and crt_reconstruct
*/

#include "../number_theory.h"
#include <stdio.h>
#include <assert.h>

int main(void) {
	int mods1[] = {3, 5, 7};
	int mods2[] = {29, 31, 43, 37, 101};

	check(41, mods1, 3);
	check(2048, mods2, 5);
	check(4096, mods1, 3);
}

int check(int n, int *mods, int mods_length) {
	int *decomp = crt_decompose(n, mods, mods_length);
	int z = crt_reconstruct(decomp, mods, mods_length);
	int p = 1, k;
	
	printf("%d is reconstructed as %d\n", n, z);

	for(k = 0; k < mods_length; k++)
		p *= mods[k];
	assert(positive_residue(z, p) == n % p);
}