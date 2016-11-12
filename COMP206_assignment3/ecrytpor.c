//Ecryptor.c
//encrypts a file 
//usage: ./exe <key> <filename>

#include <stdio.h>
#include <stdlib.h>

static int inputSize;

struct s_listnode { //standard struct used for both Stack and Queue
    char element;
    struct s_listnode * pnext;
};

struct Stack{ //Stack structure to facilitate reading and modulability
    struct s_listnode *stack_buffer;
};

// functions for the stack
struct Stack newStack(void); //function to create a new Stack
void push(char elem, struct Stack * stack); //function to pus an element to the stack
char pop(struct Stack * stack); //function to pop an element from the stack

//functions for the encryption
void reverseStrings(char * array);
void encrypt(char * input, int key);

int main(int argc, char* argv[]){
	FILE * dataFile;
	char read, result[1000];
	int i;
	if((dataFile = fopen(argv[2], "r")) == NULL){
		printf("Can't read from file %s\n", argv[2]);
		exit(1);
	}
	i=0;
	while((read == fgetc(dataFile)) != EOF){
		result[i] = read;
		i++
	}
	fclose(dataFile);
	//Set input size
	inputSize = i-1;
	reverseStrings(&result);
	encrypt(&result,atoi(argv[1]));

	FILE * dataFile;
	dataFile = fopen(argv[2],"w");
	for(i=0;i<1000;i++){
		fputc(result[i],datafile);
	}
	fclose(dataFile);
}

void reverseStrings(char * array){
	Stack reverseStack = newStack();
	int i=0,j=0;
	char result[inputSize];
	while(i<inputSize){
		while((*array[i]) != 32){
			reverseStack.push(*array[i]);
			i++;
		}
		i++;
		for(j;j<i;j++){
			result[j]=reverseStack.pop();
		}
		j++;
		result[j]=32;
	}
	for(i=0;i<inputSize;i++){
		*array[i]=result[i];
	}
}

void encrypt(char * input, int key){
	int i;
	for(i=0;i<inputSize;i++){
		*input[i] = (*input[i]+key)%256;
	}
}

struct Stack newStack(void){ //function to create a new stack
    struct Stack tmp;
    tmp.stack_buffer = NULL; //start empty
    return tmp;
}

void push(char elem, struct Stack * stack) { //function to append a element ot the top of a specific Stack
    struct s_listnode *new_node = (struct s_listnode *) malloc(sizeof(struct s_listnode));
    new_node->pnext = stack->stack_buffer;
    new_node->element = elem;
    stack->stack_buffer = new_node;
}

char pop(struct Stack * stack) { //function to pop the top element from a specific stack
    if (stack->stack_buffer) {
        struct s_listnode *pelem = stack->stack_buffer;
        char elem = stack->stack_buffer->element;
        stack->stack_buffer = pelem->pnext;
        free(pelem);
        return elem;
    } else {
        return 0;  
    }
}


