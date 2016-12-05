'''**************************************************************************
*
* FILE: convolve_slow.py
*
* BRIEF: Implements image filtering from the Unix command-line 
*
* USAGE EXAMPLE: Apply an edge detector
* $python convolve_slow.py utah.bmp utah_edges.bmp 3 -1 -1 -1 -1 8 -1 -1 -1 -1
* 
* COMMAND-LINE ARGUMENTS:
*  1)                   Input filename (must be bmp format).
*  2)                   Output filename (will be bmp format).
*  3)                   Filter width (an odd integer).
*  4 to filter_width^2) The floating point weights that define the filter, 
*                       ordered left->right and top->bottom.
*                   
* AUTHOR: David Meger, 2015
*
***************************************************************************'''

#!/usr/bin/python
import sys
import struct
import copy
import cProfile
import re
import ctypes

# Reads a BMP image from disk into a convenient array format
def loadBMPImage( img_name ):

  img_in = open( img_name, 'rb' )

  #declaring img_data as a list. 
  img_data = []

  #read from the binary code from the file and store it into img_data. 
  img_data = img_in.read()
  img_in.close()
  
  return ( img_data )
  
# Write the output image to file  
def saveBMPImage( out_img_data, out_fname ):
  img_out = open( out_fname, 'wb' )
  img_out.write( out_img_data )

  img_out.close()

# The main code starts here
if __name__== "__main__":
  	#gets the image data. 
  	
  	#receives img_data from loadBMPImage.
	(img_data) = loadBMPImage( sys.argv[1] )

	#gets the filter_width from commandline and converts it into an int.
  	filter_width = int (sys.argv[3])

  	#sets up a list for filter_weights
  	filter_weights = []

  	#storing the filter_weights as float. 
	for i in range(0,filter_width*filter_width):
		filter_weights.append( float(sys.argv[4+i] ))
  	
  	#converts the filter weights into a ctype array. 
  	filweights = (ctypes.c_float *len(filter_weights)) (*filter_weights)

  	#converts the width into ctype int. 
  	filwidth = ctypes.c_int(filter_width)

 	#imgData = (ctype.c_float * len(img_data)) (*img_data)
  	outData = [''] *len(img_data)

  	#uses string_buffer to cast the list into a C_Type array. 
  	outData = ctypes.create_string_buffer(len(img_data))

  	#loads library
  	lib = ctypes.cdll.LoadLibrary("./libfast_filter.so")
	
  	lib.doFiltering(img_data, filweights, filwidth, outData)

  	#i produce the BMP image. 
  	saveBMPImage(outData, sys.argv[2])