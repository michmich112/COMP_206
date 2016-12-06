#!/usr/bin/python
import sys
import ctypes
import pickle

#permits us to get the CWD whether it be on Windows or a Unix system
import os
dir_path = os.path.dirname(os.path.realpath(__file__))

HistoryData = []
historyFileName = "history.pickle"
global presentCounter
global furthestCounter
global mostRecentLoad
global loadedImage
outputFilename = "result.bmp"

def initialize():
  global HistoryData, presentCounter,furthestCounter,mostRecentLoad,loadedImage
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

#we will make a user terminal so it can interact with the program
def inputParser(provided=None):
  initialize()

  if provided == None:
    currentInput = sys.argv
  else:
    currentInput = provided

  if currentInput[1] == "load":
    load(currentInput[2])
    print(currentInput[2] + " was successfully loaded!")
    if provided == None:
      print(currentInput[2] + " was successfully loaded!")
      passToHistory(currentInput)
      updateHeader()
  elif currentInput[1] == "filter":
    parse(currentInput)
    if provided == None:
      print("Convulation Terminated successfully!")
      passToHistory(currentInput)
      updateHeader()
  elif currentInput[1] == "undo":
    undo()
  elif currentInput[1] == "redo":
    redo()
  elif currentInput[1] == "help":
    help()
  else:
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
    #errorHandler
    filter_weights.append(float(argv[3+i]))

  c_filter_weights = (ctypes.c_float *len(filter_weights)) (*filter_weights)
  c_filter_width = ctypes.c_int(filter_width)
  output_data = [''] *len(data)
  output_data = ctypes.create_string_buffer(len(data))
  
  lib = ctypes.cdll.LoadLibrary(dir_path+"/libfast_filter.so")
  lib.doFiltering(data, c_filter_weights, c_filter_width, output_data)
  saveBMPImage(output_data, outputFilename)

  presentCounter += 1
  furthestCounter = presentCounter

def findLoad( currentSpace ):
  global HistoryData
  currentLoad = 0
  counter = 0
  while counter <= currentSpace:
    if HistoryData[counter+1].split()[1] == "load":
      currentLoad = counter
      counter += 1
    else:
      counter += 1
  return currentLoad

def load(img_name):
  global presentCounter, furthestCounter, mostRecentLoad, outputFilename
  data = loadBMPImage(img_name)
  saveBMPImage(data, outputFilename)
  presentCounter += 1
  furthestCounter = presentCounter
  mostRecentLoad = presentCounter


def undo():
  global presentCounter,mostRecentLoad,HistoryData
  if presentCounter >= 1:
    presentCounter -=1
  else:
    print("Cannot Undo!")
    quit(1)
  if mostRecentLoad > presentCounter:
    mostRecentLoad = findLoad(presentCounter)

  for i in range(mostRecentLoad,presentCounter+1):
    print(str(i)+"\n\n\n")
    inputParser(HistoryData[i].split())
  updateHeader()


##forgot to redo the redo function
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
  #debugging
  global HistoryData
  print(HistoryData)
  quit(1)

def passToHistory(userInput):
  global HistoryData,historyFileName,presentCounter,furthestCounter
  if len(HistoryData) > presentCounter+1:
    print("it is true\n\n\n\n")
    for i in range(len(HistoryData)-(presentCounter+1)):
      del HistoryData[len(HistoryData)-1]
  furthestCounter = presentCounter
  HistoryData.append(toString(userInput))
  pickle.dump(HistoryData,open(historyFileName,"r+"))
  print(HistoryData)

def toString( liste ):
  string = ""
  for element in liste:
    string += str(element)
    string += " "
  return string

def updateHeader():
  global HistoryData,historyFileName
  HistoryData[0][0] = presentCounter
  HistoryData[0][1] = furthestCounter
  HistoryData[0][2] = mostRecentLoad
  HistoryData[0][3] = loadedImage
  pickle.dump(HistoryData,open(historyFileName,"r+"))

inputParser()