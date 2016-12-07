'''
*  Author:      Michel Cantacuzene
*  Name:        q1_image_filter.py
*  Description: applies a convulation matrix on an image by calling  shared library (.so)
'''

#!/usr/bin/python
import sys
import ctypes
import pickle

#permits us to get the CWD whether it be on Windows or a Unix system
import os
dir_path = os.path.dirname(os.path.realpath(__file__))

#global variables used in this program
HistoryData = []
historyFileName = "history.pickle"
global presentCounter
global furthestCounter
global mostRecentLoad
global loadedImage
outputFilename = "result.bmp"

#function to initialize the global variables
def initialize(): 
  global HistoryData, presentCounter,furthestCounter,mostRecentLoad,loadedImage

  #handle the possible errors
  try:
    historyFile = open( historyFileName , "rb")
    historyFile.close()
  except IOError:
    historyFile = open( historyFileName , "wb")
    historyFile.close()
    HistoryData.append([0,0,0,None]) #if there was an error this means that no value wasinputed in the file
    pickle.dump(HistoryData,open(historyFileName,"r+"))
    loadedImage = None
    #currentData = None
    presentCounter = 0
    furthestCounter = 0
    mostRecentLoad = 0

  try:
    HistoryData = pickle.load(open(historyFileName,"r+"))
    if HistoryData[0][3] != None:
      loadedImage = HistoryData[0][3]
    else:
      loadedImage = None
    #currentData = None
    presentCounter = HistoryData[0][0]
    furthestCounter = HistoryData[0][1]
    mostRecentLoad = HistoryData[0][2]

  except EOFError:
    historyFile = open( historyFileName , "wb")
    historyFile.close()
    HistoryData.append([0,0,0,None]) #if there was an error this means that no value wasinputed in the file
    pickle.dump(HistoryData,open(historyFileName,"r+"))
    loadedImage = None
    #currentData = None
    presentCounter = 0
    furthestCounter = 0
    mostRecentLoad = 0

#Function that evaluates the input, handles the errors and passes the querry to the correct function
def inputParser(provided=None): #we made provided by default None to differentiate two cases: when the user inputs from the terminal, when the inputParser function is called in the program
  global presentCounter,furthestCounter
  
  #initialize the global variables
  initialize()

  if provided == None:
    currentInput = sys.argv
  else:
    currentInput = provided

  #associates the input to the corret output(could have used a switch statement)
  if currentInput[1] == "load":
    load(currentInput[2]) #load function
    if provided == None: # since the input parser is used for the undo funtion we need to render some outputs "invisible"
      print(currentInput[2] + " was successfully loaded!")
      passToHistory(currentInput)
      presentCounter += 1
      furthestCounter = presentCounter
      mostRecentLoad = presentCounter
      updateHeader()

  elif currentInput[1] == "filter":
    if loadedImage == None:
      print("Please load an image before applying a filter.")
      quit(1)
    parse(currentInput)
    if provided == None:
      print("Convulation Terminated successfully!")
      passToHistory(currentInput)
      presentCounter += 1
      furthestCounter = presentCounter
      updateHeader()

  elif currentInput[1] == "undo":
    undo()
    print("Undone successfully!")
    quit(0)

  elif currentInput[1] == "redo":
    redo()
    print("Redone Successfully!")
    quit(0)

  elif currentInput[1] == "help":
    help()
    quit(0)

  else: #last possiblity the input is completely incorrect
    print("Incorrect Input.\nType: \n\t$python q2_filter_with_history.py help\nto get input help.")
    quit(1)

# Reads a BMP image from disk into a convenient array format
def loadBMPImage( img_name ):
  global loadedImage
  #error handling
  try:
    img_in = open( img_name, 'rb' )
    loadedImage = img_name
    data = img_in.read()
    img_in.close()
    return data
  except IOError:
    print(img_name+"is unreadable or doesn't exist. Please input a correct filename.")
    quit(1)

# Write the output image to file  
def saveBMPImage( out_img_data, out_fname ):
  img_out = open( out_fname, 'wb' )
  for element in out_img_data:
    img_out.write( element )
  img_out.close()

#function that applies the convolution 
def parse(argv):
  global loadedImage,outputFilename,presentCounter,furthestCounter
  try: #catch an error if it's not an integer
    if int(argv[2])%2 != 1:
      print("Input a correct matrix value. Integer has to be odd.\nType help for input help")
      quit(1)
    elif len(argv) != 3+(int(argv[2])**2):
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
    filter_weights.append(float(argv[3+i]))

  c_filter_weights = (ctypes.c_float *len(filter_weights)) (*filter_weights)
  c_filter_width = ctypes.c_int(filter_width)
  output_data = [''] *len(data)
  output_data = ctypes.create_string_buffer(len(data))
  
  lib = ctypes.cdll.LoadLibrary(dir_path+"/libfast_filter.so")
  lib.doFiltering(data, c_filter_weights, c_filter_width, output_data)
  saveBMPImage(output_data, outputFilename)

#function to load a specific file into
def load(img_name):
  global presentCounter, furthestCounter, mostRecentLoad, outputFilename
  data = loadBMPImage(img_name)
  saveBMPImage(data, outputFilename)

#function to undo an action
def undo():
  global presentCounter,mostRecentLoad,HistoryData
  if presentCounter >= 1:
    presentCounter -= 1 #decrese the present conter to read the adequate step while keeping the entire memory
  else:
    print("Cannot Undo!")
    quit(1)
  updateHeader()
  for i in range(0,presentCounter):
    inputParser(HistoryData[i+1].split())
  updateHeader()

#function to undo an undo aka redo something
def redo():
  global HistoryData
  if presentCounter < len(HistoryData):
    inputParser(HistoryData[presentCounter+1].split())
  else:
    print("Cannot Redo!")
    quit(1)

#function that displays the help text
def help():
  print("Commands:\nload [image_name.bmp]: loads a new bmp image\nfilter [filter_width] [filter_weights]: applies the inputed convulation matrix on the loaded image\nundo: undoes the last action (if possible)\nredo: redoes the last action (if possible)")
  #debugging
  #global HistoryData
  #print(HistoryData)
  quit(0)

#function to pass the input and the changes to the history file
def passToHistory(userInput):
  global HistoryData,historyFileName,presentCounter,furthestCounter
  if len(HistoryData) > presentCounter+1:
    for i in range(len(HistoryData)-(presentCounter+1)):
      del HistoryData[len(HistoryData)-1]
  furthestCounter = presentCounter
  HistoryData.append(toString(userInput))
  pickle.dump(HistoryData,open(historyFileName,"r+"))
  #print(HistoryData) #for debugging purpouses

#passes a list of strings into one big one
def toString( liste ):
  string = ""
  for element in liste:
    string += str(element)
    string += " "
  return string

#function to update the header section of the file
def updateHeader():
  global HistoryData,historyFileName,presentCounter,furthestCounter,mostRecentLoad,loadedImage
  HistoryData[0][0] = presentCounter
  HistoryData[0][1] = furthestCounter
  HistoryData[0][2] = mostRecentLoad
  HistoryData[0][3] = loadedImage
  pickle.dump(HistoryData,open(historyFileName,"r+"))

inputParser()
