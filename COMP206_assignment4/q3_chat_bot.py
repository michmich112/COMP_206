#Author		: Michel Cantacuzene
#Description: Finds the frequency of word-pair apearences in a text file

#!/usr/bin/python
import sys
import operator
from random import randint

global filename
words = {} #dictionary where we will store the words and the number of repetitions
punctuation = [",",'.',";",":","?","!","'","(",")","{","}","[","]","-",">","<","+","=",'"',"_","*","&"] #punctuation marks to watch out for and remove

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

#displays the frequencies of word-pairs
def displayFrequency():
	keys = words.keys()
	sorted_words = sorted(words.items(), key=operator.itemgetter(1))
	sorted_words.reverse()
	for items in sorted_words:
		print(str(items[0])+": "+str(items[1]))

#this is the chatbot
def chatBot(): 
	print("Welcome to chatbot! This is a very poorly designed chat AI. just type your words and enjoy the response. To quit press enter without having written a response.\nHave fun!")
	userInput=str(raw_input("[user]-> ")) #display the prompt
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
		response += associateNext(lastWord)[randint(0,len(associateNext(lastWord))-1)] #add one of paired word to the last word
		for i in range(len(userInput)-1): #go through all the words except the last word
			response += " "
			lastWord = userInput[i]
			response += associateNext(lastWord)[randint(0,len(associateNext(lastWord))-1)] #get the paird word 

		print("[chatbot] -> "+response)
		userInput=str(raw_input("[user]-> "))

def associateNext(word): #function to get an associated word to the querry
	keyz = words.keys()
	possibilities = []
	for key in keyz:
		k = key.split('-')
		if k[0] == word:
			possibilities.append(k[1])
	if len(possibilities) < 1:
		k = keyz[randint(0,len(keyz))].split('-')
		possibilities.append(k[randint(0,1)])
	return possibilities

main()