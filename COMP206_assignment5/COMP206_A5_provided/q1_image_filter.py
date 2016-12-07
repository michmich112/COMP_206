'''
*  Author:      Michel Cantacuzene
*  Name:        q1_image_filter.py
*  Description: applies a convulation matrix on an image by calling  shared library (.so)
'''

#!/usr/bin/python
import sys
import ctypes

#permits us to get the CWD whether it be on Windows or a Unix system
import os
dir_path = os.path.dirname(os.path.realpath(__file__))

# Reads a BMP image from disk into a convenient array format
def loadBMPImage( img_name ):
  #error handling
  try:
    img_in = open( img_name, 'rb' )
  except IOError:
    print(img_name+"is unreadable or doesn't exist. Please input a correct filename.")
    quit(1)
  #read and close the file
  data = img_in.read()
  img_in.close()
  return data

# Write the output image to file  
def saveBMPImage( out_img_data, out_fname ):
  img_out = open( out_fname, 'wb' )
  for element in out_img_data:
    img_out.write( element )
  img_out.close()

#function that applies the convolution matrix to the image
def parse():
  #error handlers
  if sys.argv[1] == "--help" or sys.argv[1] == "-h":
    print("Usage:\n$python q1_image_filter.py [base file name] [output file name] [convulation matrix size] [matrix elements]\n The filenames must have the .bmp extension\n The convulation matrix size must be an odd integer.\n The matrix elements are seperated by a whitespace\nExample: $python q1_image_filter.py input_filename.bmp output_filename.bmp 3 1 1 1 1 -8 1 1 1 1")
    quit(1)
  elif len(sys.argv[]) < 6:
    print("Not enough arguments. Enter a correct input.\nPass the -h or --help parameters for input help")
    quit(1)
  try: #catch an error if it's not an integer
    if int(sys.argv[3])%2 != 1:
      print("Input a correct matrix value. Integer has to be odd.\nPass the -h or --help parameters for input help")
      quit(1)
    elif len(sys.argv) != 4+(int(sys.argv[3])**2):
      print("Not enough arguments. Enter a correct input.\nPass the -h or --help parameters for input help")
      quit(1)
  except ValueError:
    print("Input a correct matrix size value.\nPass the -h or --help parameters for input help")
  if sys.argv[1].split('.')[1] != "bmp"
  #start of the program
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