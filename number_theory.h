#if !defined(NUMBER_THEORY_H)
#define NUMBER_THEORY_H

/*Definitions and such*/
int *crt_decompose(int i, int *mods, int mods_length);

int crt_reconstruct(int *eq, int *mods, int mods_length);

int coprime_check(int* a, int a_length);

int mult_inv(int a, int m);

int gcd(int a, int b);

int *euclidean_ext(int a, int b);

int positive_residue(int a, int m);

#endif