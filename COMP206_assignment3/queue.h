#ifndef ENCRYPTION_H
# define ENCRYPTION_H

struct s_listnode {
    char element;
    struct s_listnode * pnext;
};

struct queueData {
    struct s_listnode *queue_buffer; //start empty
    struct s_listnode *prear; //start empty
};

struct queueData newQueue(void);
void enqueue(char elem,struct queueData * data);
char dequeue(struct queueData * data);

#endif