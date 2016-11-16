/*
 * Name:		q1a_decrypt.c
 * Author: 		Michel Cantacuzene
 * Version: 	0.1
 * Description:	Reverse Ceaser decryptor
 * Usage:		./exec <key> <file_to_decrypt>
 */

#include <stdlib.h>
#include <stdio.h>
#include "q1a_decrypt.h"

void reverse(char* strings, int size);
void decrypt(char* input, int key, int size);
void decryption(char* string,char *output,int key);

int main(int argc, char* argv[]){

	if (argc != 3){ //Check for errors
			printf("Error. Bad Input\nUsage: ./executable [key] [file_to_decrypt]\n");
			exit(1);
		}

	decryption(argv[2]);
}

void decryption(char* string,char *output,int key){ //decryption function
	char cur;
	int index;
	FILE * in;
	if ((in=fopen(string, "r")) == NULL){ //handle file errors
		printf("Can't read from file %s\nUsage: ./executable [key] [file_to_decrypt]\n",argv[2]);
		exit(1);
	}

	index = 0;

	while ((cur = fgetc(in)) != EOF){
		output[index] = cur; //put every character in the file to the array
		index++;
	}

	decrypt(output,key, index-1);
	printf("%s\n",output);

	fclose(in); 
}



void decrypt(char* input, int key, int size){ //decrypt every char in the array
	reverse(input,size);
	for(int i = 0; i < size; i++){
		input[i] = (input[i] - key) % 256;
	
	}
}

void reverse(char* strings, int size){ //Reverse the strings from the file
	char reversed[size];
	for(int j=0; j<size; j++){
		reversed[j] = strings[size-j-1];
	}
	for(int k=0; k<size; k++){
		strings[k] = reversed[k];
	}
}



