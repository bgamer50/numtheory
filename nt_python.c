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
	int *eq, *mods, mods_length, k, r;
	PyObject *eq_list, *mod_list, *item;
	eq_list = malloc(sizeof(PyObject));
	mod_list = malloc(sizeof(PyObject));

	if(!PyArg_ParseTuple(args, OO, &eq_list, &mods_list))
		return NULL;
	if(!PyList_Check(mod_list) || !PyList_Check(eq_list))
		return NULL;

	mods_length = PyList_Size(mod_list);
	if(mods_length != PyList_Size(eq_list))
		return NULL;
	mods = malloc(sizeof(int) * mods_length);
	eq = malloc(sizeof(int) * mods_length);

	for(k = 0; k < mods_length; k++) {
		item = PyList_GetItem(mods_list, k);
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
Method table
*/
static PyMethodDef numtheory_methods[] = {
	{"gcd", (PyCFunction)numtheory_gcd, METH_VARARGS, "Compute the Greatest Common Divisor."},
	{"crt_decompose", (PyCFunction)numtheory_crt_decompose, METH_VARARGS, "Decompose a Natural Number with the Chinese Remainder Theorem."},
	{"crt_reconstruct", (PyCFunction)numtheory_crt_reconstruct, METH_VARARGS, "Reconstruct a Natural Number with the Chinese Remainder Theorem."},
	{NULL, NULL, 0, NULL}
};

/*
Initialization Function
*/
PyMODINIT_FUNC initnumtheory(void) {
	(void)Py_InitModule("numtheory", numtheory_methods);
}
