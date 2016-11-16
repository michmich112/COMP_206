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

int chatDaemon(char *argv[], int runs);
void printMessage(FILE * stream, char tmp);
void sendMessage(FILE * stream, char *username);

int main(int argc, char *argv[]){
	if(argc!=4){
		printf("Error. Wrong input\nUsage: ./executable [incoming file] [outgoing_file] [username]\n");
		exit(1);
	}
	int i=1,runs=1;
	while(i){
		i=chatDaemon(argv,runs);
		runs++;
	}
	return 0;
}

int chatDaemon(char *argv[],int runs){  //function for the chat daemon, return 1 for a successful turn
	char *username = argv[3],tmp;
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
		printMessage(inputFile,tmp);
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
		printMessage(inputFile,tmp);
		fclose(inputFile);
		inputFile = fopen(argv[1], "w");
		fclose(inputFile);
	}else {
		printMessage(inputFile,tmp);
		fclose(inputFile);
		inputFile = fopen(argv[1], "w");
		fclose(inputFile);
	}

	outputFile = fopen(argv[2],"w"); // opens the file for writing and creates it if it doesn't exist
	sendMessage(outputFile,username);
	fclose(outputFile);

	return 1;
}


void printMessage(FILE * stream,char tt){ //function to print the received messages
	char tmp;
	printf("Received: %c",tt);
	while((tmp= fgetc(stream)) != EOF){
		printf("%c",tmp);
	}
	printf("\n");
}

void sendMessage(FILE * stream,char *username){ //function to send messages
	char tmp;
	printf("Send:");
	tmp=getc(stdin);
	if(tmp=='\n'){
		printf("Session terminated due to end of input stream\n");
		exit(1);
	} else {
		fputc('[',stream);
		fputs(username,stream);
		fputs("] ",stream);
		while(tmp!='\n'){
			fputc(tmp,stream);
			tmp=getc(stdin);
		}
		fputc(EOF,stream);
	}
}
