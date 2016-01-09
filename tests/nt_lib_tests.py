import numtheory

print(numtheory.gcd(3, 9))

mods = [3, 5, 7]
eq = numtheory.crt_decompose(41, mods)
print(numtheory.crt_reconstruct(eq, mods))

print(numtheory.coprime_check([2, 3, 5, 10]))
print(numtheory.coprime_check([2, 3, 5, 7]))

print(numtheory.mult_inv(3, 5))
print(numtheory.euclidean_ext(3, 5))

print(numtheory.positive_residue(-23, 10))
print(numtheory.solve_linear_diophantine(3, 4, 5))

print(numtheory.legendre(5, 3))
print(numtheory.legendre(4, 7))
print(numtheory.legendre_prime(5, 31))

print(numtheory.tau([1]))
print(numtheory.phi([5], [1]))
print(numtheory.sigma([5], [1]))
