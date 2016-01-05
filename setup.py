#Setup Script for numtheory
from disutils.core import setup, Extension
setup(name='numtheory', version='1.0', ext_modules=[Extension('numtheory', ['nt_python.c'])])