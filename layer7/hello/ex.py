import os
flag=""
for i in range(998,0,-1):
	flag="unzip "+"layer"+str(i)+".zip"
	os.system(flag)

