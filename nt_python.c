#include <Python.h>
#include "number_theory.h"

/*
GCD Definition
*/
static PyObject *numtheory_gcd(PyObject *self, PyObject *args) {
	int a, b;
	if(!PyArg_ParseTuple(args, "ii", &a, &b))
		return NULL;
	return Py_BuildValue("i", gcd(a, b));
}

/*
CRT_DECOMPOSE Definition
*/
static PyObject *numtheory_crt_decompose(PyObject *self, PyObject *args) {
	int i, k, *mods, mods_length, *decomp;
	PyObject *obj, *item, *decomp_list;
	obj = malloc(sizeof(PyObject));	

	if(!PyArg_ParseTuple(args, "iO", &i, &obj))
		return NULL;
	if(!PyList_Check(obj))
		return NULL;

	mods_length = PyList_Size(obj);
	mods = malloc(sizeof(int) * mods_length);

	for(k = 0; k < mods_length; k++) {
		item = PyList_GetItem(obj, k);
		if(!PyInt_Check(item))
			return NULL;
		mods[k] = (int)PyInt_AsLong(item);
	}

	decomp = crt_decompose(i, mods, mods_length);
	if(decomp == NULL)
		return NULL;

	decomp_list = PyList_New(mods_length);
	for(k = 0; k < mods_length; k++)
		PyList_SET_ITEM(decomp_list, (Py_ssize_t)k, PyInt_FromLong((long)decomp[k]));

	return decomp_list;
}

/*
CRT_RECONSTRUCT Definition
*/
static PyObject *numtheory_crt_reconstruct(PyObject *self, PyObject *args) {
	int *eq, *mods, mods_length, k;
	PyObject *eq_list, *mod_list, *item;
	eq_list = malloc(sizeof(PyObject));
	mod_list = malloc(sizeof(PyObject));

	if(!PyArg_ParseTuple(args, "OO", &eq_list, &mod_list))
		return NULL;
	if(!PyList_Check(mod_list) || !PyList_Check(eq_list))
		return NULL;

	mods_length = PyList_Size(mod_list);
	if(mods_length != PyList_Size(eq_list))
		return NULL;
	mods = malloc(sizeof(int) * mods_length);
	eq = malloc(sizeof(int) * mods_length);

	for(k = 0; k < mods_length; k++) {
		item = PyList_GetItem(mod_list, k);
		if(!PyInt_Check(item))
			return NULL;
		mods[k] = (int)PyInt_AsLong(item);

		item = PyList_GetItem(eq_list, k);
		if(!PyInt_Check(item))
			return NULL;
		eq[k] = (int)PyInt_AsLong(item);
	}

	return Py_BuildValue("i", crt_reconstruct(eq, mods, mods_length));
}

/*
COPRIME_CHECK Definition
*/
static PyObject *numtheory_coprime_check(PyObject *self, PyObject *args) {
	int *a, a_length, k;
	PyObject *a_list, *item;
	a_list = malloc(sizeof(PyObject));

	if(!PyArg_ParseTuple(args, "O", &a_list))
		return NULL;
	if(!PyList_Check(a_list))
		return NULL;
	a_length = PyList_Size(a_list);
	a = malloc(sizeof(int) * a_length);

	for(k = 0; k < a_length; k++) {
		item = PyList_GetItem(a_list, k);
		if(!PyInt_Check(item))
			return NULL;
		a[k] = (int)PyInt_AsLong(item);
	}

	return coprime_check(a, a_length) ? Py_True : Py_False;
}

/*
MULT_INV Definition
*/
static PyObject *numtheory_mult_inv(PyObject *self, PyObject *args) {
	int a, m;
	
	if(!PyArg_ParseTuple(args, "ii", &a, &m))
		return NULL;

	return Py_BuildValue("i", mult_inv(a, m));
}

/*
EUCLIDEAN_EXT Definition
*/
static PyObject *numtheory_euclidean_ext(PyObject *self, PyObject *args) {
	int a, b, *e, k;
	PyObject *e_list;

	if(!PyArg_ParseTuple(args, "ii", &a, &b))
		return NULL;

	e = euclidean_ext(a, b);
	e_list = PyList_New(3);
	for(k = 0; k < 3; k++)
		PyList_SET_ITEM(e_list, (Py_ssize_t)k, PyInt_FromLong((long)e[k]));

	return e_list;
}

