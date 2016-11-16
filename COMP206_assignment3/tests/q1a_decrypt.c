
#include <stdlib.h>
#include <stdio.h>

void reverse(char* strings, int size);
void decrypt(char* input, int key, int size);
void decryption(char* argv[]);

int main(int argc, char* argv[]){

	if (argc<2){ //no args..bad! we need input!
			printf("Not enough arguments!\n");
			exit(1);
		}

	decryption(argv);
} //end main



void decryption(char* argv[]){
	char cur;
	char strings[1000];
	int index;
	FILE * in;
		in=fopen(argv[2], "r"); 
		if (in == NULL){
			fprintf(stderr, "Can't open the file!\n");
			exit(1);
		}

	index = 0;

	while ((cur = fgetc(in)) != EOF){
		strings[index] = cur;
		index++;
	}

	reverse(strings, index-1);
	decrypt(strings,atoi(argv[1]), index-1);
	printf("%s\n",strings);

	fclose(in); 
}



void decrypt(char* input, int key, int size){
	for(int i = 0; i < size; i++){
		input[i] = (input[i] - key) % 256;
	
	}
}




//Reverse the strings from the file
void reverse(char* strings, int size){
	//find size of the input strings
	
	char reversed[size];//itialize result to have enough memory according to size of 'strings'
	for(int j=0; j<size; j++){
		reversed[j] = strings[size-j-1];
	
	
	}
	
	for(int k=0; k<size; k++){
		strings[k] = reversed[k];
	}
}



