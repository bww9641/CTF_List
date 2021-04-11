from pwn import *

for i in range(10):
	for j in range(10):
		for k in range(10):
			for l in range(10):
				p=process("./paper.exe")
				p.sendline(str(i)+str(j)+str(k)+str(l)+"-4816")
				p.recv()
				p.sendline("")
				print p.recv()
				if "not" in p.recv():
					p.close()
					continue
				else:
					print str(i)+str(j)+str(k)+str(l)
					exit()
	
