#include <stdio.h>
#include <stdlib.h>

struct s_listnode {
    char element;
    struct s_listnode * pnext;
};

struct queueData {
    struct s_listnode *queue_buffer; //start empty
    struct s_listnode *prear; //start empty
};


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


int main(int argc, char *argv[]){
    struct queueData data = newQueue();
    enqueue('a',&data);
    enqueue('b',&data);
    enqueue('c',&data);
    printf("%c",dequeue(&data));
    printf("%c",dequeue(&data));
    printf("%c",dequeue(&data));
    return 0;
}
