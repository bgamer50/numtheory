#Setup Script for numtheory
from distutils.core import setup, Extension
setup(name='numtheory', version='1.0', ext_modules=[Extension('numtheory', sources = ['nt_python.c', 'number_theory.c'])])
