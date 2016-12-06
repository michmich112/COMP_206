#!/usr/bin/python
import sys
import ctypes
#import pickle

#permits us to get the CWD whether it be on Windows or a Unix system
import os
dir_path = os.path.dirname(os.path.realpath(__file__))

historyFileName = "history.pickle"
try:
  historyFile = open( historyFileName , "rb")
except IOError:
  historyFile = open( historyFileName , "wb")
  historyFile.write("1 1 1 none")
  historyFile.close()
  historyFile = open( historyFileName , "rb")

'''
*   we store information as folows
* 1 <presentCounter> <furthestCounter> <mostRecentLoad> <loadedFile>
* 2 Command 1
* 3 Command 2 
* 4 ...
'''

firstLine = historyFile.readline().split()
historyFile.close()
if str(firstLine[3]) != "none":
  loadedImage = str(firstLine[3])
else:
  loadedImage = None
#currentData = None
presentCounter = int(firstLine[0])
furthestCounter = int(firstLine[1])
mostRecentLoad = int(firstLine[2])
outputFilename = "result.bmp"

#we will make a user terminal so it can interact with the program
def inputParser(provided=None):
  if provided == None:
    currentInput = sys.argv
  else:
    currentInput = provided

  if currentInput[1] == "load":
    load(currentInput[2])
    print(currentInput[2] + " was successfully loaded!")
  elif currentInput[1] == "filter":
    parse(currentInput)
    print("Convulation Terminated successfully!")
  elif currentInput[1] == "undo":
    undo()
  elif currentInput[1] == "redo":
    redo()
  elif currentInput[1] == "help":
    help()
  else:
    print("Incorrect Input.\nType: \n\t$python q2_filter_with_history.py help\nto get input help.")
    quit(1)

  if provided == None:
    passToHistory(userInput)
    updateHeader()
  else:
    pass


# Reads a BMP image from disk into a convenient array format
def loadBMPImage( img_name ):
  #error handling
  try:
    img_in = open( img_name, 'rb' )
    loadedImage = img_name
    data = img_in.read()
    img_in.close()
    return data
  except IOError:
    print(img_name+"is unreadable or doesn't exist. Please input a correct filename.")
    img_in.close()
    quit(1)

# Write the output image to file  
def saveBMPImage( out_img_data, out_fname ):
  img_out = open( out_fname, 'wb' )
  for element in out_img_data:
    img_out.write( element )
  img_out.close()

def parse(argv):
  '''#error handlers
  if sys.argv[1] == "--help" or sys.argv[1] == "-h":
    print("Usage:\n$python q1_image_filter.py [base file name] [output file name] [convulation matrix size] [matrix elements]\n The filenames must have the .bmp extension\n The convulation matrix size must be an odd integer.\n The matrix elements are seperated by a whitespace\nExample: $python q1_image_filter.py input_filename.bmp output_filename.bmp 3 1 1 1 1 -8 1 1 1 1")
    quit(1)
  elif len(sys.argv[]) < 6:
    print("Not enough arguments. Enter a correct input.\nPass the -h or --help parameters for input help")
    quit(1)'''
  try: #catch an error if it's not an integer
    if int(argv[2])%2 != 1:
      print("Input a correct matrix value. Integer has to be odd.\nType help for input help")
      quit(1)
    elif len(argv) != 2+(int(sys.argv[2])**2):
      print("Not enough arguments. Enter a correct input.\nType help for input help")
      quit(1)
  except ValueError:
    print("Input a correct matrix size value.\nType help for input help")
    quit(1)

  #start of the program
  data = loadBMPImage( loadedImage )
  filter_width = int(argv[2])
  filter_weights = []

  for i in range(filter_width*filter_width):
    #errorHandler
    filter_weights.append(float(argv[3+i]))

  c_filter_weights = (ctypes.c_float *len(filter_weights)) (*filter_weights)
  c_filter_width = ctypes.c_int(filter_width)
  output_data = [''] *len(data)
  output_data = ctypes.create_string_buffer(len(data))
  
  lib = ctypes.cdll.LoadLibrary(dir_path+"/libfast_filter.so")
  lib.doFiltering(data, c_filter_weights, c_filter_width, output_data)
  saveBMPImage(output_data, outputFilename)

def findLoad( currentSpace ):
  file = open(historyFileName)#no error possible
  currentLoad = 0
  counter = 0
  for line in file:
    if counter < currentSpace:
      if line.split()[0] == "load":
        currentLoad = counter
        counter++
      else:
        counter++
    else:
      break
  return currentLoad

def load(img_name):
  loadBMPImage(img_name)
  presentCounter += 1
  furthestCounter = presentCounter
  mostRecentLoad = presentCounter

def undo():
  if presentCounter >= 1:
    presentCounter -=1
  else:
    print("Cannot Undo!")
    quit(1)
  if mostRecentLoad > presentCounter:
    mostRecentLoad = findLoad(presentCounter)

  historyFile = open(historyFileName,"r")
  for i in range(0,mostRecentLoad):
    historyFile.readline()
  for i in range(mostRecentLoad,presentCounter):
    inputParser(historyFile.readline().split())
  historyFile.close()

def redo():
  if presentCounter < furthestCounter:
    historyFile = open(historyFileName, "r")
    for i in range(1,presentCounter):
      historyFile.readline()
    inputParser(historyFile.readline().split())
    historyFile.close()
  else:
    print("Cannot Redo!")
    historyFile.close()

def help():
  print("Commands:\nload [image_name.bmp]: loads a new bmp image\nfilter [filter_width] [filter_weights]: applies the inputed convulation matrix on the loaded image\nundo: undoes the last action (if possible)\nredo: redoes the last action (if possible)")
  quit(1)

def passToHistory(userInput)
  command = ""
  for querry in userInput:
    command += str(querry)
    command += " "
  historyFile = open(historyFileName,"a")
  historyFile.write(command)
  historyFile.close()

def toString( liste ):
  string = ""
  for element in liste:
    string += str(element)
    string += " "
  return string

def updateHeader():
  historyFile = open(historyFileName, "r")
  data = []
  for lines in historyFile:
    data.append(lines.split())
  data[0][0] = str(presentCounter)
  data[0][1] = str(furthestCounter)
  data[0][2] = str(mostRecentLoad)
  data[0][3] = str(loadedImage)
  historyFile.close()

  historyFile = open(historyFileName, "w")
  historyFile.write(toString(data[0]))
  historyFile.close()

  historyFile = open(historyFileName, "a")
  for i in range(1,len(data))
    historyFile.write(toString(data[i]))
  historyFile.close()


parse()