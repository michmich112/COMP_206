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
void reverseStrings(char *array);
void encrypt(char *input, int key);

int main(int argc, char* argv[]){
	printf("started \n");
	FILE * dataFile;
	char read,result[1000];
	int i;
	//for(i=0;i<1000;i++){result[i]='\0';}
	if((dataFile = fopen(argv[2], "r")) == NULL){
		printf("Can't read from file %s\n", argv[2]);
		exit(1);
	}
	i=0;
	printf("accessing data\n");
	while((read = fgetc(dataFile)) != EOF){
		printf("\taccessing %d\n",read);
		result[i] = read;
		i++;
	}
	fclose(dataFile);
	printf("data read!\n");
	//Set input size
	inputSize = i;
	reverseStrings(result);
	printf("strings revered\n");
	printf("starting encryption process\n");
	encrypt(result,atoi(argv[1]));
	printf("encrypted\n");

	FILE * resultFile;
	resultFile = fopen(argv[2],"w");
	for(i=0;i<1000;i++){
		if(result[i] != atoi(argv[1])){
			printf("\t putting %d \n",result[i]);
			fputc(result[i],resultFile);
		}
	}
	fclose(resultFile);
}

void reverseStrings(char *array){
	struct Stack reverseStack = newStack();
	int i=0,j=0;
	char result[inputSize];
	while(i<inputSize){
		while((array[i]) != 32 && array[i] != '\0' && array[i] != 10){
			printf("%d \n",i);
			push(array[i],&reverseStack);
			i++;
		}
		//i++;
		for(j=j;j<i;j++){
			result[j]=pop(&reverseStack);
		}
		j++;
		result[j]=32;
	}
	for(i=0;i<inputSize;i++){
		array[i]=result[i];
	}
}

void encrypt(char *input, int key){
	int i;
	for(i=0;i<inputSize;i++){
		printf("%c\t%d\n",input[i],input[i]);
		input[i] = (char) ((input[i] + key)%256);
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


