/*
Test Cases for coprime_check
*/

#include "../number_theory.h"
#include <stdio.h>
#include <assert.h>

int main(void) {
	int arr1[] = {2, 3, 5, 7};
	int arr2[] = {2, 3, 5, 7, 6};
	int arr3[] = {5, 7, 15, 15, 15};
	int arr4[] = {29, 37, 41, 53};
	int arr5[] = {29, 37, 41, 53, 2};
	int arr6[] = {29, 37, 41, 53, 2, 27};

	check(arr1, 1, 4);
	check(arr2, 0, 5);
	check(arr3, 0, 5);
	check(arr4, 1, 4);
	check(arr5, 1, 5);
	check(arr6, 1, 6);
}

int check(int *arr, int r, int l) {
	int z = coprime_check(arr, l);
	if(z == 0)
		printf("Not Coprime.\n");
	else
		printf("Coprime.\n");
	
	assert(z == r);
}