/*
POSITIVE_RESIDUE Definition
*/
static PyObject *numtheory_positive_residue(PyObject *self, PyObject *args) {
	int a, m;
	
	if(!PyArg_ParseTuple(args, "ii", &a, &m))
		return NULL;

	return Py_BuildValue("i", positive_residue(a, m));
}

/*
SOLVE_LINEAR_DIOPHANTINE Definition
*/
static PyObject *numtheory_solve_linear_diophantine(PyObject *self, PyObject *args) {
	int a, b, c, k, *s;
	PyObject *s_list;

	if(!PyArg_ParseTuple(args, "iii", &a, &b, &c))
		return NULL;

	s = solve_linear_diophantine(a, b, c);
	if(s == NULL)
		return NULL;

	s_list = PyList_New(4);
	for(k = 0; k < 4; k++)
		PyList_SET_ITEM(s_list, (Py_ssize_t)k, PyInt_FromLong((long)s[k]));

	return s_list;
}

/*
LEGENDRE Definition
*/
static PyObject *numtheory_legendre(PyObject *self, PyObject *args) {
	int a, p;

	if(!PyArg_ParseTuple(args, "ii", &a, &p))
		return NULL;

	return Py_BuildValue("i", legendre(a, p));
}

/*
LEGENDRE_PRIME Definition
*/
static PyObject *numtheory_legendre_prime(PyObject *self, PyObject *args) {
	int p, q;

	if(!PyArg_ParseTuple(args, "ii", &p, &q))
		return NULL;

	return Py_BuildValue("i", legendre_prime(p, q));
}

/*
TAU Definition
*/
static PyObject *numtheory_tau(PyObject *self, PyObject *args) {
	int *powers, powers_length, k;
	PyObject *powers_list, *item;

	if(!PyArg_ParseTuple(args, "O", &powers_list))
		return NULL;
	if(!PyList_Check(powers_list))
		return NULL;

	powers_length = PyList_Size(powers_list);
	powers = malloc(sizeof(int) * (powers_length + 1));

	for(k = 0; k < powers_length; k++) {
		item = PyList_GetItem(powers_list, k);
		if(!PyInt_Check(item))
			return NULL;
		powers[k] = (int)PyInt_AsLong(item);
	}
	powers[powers_length] = 0;

	return Py_BuildValue("i", tau(powers));
}

/*
PHI Definition
*/
static PyObject *numtheory_phi(PyObject *self, PyObject *args) {
	int *primes, *powers, powers_length, k;
	PyObject *primes_list, *powers_list, *item;

	if(!PyArg_ParseTuple(args, "OO", &primes_list, &powers_list))
		return NULL;
	if(!PyList_Check(powers_list) || !PyList_Check(primes_list))
		return NULL;

	powers_length = PyList_Size(powers_list);
	powers = malloc(sizeof(int) * (powers_length + 1));
	if(PyList_Size(primes_list) != powers_length)
		return NULL;
	primes = malloc(sizeof(int) * (powers_length + 1));


	for(k = 0; k < powers_length; k++) {
		item = PyList_GetItem(powers_list, k);
		if(!PyInt_Check(item))
			return NULL;
		powers[k] = (int)PyInt_AsLong(item);

		item = PyList_GetItem(primes_list, k);
		if(!PyInt_Check(item))
			return NULL;
		primes[k] = (int)PyInt_AsLong(item);
	}
	primes[powers_length] = powers[powers_length] = 0;

	return Py_BuildValue("i", phi(primes, powers));
}

