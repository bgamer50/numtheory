tests: tests/coprime_check_test_cases.x tests/crt_test_cases.x tests/euclidean_ext_test_cases.x tests/gcd_test_cases.x tests/mult_inv_test_cases.x
tests/coprime_check_test_cases.x: number_theory.o tests/coprime_check_test_cases.o
	gcc number_theory.o tests/coprime_check_test_cases.o -o tests/coprime_check_test_cases.x

tests/crt_test_cases.x: number_theory.o tests/crt_test_cases.o
	gcc number_theory.o tests/crt_test_cases.o -o tests/crt_test_cases.x

tests/euclidean_ext_test_cases.x: number_theory.o tests/euclidean_ext_test_cases.o
	gcc number_theory.o tests/euclidean_ext_test_cases.o -o tests/euclidean_ext_test_cases.x

tests/gcd_test_cases.x: number_theory.o tests/gcd_test_cases.o
	gcc number_theory.o tests/gcd_test_cases.o -o tests/gcd_test_cases.x

tests/mult_inv_test_cases.x: number_theory.o tests/mult_inv_test_cases.o
	gcc number_theory.o tests/mult_inv_test_cases.o -o tests/mult_inv_test_cases.x


tests/coprime_check_test_cases.o: number_theory.o tests/coprime_check_test_cases.c
	gcc -c tests/coprime_check_test_cases.c -o tests/coprime_check_test_cases.o

tests/crt_test_cases.o: tests/crt_test_cases.c
	gcc -c tests/crt_test_cases.c -o tests/crt_test_cases.o

tests/euclidean_ext_test_cases.o: tests/euclidean_ext_test_cases.c
	gcc -c tests/euclidean_ext_test_cases.c -o tests/euclidean_ext_test_cases.o

tests/gcd_test_cases.o: tests/gcd_test_cases.c
	gcc -c tests/gcd_test_cases.c -o tests/gcd_test_cases.o

tests/mult_inv_test_cases.o: tests/mult_inv_test_cases.c
	gcc -c tests/mult_inv_test_cases.c -o tests/mult_inv_test_cases.o

number_theory.o: number_theory.c number_theory.h
	gcc -c number_theory.c -o number_theory.o