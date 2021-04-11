from pwn import *

p=process("./chall")

pause()

p.send("\x00")

pause()

p.interactive()
