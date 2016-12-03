#Author		: Michel Cantacuzene
#Description: Finds the frequency of word-pair apearences in a text file

#!/usr/bin/python
import sys
import operator

global filename
words = {} #dictionary where we will store the words and the number of repetitions
punctuation = [",",'.',";",":","?","!","'","(",")","{","}","[","]","-",">","<","+","=",'"'] #punctuation marks to watch out for and remove

def main():
	#error handler
	if len(sys.argv) != 2 :
		print "Plese input a file name."
		quit(1)
	else:
		filename = sys.argv[1]
	
	#opens the file
	try:
		file = open(filename,"r")
		text = file.read().lower()
		for symbol in punctuation:
			text = text.replace(symbol," ")
		for number in range(10):
			text = text.replace(str(number),"")
		initializeFrequency(text.split())
		displayFrequency()

	except IOError:
		print("File is unreadable or doesn't exist. Please change permisions or create the file")

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

main()