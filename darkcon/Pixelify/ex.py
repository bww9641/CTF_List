import base64
import argparse
from PIL import Image
import math

colours = [
		(255, 0, 0),
		(0, 0, 255),
		(0, 128, 0),
		(255, 255, 0)
	]

im = Image.open('./inject.png')
pic = im.load()
tmp = 0
a=""
for y in range(150):
  for x in range(150):
    if pic[x,y]==colours[0]:
      tmp += pow(4,3-(y*150+x)%4)*0
    if pic[x,y]==colours[1]:
      tmp += pow(4,3-(y*150+x)%4)*1
    if pic[x,y]==colours[2]:
      tmp += pow(4,3-(y*150+x)%4)*2
    if pic[x,y]==colours[3]:
      tmp += pow(4,3-(y*150+x)%4)*3
    #print("cnt is" + str(y*150+x+1))
    if (y*150+x+1)%4==0:
      print("tmp is" + chr(tmp))
      a+=chr(tmp)
      tmp=0
print(a)