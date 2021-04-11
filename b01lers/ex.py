from PIL import Image

out=Image.open("./lawnmower-ff277c32659f09599008bb4e61a43fd3.png")

pic=out.load()
width, height=out.size

for i in range(width):
	for j in range(height):
		if pic[i,j][0]==0xFC and pic[i,j][1]==0xFC and pic[i,j][2]==0xFC:
			pic[i,j]=(0,0,0)
		#elif pic[i,j][0]==0xFE and pic[i,j][1]==0xFE and pic[i,j][2]==0xFE:
		#	pic[i,j]=(0,0,0)
		else:
			pic[i,j]=(0xFF,0xFF,0xFF)

out.save('flag.png')