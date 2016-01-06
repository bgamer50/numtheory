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

*/
static PyObject *numtheory_crt_decompose(PyObject *self, PyObject *args) {
	int i, k, *mods, mods_length;
	PyObject *obj, *item;
	if(!PyArgParseTuple(args, "iO"), &i, obj)
		return NULL;
	mods_length = PyTupleSize(obj);

	mods = malloc(sizeof(int) * mods_length);
	for(k = 0; k < mods_length; k++) {
		item = PyTuple_GetItem(obj, k);
		if(!PyInt_Check(item))
			return NULL;
		mods[k] = (int)item;
	}

	return NULL;
}
/*
Method table
*/
static PyMethodDef numtheory_methods[] = {
	{"gcd", (PyCFunction)numtheory_gcd, METH_VARARGS, "Compute the Greatest Common Divisor."},
	{NULL, NULL, 0, NULL}
};

/*
Initialization Function
*/
PyMODINIT_FUNC initnumtheory(void) {
	(void)Py_InitModule("numtheory", numtheory_methods);
}
