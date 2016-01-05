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
Method table
*/
static PyMethodDef module_methods[] = {
	{"gcd", (PyCFunction)numtheory_gcd, METH_VARARGS, NULL},
	{NULL, NULL, 0, NULL}
};

/*
Initialization Function
*/
PyMODINIT_FUNC initnumtheory() {
	Py_InitModule3("numtheory", module_methods, "Number Theory");
}