/*
SIGMA Definition
*/
static PyObject *numtheory_sigma(PyObject *self, PyObject *args) {
	int *primes, *powers, powers_length, k;
	PyObject *primes_list, *powers_list, *item;

	if(!PyArg_ParseTuple(args, "OO", &primes_list, &powers_list))
		return NULL;
	if(!PyList_Check(powers_list) || !PyList_Check(primes_list))
		return NULL;

	powers_length = PyList_Size(powers_list);
	powers = malloc(sizeof(int) * (powers_length + 1));
	if(PyList_Size(primes_list) != powers_length)
		return NULL;
	primes = malloc(sizeof(int) * (powers_length + 1));


	for(k = 0; k < powers_length; k++) {
		item = PyList_GetItem(powers_list, k);
		if(!PyInt_Check(item))
			return NULL;
		powers[k] = (int)PyInt_AsLong(item);

		item = PyList_GetItem(primes_list, k);
		if(!PyInt_Check(item))
			return NULL;
		primes[k] = (int)PyInt_AsLong(item);
	}
	primes[powers_length] = powers[powers_length] = 0;

	return Py_BuildValue("i", sigma(primes, powers));
}

/*
SOLVE_LINEAR_CONGRUENCE Definition
*/
static PyObject *numtheory_solve_linear_congruence(PyObject *self, PyObject *args) {
	int a, b, m;

	if(!PyArg_ParseTuple(args, "iii", &a, &b, &m))
		return NULL;

	return Py_BuildValue("i", solve_linear_congruence(a, b, m));
}

/*
ORDER Definition
*/
static PyObject *numtheory_order(PyObject *self, PyObject *args) {
	int a, m, *primes, *powers, powers_length, k;
	PyObject *primes_list, *powers_list, *item;

	if(!PyArg_ParseTuple(args, "iiOO", &a, &m, &primes_list, &powers_list))
		return NULL;
	if(!PyList_Check(powers_list) || !PyList_Check(primes_list))
		return NULL;

	powers_length = PyList_Size(powers_list);
	powers = malloc(sizeof(int) * (powers_length + 1));
	if(PyList_Size(primes_list) != powers_length)
		return NULL;
	primes = malloc(sizeof(int) * (powers_length + 1));

	for(k = 0; k < powers_length; k++) {
		item = PyList_GetItem(powers_list, k);
		if(!PyInt_Check(item))
			return NULL;
		powers[k] = (int)PyInt_AsLong(item);

		item = PyList_GetItem(primes_list, k);
		if(!PyInt_Check(item))
			return NULL;
		primes[k] = (int)PyInt_AsLong(item);
	}
	primes[powers_length] = powers[powers_length] = 0;

	return Py_BuildValue("i", order(a, m, primes, powers));
}

/*
PRIMITIVE_ROOT Definition
*/
static PyObject *numtheory_primitive_root(PyObject *self, PyObject *args) {
	int m, *primes, *powers, powers_length, k;
	PyObject *primes_list, *powers_list, *item;

	if(!PyArg_ParseTuple(args, "iOO", &m, &primes_list, &powers_list))
		return NULL;
	if(!PyList_Check(powers_list) || !PyList_Check(primes_list))
		return NULL;

	powers_length = PyList_Size(powers_list);
	powers = malloc(sizeof(int) * (powers_length + 1));
	if(PyList_Size(primes_list) != powers_length)
		return NULL;
	primes = malloc(sizeof(int) * (powers_length + 1));

	for(k = 0; k < powers_length; k++) {
		item = PyList_GetItem(powers_list, k);
		if(!PyInt_Check(item))
			return NULL;
		powers[k] = (int)PyInt_AsLong(item);

		item = PyList_GetItem(primes_list, k);
		if(!PyInt_Check(item))
			return NULL;
		primes[k] = (int)PyInt_AsLong(item);
	}
	primes[powers_length] = powers[powers_length] = 0;

	return Py_BuildValue("i", primitive_root(m, primes, powers));
}

