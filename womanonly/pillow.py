from PIL import Image

out=Image.new("RGB", (10*60, 10*50), (0,0,0))

outpic=out.load()

print(outpic)

for i in range(60):
	for j in range(50):
		path=str(i*50+j+1)+".jpg"
		print(path)
		im=Image.open("60x50/"+path)
		pic=im.load()
		width, height=im.size
		for k in range(width):
			for l in range(height):
				outpic[i*10+k,j*10+l]=pic[k,l]

out.save('flag.jpg')