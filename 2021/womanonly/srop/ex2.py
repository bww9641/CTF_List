f=open('pk.zip','rb').read()[::-1]

p=open('pk_rev.zip','wb')
p.write(f)

p.close()
