/*
 * Name:		q2_chat.c
 * Author:		Michel Cantacuzene
 * Version:		0.1
 * Description:	Matt's Chat Daemon
 * Usage:		./executable <incoming_file> <outgoing_file> <username>
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "encryption.h"

int chatDaemon(char *argv[], int runs);
void printMessage(FILE * stream, char tt,int key);
void sendMessage(FILE * stream, char *username,int key);

int main(int argc, char *argv[]){
	int i=1,runs=1;
	while(i){
		i=chatDaemon(argv,runs);
		runs++;
	}
	return 0;
}

int chatDaemon(char *argv[],int runs){  //function for the chat daemon, return 1 for a successful turn
	char *username = argv[3],tmp;
	int key=atoi(argv[4]);
	FILE * inputFile;
	FILE * outputFile;

	inputFile = fopen(argv[1],"r");
	//tmp = fgetc(inputFile);

	if((inputFile == NULL) && runs == 1){
		printf("Nothing received yet.\n");
	}else if((inputFile != NULL) && runs ==1){
 		tmp = fgetc(inputFile);
		if(tmp==EOF){printf("Nothing received yet.\n");}
	}else if((inputFile == NULL) && runs >= 2){
		while(inputFile == NULL){
			fclose(inputFile);
			sleep(1);//wait before reopening the file to avoid stream errors on the same file.
			inputFile = fopen(argv[1],"r");
		}
		if((tmp=fgetc(inputFile))==EOF && runs >= 2){ 
		while(tmp==EOF){
			fclose(inputFile);
			sleep(1);//wait before reopening the file to avoid stream errors on the same file.
			inputFile = fopen(argv[1],"r");
			tmp = fgetc(inputFile);
		}
		printMessage(inputFile,tmp,key);
		fclose(inputFile);
		inputFile = fopen(argv[1], "w");
		fclose(inputFile);
		}
	}else if((tmp=fgetc(inputFile))==EOF && runs >= 2){ 
		while(tmp==EOF){
			fclose(inputFile);
			sleep(1);//wait before reopening the file to avoid stream errors on the same file.
			inputFile = fopen(argv[1],"r");
			tmp = fgetc(inputFile);
		}
		printMessage(inputFile,tmp,key);
		fclose(inputFile);
		inputFile = fopen(argv[1], "w");
		fclose(inputFile);
	}else {
		printMessage(inputFile,tmp,key);
		fclose(inputFile);
		inputFile = fopen(argv[1], "w");
		fclose(inputFile);
	}

	outputFile = fopen(argv[2],"w"); // opens the file for writing and creates it if it doesn't exist
	sendMessage(outputFile,username,key);
	fclose(outputFile);

	return 1;
}


void printMessage(FILE * stream,char tt, int key){ //function to print the received messages
	char tmp,input[10000];
	printf("Received: %c",tt);
	int i=0,j;
	while((tmp= fgetc(stream)) != EOF){
		input[i] = tmp;
		//printf("%c",tmp);
	}
	decryptMessage(input,key,i);
	for(j=0;j<i;j++){printf("%c",input[j]);}
	printf("\n");
}

void sendMessage(FILE * stream,char *username,int key){ //function to send messages
	char tmp,input[10000];
	int counter=0;
	printf("Send:");
	tmp=getc(stdin);
	if(tmp=='\n'){
		printf("Session terminated due to end of input stream\n");
		exit(1);
	} else {
		/*fputc('[',stream);
		fputs(username,stream);
		fputs("] ",stream);*/
		input[counter]='[';
		counter++;
		while(username[counter-1]!='\0'){input[counter]=username[counter-1];counter++;}
		while(tmp!='\n'){
			//fputc(tmp,stream);
			input[counter]=tmp;
			tmp=getc(stdin);
			counter++;
		}
		input[counter]='\0';
		encryptMessage(input,key,counter-1);
		fputs(input,stream);
		fputc(EOF,stream);
	}
}