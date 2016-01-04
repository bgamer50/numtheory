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

int *solve_linear_diophantine(int a, int b, int c);

int legendre(long a, long p);

int tau(int *powers);

int phi(int *primes, int *powers);

int sigma(int *primes, int *powers);

int solve_linear_congruence(int a, int b, int m);

int order(int a, int m, int *primes, int *powers);

int primitive_root(int m, int *primes, int *powers);

int *all_primitive_roots(int m, int *primes, int *powers);

/*
Converts a to a positive least residue mod m
*/
#define positive_least_residue(a, m) ( positive_residue( (a), (m) ) % (m) )

#endif