/*
ALL_PRIMITIVE_ROOTS Definition
*/
static PyObject *numtheory_all_primitive_roots(PyObject *self, PyObject *args) {
	int m, *primes, *powers, *roots, powers_length, k;
	PyObject *primes_list, *powers_list, *roots_list, *item;

	if(!PyArg_ParseTuple(args, "iOO", &m, &primes_list, &powers_list))
		return NULL;
	if(!PyList_Check(powers_list) || !PyList_Check(primes_list))
		return NULL;

	powers_length = PyList_Size(powers_list);
	powers = malloc(sizeof(int) * (powers_length + 1));
	if(PyList_Size(primes_list) != powers_length)
		return NULL;
	primes = malloc(sizeof(int) * (powers_length + 1));

	for(k = 0; k < powers_length; k++) {
		item = PyList_GetItem(powers_list, k);
		if(!PyInt_Check(item))
			return NULL;
		powers[k] = (int)PyInt_AsLong(item);

		item = PyList_GetItem(primes_list, k);
		if(!PyInt_Check(item))
			return NULL;
		primes[k] = (int)PyInt_AsLong(item);
	}
	primes[powers_length] = powers[powers_length] = 0;

	roots = all_primitive_roots(m, primes, powers);
	if(roots == NULL)
		return NULL;

	roots_list = PyList_New((Py_ssize_t)0);
	k = 0;
	while(roots[k] != -1)
		PyList_Append(roots_list, PyInt_FromLong((long)roots[k]));

	return roots_list;
}

/*
POW_MOD Definition
*/
static PyObject *numtheory_pow_mod(PyObject *self, PyObject *args) {
	unsigned long y, x, m;

	if(!PyArg_ParseTuple(args, "kkk", &y, &x, &m))
		return NULL;

	return Py_BuildValue("k", pow_mod(y, x, m));
}

/*
Method table
*/
static PyMethodDef numtheory_methods[] = {
	{"gcd", (PyCFunction)numtheory_gcd, METH_VARARGS, "Compute the Greatest Common Divisor."},
	{"crt_decompose", (PyCFunction)numtheory_crt_decompose, METH_VARARGS, "Decompose a Natural Number with the Chinese Remainder Theorem."},
	{"crt_reconstruct", (PyCFunction)numtheory_crt_reconstruct, METH_VARARGS, "Reconstruct a Natural Number with the Chinese Remainder Theorem."},
	{"coprime_check", (PyCFunction)numtheory_coprime_check, METH_VARARGS, "Check if all numbers in a list are coprime to each other."},
	{"mult_inv", (PyCFunction)numtheory_mult_inv, METH_VARARGS, "Find the Multiplicative Inverse of a Number a modulo m."},
	{"euclidean_ext", (PyCFunction)numtheory_euclidean_ext, METH_VARARGS, "Get the results of the Extended Euclidean Algorithm on a and b."},
	{"positive_residue", (PyCFunction)numtheory_positive_residue, METH_VARARGS, "Convert an Integer to a Positive Residue modulo m."},
	{"solve_linear_diophantine", (PyCFunction)numtheory_solve_linear_diophantine, METH_VARARGS, "Solve a Linear Diophantine Equation."},
	{"legendre", (PyCFunction)numtheory_legendre, METH_VARARGS, "Evaluate a Legendre Symbol where the lower value is prime."},
	{"legendre_prime", (PyCFunction)numtheory_legendre_prime, METH_VARARGS, "Evaluate a Legendre Symbol where both values are prime."},
	{"tau", (PyCFunction)numtheory_tau, METH_VARARGS, "Find tau of a factored positive integer."},
	{"phi", (PyCFunction)numtheory_phi, METH_VARARGS, "Find phi of a factored positive integer."},
	{"sigma", (PyCFunction)numtheory_sigma, METH_VARARGS, "Find sigma of a factored positive integer."},
	{"solve_linear_congruence", (PyCFunction)numtheory_solve_linear_congruence, METH_VARARGS, "Solve a Linear Congruence Equation."},
	{"order", (PyCFunction)numtheory_order, METH_VARARGS, "Find the Order of a Number modulo m."},
	{"primitive_root", (PyCFunction)numtheory_primitive_root, METH_VARARGS, "Find a Primitive Root modulo m."},
	{"all_primitive_roots", (PyCFunction)numtheory_all_primitive_roots, METH_VARARGS, "Find all Primitive Roots modulo m."},
	{"pow_mod", (PyCFunction)numtheory_pow_mod, METH_VARARGS, "Find a power modulo m."},
	{NULL, NULL, 0, NULL}
};

/*
Initialization Function
*/
PyMODINIT_FUNC initnumtheory(void) {
	(void)Py_InitModule("numtheory", numtheory_methods);
}
