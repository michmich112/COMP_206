/*
 * Name:		q1b_crack.c
 * Author: 		Michel Cantacuzene
 * Version: 	0.1
 * Description:	Reverse Ceaser key cracking program
 * Usage:		./exec <file_to_crack>
 */

#include <stdlib.h>
#include <stdio.h>

void reverse(char* strings, int size);
void decrypt(char* input, int key, int size);
void crack(char* argv[], int key);
int check(char *input, int size);

int main(int argc, char *argv[]){

	if(argc != 2){ //handle errors
		printf("Error. Bad Input\nUsage: ./executable [file_to_crack]\n");
		exit(1);
	}

	int key=0;
	while(key<256){
		crack(argv,key);
		key++;
	}
}

void crack(char* argv[],int key){ //function to crack the file's encryption
	char cur;
	char strings[1000];
	int index;
	FILE * in;
		if ((in=fopen(argv[1], "r"))== NULL){
			printf("Can't read from file %s\nUsage: ./executable [key] [file_to_decrypt]\n",argv[1]);
			exit(1);
		}

	index = 0;

	while ((cur = fgetc(in)) != EOF){ //gets the exact size of the input in the file + inserts characters into the array
		strings[index] = cur;
		index++;
	}

	reverse(strings, index-1);
	decrypt(strings,key, index-1);
	fclose(in);

	if(check(strings,index-1)){
		printf("%d\n%s\n",key,strings);
		exit(0);
	}
}

int check(char *input, int size){ //function to check if the decryption was well done or not.
	int i;
	for(i=0;i<size;i++){
		if((input[i]<65 ||input[i]>90) && (input[i]<97 || input[i]>122) && input[i]!=32 && input[i]!='\0'){
			return 0; //returns 0 for something that is not decripted well
		}
	}
	return 1; // returns 1 for omething that is correctly decrypted
}


void decrypt(char* input, int key, int size){ //function to decrypt every character in the array
	for(int i = 0; i < size; i++){
		input[i] = (input[i] - key) % 256;
	}
}




//Reverse the strings from the file
void reverse(char* strings, int size){
	char reversed[size];//itialize result to have enough memory according to size of 'strings'
	for(int j=0; j<size; j++){
		reversed[j] = strings[size-j-1];
	}
	
	for(int k=0; k<size; k++){
		strings[k] = reversed[k];
	}
}
