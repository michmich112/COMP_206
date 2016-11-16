#include <stdio.h>
#include <sdtlib.h>

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

//functions for the main decryption program
int size(char array);
void reverseStrings(char * array);
void printResult(char * array);
void decrypt(char* input, int key);

int main(int argc, char* argv[]){
	//getting the data
	FILE * dataFile;
	char read, result[1000];
	int i;
	for(i=0; i<1000; i++){result[i]='\0';}
	if((dataFile = fopen(argv[2], "r")) == NULL){
		printf("Can't read from file %s\n", argv[2]);
		exit(1);
	}
	i=0;
	while((read == fgetc(dataFile))!= EOF){
		result[i]=read;
		i++;
	}
	decrypt(&result,atoi(argv[1]));
	reverseStrings(&result);
	printResult(&result);

	return 0;
}

void reverseStrings(char * array){
	Stack reverseStack = newStack();
	int i=0,j=0;
	char result[size(*array)];
	while(i<size(*array)){
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
	for(i=0;i<size(*array);i++){
		*array[i]=result[i];
	}
}

void decrypt(char* input, int key){
	int i;
	for(i=0;i<size(input);i++){
		 *input[i] = (*input[i] - key)%256;
	}
}

void printResults(char * array){
	int i;
	for(i=0;i<size(*array);i++){
		printf("%c",*array[i]);
	}
	printf("\n");
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

int size(char array){
	int i=0;
	while(array[i]!= '\0'){
		i += 1;
	}
	return i;
}
