#if !defined(NUMBER_THEORY_H)
#define NUMBER_THEORY_H

/*Definitions and such*/
long *crt_decompose(long i, long *mods, unsigned int mods_length);

long crt_reconstruct(long *eq, long *mods, unsigned int mods_length);

int coprime_check(long* a, unsigned int a_length);

long mult_inv(long a, long m);

long gcd(long a, long b);

long *euclidean_ext(long a, long b);

long positive_residue(long a, long m);

long *solve_linear_diophantine(long a, long b, long c);

int legendre(long a, long p);

int legendre_prime(long p, long q);

long tau(long *powers);

long phi(long *primes, long *powers);

long sigma(long *primes, long *powers);

long solve_linear_congruence(long a, long b, long m);

long order(long a, long m, long *primes, long *powers);

long primitive_root(long m, long *primes, long *powers);

long *all_primitive_roots(long m, long *primes, long *powers);

unsigned long pow_mod(unsigned long y, unsigned long x, unsigned long m);

/*
Converts a to a positive least residue mod m
*/
#define positive_least_residue(a, m) ( positive_residue( (a), (m) ) % (m) )

#endif