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
Method table
*/
static PyMethodDef numtheory_methods[] = {
	{"gcd", (PyCFunction)numtheory_gcd, METH_VARARGS, "Compute the Greatest Common Divisor."},
	{"crt_decompose", (PyCFunction)numtheory_crt_decompose, METH_VARARGS, "Decompose a Natural Number with the Chinese Remainder Theorem."},
	{"crt_reconstruct", (PyCFunction)numtheory_crt_reconstruct, METH_VARARGS, "Reconstruct a Natural Number with the Chinese Remainder Theorem."},
	{"coprime_check", (PyCFunction)numtheory_coprime_check, METH_VARARGS, "Check if all numbers in a list are coprime to each other."},
	{"mult_inv", (PyCFunction)numtheory_mult_inv, METH_VARARGS, "Find the Multiplicative Inverse of a Number a modulo m."},
	{"euclidean_ext", (PyCFunction)numtheory_euclidean_ext, METH_VARARGS, "Get the results of the Extended Euclidean Algorithm on a and b."},
	{NULL, NULL, 0, NULL}
};

/*
Initialization Function
*/
PyMODINIT_FUNC initnumtheory(void) {
	(void)Py_InitModule("numtheory", numtheory_methods);
}
