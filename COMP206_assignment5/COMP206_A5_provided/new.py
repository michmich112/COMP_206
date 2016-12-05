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
import ctypes
import os

dir_path = os.path.dirname(os.path.realpath(__file__))

# Reads a BMP image from disk into a convenient array format
def loadBMPImage( img_name ):
  img_in = open( img_name, 'rb' )
  data = img_in.read()
  img_in.close()
  return data

# Write the output image to file  
def saveBMPImage( out_img_data, out_fname ):
  img_out = open( out_fname, 'wb' )
  for element in out_img_data:
    img_out.write( element )
  img_out.close()

def parse():
  #error handlers
  data = loadBMPImage( sys.argv[1] )
  filter_width = int(sys.argv[3])
  filter_weights = []

  for i in range(filter_width*filter_width):
    #errorHandler
    filter_weights.append(float(sys.argv[4+i]))

  c_filter_weights = (ctypes.c_float *len(filter_weights)) (*filter_weights)
  c_filter_width = ctypes.c_int(filter_width)
  output_data = [''] *len(data)
  output_data = ctypes.create_string_buffer(len(data))
  
  lib = ctypes.cdll.LoadLibrary(dir_path+"/libfast_filter.so")
  lib.doFiltering(data, c_filter_weights, c_filter_width, output_data)
  saveBMPImage(output_data, sys.argv[2])

  
parse()
# The main code starts here 
#(img_data, header_data, img_height, img_width) = loadBMPImage( sys.argv[1] )
#(filter_width, filter_weights) = parseFilterCmdArgs( sys.argv )
#out_img_data = libc.doFiltering( img_data, filter_width, filter_weights, img_height, img_width )
#saveBMPImage( out_img_data, header_data, sys.argv[2], img_height, img_width )
