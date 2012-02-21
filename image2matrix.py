#!/usr/local/bin/python3
import sys
import Image
import numpy

if (len(sys.argv) > 1):
  name = sys.argv[1]  
  im = Image.open(name)
  if(im.mode not 'L'):
    im = im.convert('L')
  im.show()
  pixels = numpy.asarray(im)
  numpy.savetxt('matrix', pixels, fmt='%d')
  size = im.size
  sizetxt = open('size', 'w')
  sizetxt.write(str(size[0])+'\n')
  sizetxt.write(str(size[1])+'\n')
  sizetxt.close()
