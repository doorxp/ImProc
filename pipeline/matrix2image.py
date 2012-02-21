#!/usr/local/bin/python3
import sys
import Image
import numpy

pixels = numpy.loadtxt('output')
im = Image.fromarray(pixels)
im.show()

