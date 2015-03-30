#!/usr/bin/python
#Filename:test.py
import string
import numpy as np
from tile_raster_image import tile_raster_images
import PIL.Image
import theano

def readweight():
	weightlist=[]
	f=open('../src/red_image[0]_pixel.txt','r')
	s=f.read()
	b=s.split('\n')
	del b[-1]
	for element in b:
		weightlist.append(string.atof(element))
	a=np.array(weightlist,dtype=np.float64).reshape(32,32)
	#a=(-1)*a
	#print a[1]
	return a

def plotimage(a):
	#arr1=np.array(a,dtype=theano.config.floatX)
	image = PIL.Image.fromarray(tile_raster_images(a.T,img_shape=(32,32),tile_shape=(10,10),tile_spacing=(0,0)))
	image.save('test_epoch_0.png')

def main():
	a=readweight()
	plotimage(a)

if __name__=='__main__':
	main()
