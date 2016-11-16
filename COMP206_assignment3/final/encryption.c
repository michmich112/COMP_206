#include "encryption.h"

void decryptMessage(char* input, int key, int size){ //decrypt every char in the array
	reverse(input,size);
	for(int i = 0; i < size; i++){
		input[i] = (input[i] - key) % 256;
	
	}
}

void encryptMessage(char* input, int key, int size){ //decrypt every char in the array
	reverse(input,size);
	for(int i = 0; i < size; i++){
		input[i] = (input[i] + key) % 256;
	
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
