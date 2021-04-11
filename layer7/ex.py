from pwn import *

def fileToBase64(filepath):
    fp = open(filepath, "rb")
    data = fp.read()
    fp.close()
    return base64.b64encode(data)

a=base64.b64encode(open("/mnt/c/Users/bww96/Desktop/firstexec",'rb').read())
b=base64.b64encode(open("/mnt/c/Users/bww96/Desktop/secondexec",'rb').read())

print a
print b

p=remote("211.239.124.243", 18608)

p.recv()
p.sendline(str(len(a)+(4-len(a)%4)))
p.recv()
p.sendline(str(len(b)+(4-len(b)%4)))
p.recv()
p.send(a+"="*(4-len(a)%4))
p.recv()
p.send(b+"="*(4-len(a)%4))
p.interactive()
