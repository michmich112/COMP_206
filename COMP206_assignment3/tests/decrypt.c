#include <stdio.h>
#include <stdlib.h>

//main functions
void reverseStrings(char *input, char *output, int size);
void decrypt(char *input, int key, int size);

int main(int argc,char* argv[]){
	int i,size,key=atoi(argv[1]);
	char tmp[1000],read;
	FILE * dataFile;
	if((dataFile = fopen(argv[2], "r")) == NULL){
		printf("Can't read from file %s\n", argv[2]);
		exit(1);
	}

	size=0;
	while((read = fgetc(dataFile)) != EOF){
		tmp[size]=read;
		size++;
	}
	size -=1;
	fclose(dataFile);

	char input[size],output[size];
	for(i=0;i<size;i++){input[i]=tmp[i];}
	decrypt(input,key,size);
	reverseStrings(input,output,size);
	printf("%s\n",output);
	return 0;
}
/*
void decryptor(int key, char *file){
	int i,size,key=atoi(argv[1]);
	char tmp[1000],read;
	FILE * dataFile;
	if((dataFile = fopen(argv[2], "r")) == NULL){
		printf("Can't read from file %s\n", argv[2]);
		exit(1);
	}

	size=0;
	while((read = fgetc(dataFile)) != EOF){
		tmp[size]=read;
		size++;
	}
	size -=1;
	fclose(dataFile);

	char input[size],output[size];
	for(i=0;i<size;i++){input[i]=tmp[i];}
	decrypt(input,key,size);
	reverseStrings(input,output,size);
	printf("%s\n",output);
	return 0;
}*/

void decrypt(char *input, int key, int size){
	for(int i=0;i<size;i++){
		input[i]=(input[i] - key) % 256;
	}
}


void reverseStrings(char *input, char *output, int size){
	int i;
	for(i=0;i<size; i++){
		output[i] = input[size-i-1];
	}
}
