from pwn import *

p=remote("bisc.lordofpwn.kr", 19834)
p=process("./startup")
e=ELF("./startup")
l=ELF("./libc64.so.6")
	

