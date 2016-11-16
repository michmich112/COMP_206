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

struct s_listnode {
    char element;
    struct s_listnode * pnext;
};

struct queueData {
    struct s_listnode *queue_buffer; //start empty
    struct s_listnode *prear; //start empty
};

int chatDaemon(char *argv[], int runs);
void printMessage(FILE * stream, char tmp);
void sendMessage(FILE * stream, char *username);
//queue functions
struct queueData newQueue(void);
void enqueue(char elem,struct queueData * data);
char dequeue(struct queueData * data);

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
	FILE * inputFile;
	FILE * outputFile;

	struct queueData queue = newQueue();

	inputFile = fopen(argv[1],"r");
	tmp = fgetc(inputFile);

	if((inputFile == NULL ||tmp==EOF)&& runs == 1){
		printf("Nothing received yet.\n");
	} else if((inputFile == NULL || tmp==EOF) && runs >= 2){
		while(inputFile == NULL || tmp==EOF){
			fclose(inputFile);
			sleep(1);//wait before reopening the file to avoid stream errors on the same file.
			inputFile = fopen(argv[1],"r");
			tmp = fgetc(inputFile);
		}
		printMessage(inputFile,tmp);
		fclose(inputFile);
		inputFile = fopen(argv[1], "w");
		fclose(inputFile);
	} else {
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

struct queueData newQueue(void){
    struct queueData data;
    data.queue_buffer = NULL;
    data.prear = NULL;
    return data;
}

void enqueue(char elem,struct queueData * data) {
    struct s_listnode *new_node = (struct s_listnode *) malloc(sizeof(struct s_listnode));
    new_node->element = elem;
    new_node->pnext = NULL; // at rear
    if (data->prear){
        data->prear->pnext = new_node;
    } else {
        data->queue_buffer = new_node;
    }
    data->prear = new_node;
}

char dequeue(struct queueData * data) {
    if (data->queue_buffer) {
        struct s_listnode *pelem = (data->queue_buffer);
        char elem = data->queue_buffer->element;
        data->queue_buffer = pelem->pnext;
        if (pelem == (data->prear)){
            data->prear = NULL;
        }
        free(pelem);
        return elem;
    } else {
        return 0;
    }
}