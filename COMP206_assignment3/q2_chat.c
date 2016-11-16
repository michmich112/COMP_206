/*Chat Daemon*/
/*we will use a linked list to make messages as long as people want*/

#include <stdio.h>
#include <stdlib.h>

void chatDaemon(char *argv[]);
void printMessage(FILE * stream);
/*
void enqueue(char elem, struct queue * data);
char dequeue(struct queue * data);

struct s_listnode {
    char element;
    struct s_listnode * pnext;
};

struct queueData {
    struct s_listnode *queue_buffer; //start empty
    struct s_listnode *prear; //start empty
};
*/

int main(int argc, char *argv[]){
	return 0;
}

void chatDaemon(char *argv[]){
	char *username = argv[3];
	FILE * inputFile;
	FILE * outputFile;

	//struct queue inputQueue = newQueue();

	inputFile = fopen(argv[1],"r");
	outputFile = fopen(argv[2],"w"); // opens the file for writing and creates it if it doesn't exist

	//while(inputFile == NULL){inputFile = fopen(argv[1],"r");} //if the file doesn't exist it means that the other person isn't cpnnected yet
	if(inputFile == NULL ||fgetc(inputFile)==EOF){
		printf("Nothing received yet.\n");
	} else {
		printMessage(inputFile);
		fclose(inputFile);
		//inputFile = fopen(argv[1],"w")
	}


}

void printMessage(FILE * stream){
	char tmp;
	printf("Received: ");
	while((tmp= fgetc(stream)) != EOF){
		printf("%c",tmp);
	}
}

void sendMessage(FILE * stream){
	char tmp;
	printf("Send:");
	tmp=getc(stdin);
	if(tmp=='\n'){
		printf("Session terminated due to end of input stream\n");exit(1);
	} else {
		while(tmp!='\n'){
			fputc("%c",stream);
			tmp=getc(stdin);
		}
	}
	printf("\n");
}
/*
struct queue newQueue(void){
    struct queue data;
    data.queue_buffer = NULL;
    data.prear = NULL;
    return data;
}
    
void enqueue(char elem,struct queue * data) {
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

char dequeue(struct queue * data) {
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
*/