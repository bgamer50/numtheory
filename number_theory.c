#include "number_theory.h"
#include <math.h>
#include <stdlib.h>
/*The Chinese Remainder Theorem*/
/*
Somewhere, at some point I will have documentation of the CRT and how
it works, and what can be accomplished with it.  Unfortunately, for
now, I have nothing since my nice documentation got deleted.
*/

/*
Takes an integer i to decompose with the given moduli.  Returns NULL if
the moduli are not coprime.
*/
long *crt_decompose(long i, long* mods, unsigned int mods_length) {
	unsigned int k;
	long* decomp;
	if(!coprime_check(mods, mods_length))
		return NULL;

	decomp = malloc(sizeof(int) * mods_length);
	
	for(k = 0; k < mods_length; k++)
		decomp[k] = i % mods[k];

	return decomp;
}

/*
Takes an integer and reconstructs it using the power of the CRT.
eq, mods are such that x cong. eq[i] (mod mods[i])
*/
long crt_reconstruct(long* eq, long* mods, unsigned int mods_length) {
	long* n = malloc(sizeof(long) * mods_length);
	long n_product = 1;
	long val = 0;
	unsigned int k;
	if(sizeof(eq) != sizeof(mods) || !coprime_check(mods, mods_length))
		return -1;
	/*calculate N (n_product)*/
	for(k = 0; k < mods_length; k++)
		n_product *= mods[k];

	/*calculate N_k, solve modular equations*/
	for(k = 0; k < mods_length; k++) {
		n[k] = n_product / mods[k];
		val += n[k] * mult_inv(n[k], mods[k]) * eq[k];
	}

	/*return the final answer*/
	return val % n_product;
}

/*
Ensure that everything in the array is coprime.
*/
int coprime_check(long *a, unsigned int a_length) {
	int k, i;

	for(k = 0; k < a_length; k++)
		for(i = k + 1; i < a_length; i++)
			if(gcd(a[k], a[i]) != 1)
				return 0;
	return 1;
}

/*
Returns the gcd of a and b (uses the Euclidean algorithm)
*/
long gcd(long a, long b) {
	long t;
	/*swap a and b if a is smaller*/
	if(a < b) {
		t = a;
		a = b;
		b = t;
	}
	else if(a == b)
		return a;
	else if(b == 1)
		return 1;
	else if(b == 0)
		return a;

	return gcd(b, a % b);
}

/*
Returns the multiplicative inverse mod m of a.
Behavior undefined if no inverse exists.
*/
long mult_inv(long a, long m) {
	long s = 0, sP = 1;
	long r = m, rP = a;
	long q, tmp;

	while(r != 0) {
		q = rP / r;
		
		tmp = r;
		r = rP - q * r;
		rP = tmp;

		tmp = s;
		s = sP - q * s;
		sP = tmp;
	}
	return sP;
}

/*
Extended Eucliean Algorithm.  Returns the gcd of
a and b, and coefficients such that a * cA + b * cB = gcd(a, b).
Formatted as follows: [gcd, cA, cB]
*/
long *euclidean_ext(long a, long b) {
	long *arr = malloc(sizeof(long) * 3);
	int s = 0;
	int t = 1;
	int r = b;
	int q, tmp;

	arr[1] = 1;
	arr[2] = 0;
	arr[0] = a;

	while(r != 0) {
		q = arr[0] / r;
		
		tmp = r;
		r = arr[0] - q * r;
		arr[0] = tmp;

		tmp = s;
		s = arr[1] - q * s;
		arr[1] = tmp;

		tmp = t;
		t = arr[2] - q * t;
		arr[2] = tmp;
	}
	return arr;
}

/*
Converts a to an equivalent positive residue
mod m.
*/
long positive_residue(long a, long m) {
	while(a < 0)
		a += m;
	return a;
}

/*
Solves linear diophantine equations of the form
a*x + b*y = c.  Note that gcd(a, b) must divide c if
there is a solution to the equation.
Returns an array if the equation was solved
successfully.  Returns NULL if there is no solution.
Returned arrays are of the form [x0, c1, y0, c2] and
solutions are of the form x = x0 + c1*t, y = y0 +c2*t
where t is any integer.
*/
long *solve_linear_diophantine(long a, long b, long c) {
	long *arr = NULL;
	long *e = euclidean_ext(a, b);
	if(c % e[0] == 0) {
		arr = malloc(sizeof(long) * 4);
		arr[0] = e[1] * c / e[0];
		arr[2] = e[2] * c / e[0];
		arr[1] = b / e[0];
		arr[3] = -a / e[0];
	}

	return arr;
}

/*
Evaluates the legendre symbol (a/p).  Note that
p must be an odd prime.  Returns 1 if a is a
quadratic residue mod p, -1 if a is not a quadratic
residue mod p.  May fail in cases of overflow; in
this case behavior is undefined.
*/
int legendre(long a, long p) {
	long n;

	a = a % p;
	n = pow_mod(a, (p - 1) / 2, p);
	if(n != 1)
		return n - p;
	else
		return n;
}

