#Author		: Michel Cantacuzene
#Description: Finds the frequency of word-pair apearences in a text file

#!/usr/bin/python
import sys
import operator
from random import randint

global filename
words = {} #dictionary where we will store the words and the number of repetitions
punctuation = [",",'.',";",":","?","!","'","(",")","{","}","[","]","-",">","<","+","=",'"',"_","*","&","|"] #punctuation marks to watch out for and remove

def main():
	#error handler
	if len(sys.argv) < 2 :
		print "Plese at least one file name."
		quit(1)
	
	#opens the file
	for i in range(len(sys.argv)-1):
		filename = sys.argv[1+i]
		try:
			file = open(filename,"r")
			text = file.read().lower()
			for symbol in punctuation:
				text = text.replace(symbol," ")
			for number in range(10):
				text = text.replace(str(number),"")
			initializeFrequency(text.split())
			# displayFrequency()

		except IOError:
			print(filename+"is unreadable or doesn't exist. Please change permisions or create the file")

	chatBot()

#gets the frequencies of word-pairs
def initializeFrequency(liste): 
	for word in range(len(liste)-1):
		if words.get(str(liste[word])+"-"+str(liste[word+1]),0) == 0:
			words[str(liste[word])+"-"+str(liste[word+1])] = 1
		else:
			words[str(liste[word])+"-"+str(liste[word+1])] += 1

#this is the chatbot
def chatBot(): 
	print("Welcome to chatbot! This is a very poorly designed chat AI. just type your words and enjoy the response. To quit press enter without having written a response.\nHave fun!")
	userInput=str(raw_input("Send: ")) #display the prompt
	while userInput != "": #the hat goes on till the user presses return without inputing a response
		response = "" #initiate the response string
		userInput.lower()
		for symbol in punctuation:
			userInput = userInput.replace(symbol," ")
		for number in range(10):
			userInput = userInput.replace(str(number),"")
		userInput = userInput.split()
		lastWord = userInput[len(userInput)-1]
		response += lastWord #input the last word as the first word because... why not?
		response += " "
		lastWord = associateNext(lastWord)#[randint(0,len(associateNext(lastWord))-1)] #get the paird word
		if len(lastWord)<1:
			k = words.keys()
			lastWord = k[randint(0,len(k)-1)].split('-')[randint(0,1)]
		else:
			lastWord = lastWord[randint(0,len(lastWord)-1)]
		response += lastWord
		for i in range(18): #go through up to 20 words
			lastWord = associateNext(lastWord)#[randint(0,len(associateNext(lastWord))-1)] #get the paird word
			if len(lastWord)<1:
				break
			else:
				response += " "
				lastWord = lastWord[randint(0,len(lastWord)-1)]
				response += lastWord
		response += "."
		print("Received: "+capitalizeResponse(response))
		userInput=str(raw_input("Send: "))

def associateNext(word): #function to get an associated word to the querry
	keyz = words.keys()
	possibilities = []
	for key in keyz:
		k = key.split('-')
		if k[0] == word:
			possibilities.append(k[1]) #appends the paired word to the possibilities list
	return possibilities

def capitalizeResponse(response):
	return response[:0].lower() + response[0:].capitalize() #capitalize the first letter but not the rest

#start up the main function to run the program
main()