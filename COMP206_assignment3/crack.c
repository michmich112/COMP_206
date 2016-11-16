#include <stdlib.h>
#include <stdio.h>

void reverse(char* strings, int size);
void decrypt(char* input, int key, int size);
void crack(char* argv[], int key);
int check(char *input, int size);

int main(int argc, char *argv[]){
	int key=0;
	while(key<256){
		crack(argv,key);
		key++;
	}
}

void crack(char* argv[],int key){
	char cur;
	char strings[1000];
	int index;
	FILE * in;
		in=fopen(argv[1], "r"); 
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
	decrypt(strings,key, index-1);
	//printf("%s\n",strings);
	fclose(in);

	if(check(strings,index-1)){
		printf("%d\n%s\n",key,strings);
		exit(0);
	}
}

int check(char *input, int size){
	int i;
	for(i=0;i<size;i++){
		if((input[i]<65 ||input[i]>90) && (input[i]<97 || input[i]>122) && input[i]!=32 && input[i]!='\0'){
			return 0; //returns 0 for something that is not decripted well
		}
	}
	return 1; // returns 1 for omething that is correctly decrypted
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
