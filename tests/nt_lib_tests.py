import numtheory

print(numtheory.gcd(3, 9))

mods = [3, 5, 7]
eq = numtheory.crt_decompose(41, mods)
print(numtheory.crt_reconstruct(eq, mods))
