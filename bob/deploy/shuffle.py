#!/usr/bin/env python3
# pip3 install primesieve
from random import shuffle
from primesieve import n_primes
from hashlib import md5

flag = b"bisc{REDACTED FLAG}"
flag_md5 = md5(flag).hexdigest()

flag = list(flag)
primes = n_primes(len(flag))
res = []
for i in range(len(flag)):
    res += [flag[i]] * primes[i]
shuffle(res) # ?!?!!!!!

open("shuffled.txt", "wb").write(bytes(res))
open("flag.md5.txt", "w").write(flag_md5)