/*
More reliable version of legendre that requires
that both numbers are prime.  Returns 1 if a is a
quadratic residue mod p, -1 if a is not a quadratic
residue mod p.  May fail in cases of overflow; in
this case behavior is undefined.
*/
int legendre_prime(long p, long q) {
	long n;
	int neg = 1;

	if(p < q) {
		if(p % 4 == 3 && q % 4 == 3)
			neg = -1;
		n = q;
		q = p;
		p = n;
	}

	p = p % q;
	n = pow_mod(p, (q - 1) / 2, q);
	if(n != 1)
		return neg * (n - q);
	else
		return neg * n;
}

/*
Computes the sigma function, which is
equal to the sum of positive divisors
of n.  Primes is formatted as follows:
[p1, p2...0]; Powers is formatted as
follows: [k1, k2...0] where n
= p1^k1 * p2^k2 * p3^k3...
*/
long sigma(long *primes, long *powers) {
	int k = 0;
	long s = 1;
	while(primes[k] > 0) {
		s *= ( pow(primes[k], powers[k] + 1) - 1) / (primes[k] - 1);
		k++;
	}

	return s;
}

/*
Computes the tau function, which is equal to
the number of positive divisors of n.  Powers
is formatted as follows: [k1, k2...0] where
n = p1^k1 * p2^k2...
*/
long tau(long *powers) {
	int k = 0;
	long t = 1;
	while(powers[k] > 0) {
		t *= powers[k] + 1;
		k++;
	}

	return t;
}

/*
Computes the phi function, which is equal
to the number of coprime numbers less
than n.  Primes is formatted as follows:
[p1, p2...0]; Powers is formatted as follows:
[k1, k2...0] where n = p1^k1 * p2^k2...
*/
long phi(long *primes, long *powers) {
	int k = 0;
	long p = 1;
	long l;
	while(primes[k] > 0) {
		l = pow(primes[k], powers[k]);
		p *= l - l / primes[k];
		k++;
	}

	return p;
}

/*
Solves linear congruence equations of the form
a*x cong. b (mod m). Returns 0 if no solution
exists.
*/
long solve_linear_congruence(long a, long b, long m) {
	long *s = solve_linear_diophantine(a, m, b);
	if(s == NULL)
		return 0;
	else
		return s[0];
}


/*
Finds the order of a mod m, provided gcd(a,m) = 1.
Primes and powers of m are formatted as in phi.  Returns
-1 if a and m are not coprime.
*/
long order(long a, long m, long *primes, long *powers) {
	long p;
	long d = gcd(a, m);
	int k;

	if(d != 1)
		return -1;
	
	p = phi(primes, powers);
	for(k = 1; k < p; k++)
		if(p % k == 0 && pow_mod(a, k, m) == 1)
			return k;
	return p;
}

/*
Finds a single primitive root mod m if one exists.
Primes and powers of m are formatted as in phi.
Returns -1 if there are no primitive roots.
*/
long primitive_root(long m, long *primes, long *powers) {
	unsigned long p, a;
	int k;
	unsigned int f = 0;

	p = phi(primes, powers);
	for(a = 2; a < m; a++) {
		if(gcd(a, m) == 1) {
			f = 0;
			for(k = 2; k < p; k++) {
				if(p % k == 0 && pow_mod(a, k, m) == 1) {
					f = 1;
					break;
				}
			}
			if(f == 0) {
				return a;
			}
		}
	}
	return -1;
}

/*
Finds all primitive roots mod m if any exist.
Primes and powers of m are formatted as in phi.
Returns NULL if there are no primitive roots.
Array is terminated by -1.
*/
long *all_primitive_roots(int m, int *primes, int *powers) {
	int k, i = 1;
	long p = phi(primes, powers);
	long *roots = malloc(sizeof(long) * 10);
	unsigned int arr_size = 10;

	roots[0] = primitive_root(m, primes, powers);
	if(roots[0] == -1) {
		free(roots);
		return NULL;
	}

	for(k = 2; k < p; k++) {
		if(gcd(k, p) == 1) {
			if(i == arr_size - 1) {
				roots = realloc(roots, sizeof(int) * (arr_size + 10));
				arr_size += 10;
			}
			roots[i] = pow_mod(roots[0], k, m);
			i++;
		}
	}

	if(i == arr_size - 1)
		roots = realloc(roots, sizeof(int) * (arr_size + 1));
	roots[i] = -1;

	return roots;
}

/*
Computes y^x mod m.  Used to reduce overflow.
*/
unsigned long pow_mod(unsigned long y, unsigned long x, unsigned long m) {
	unsigned long r = 1;
	if(x % 2 != 0) {
		r = y;
		x--;
	}

	while(x > 0) {
		r *= y * y;
		r %= m;
		x -= 2;
	}

	return r;
}
