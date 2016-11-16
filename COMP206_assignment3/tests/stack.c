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

// functions for the stack
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


