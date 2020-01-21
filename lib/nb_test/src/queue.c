#include "queue.h"
#include <stdio.h>
#include <stdbool.h>

void queue_init(struct Queue *queue, unsigned short max_size){
    queue->max_size = max_size;
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
}

void *queue_frond(struct Queue *queue){
    if(queue->size == 0){
        return NULL;
    }else{
        return queue->head;
    }
}

void *queue_back(struct Queue *queue){
    if(queue->size == 0){
        return NULL;
    }else{
        return queue->tail;
    }
}

void queue_pop(struct Queue *queue){
    if(queue->size != 0){
        queue->head = (struct Node *)(queue->head)->next;
        --queue->size;
    }
}

enum STATUS queue_push(struct Queue *queue, void *element){
    if(queue->size < queue->max_size){
        if(queue->size == 0){
            queue->head = element;
            queue->tail = element;
        }else{
            (queue->tail)->next = (struct node *)element;
            queue->tail = element;
        }
        ++queue->size;
        return QUEUE_SUCCESS;
    }else{
        return QUEUE_FAIL;
    }
}

unsigned short queue_size(struct Queue *queue){
    return queue->size;
}

void *queue_find(struct Queue *queue, bool (*conditionFunction)(void *element, unsigned short pos, void *arg), void *arg){
    struct Node *node = queue->head;
    unsigned short pos = 0;
    if(queue->size != 0){
        while(queue->size != pos){
            if(conditionFunction(node, pos, arg)){
                return node;
            }
            node = (struct Node *)node->next;
            ++pos;
        }
    }
    return NULL;
}

void *queue_pop_element(struct Queue *queue, bool (*conditionFunction)(void *element, unsigned short pos, void *arg), void *arg){
    struct Node *node = queue->head;
    struct Node *passNode = queue->head;
    unsigned short pos = 0;

    if(queue->size != 0){
        if(conditionFunction(node, pos, arg)){
            queue->head = (struct Node *)node->next;
            queue->size = queue->size - 1;
            return node;            
        }else{
            passNode = node;
            node = (struct Node *)node->next;
            ++pos;

            while(queue->size != pos){
                if(conditionFunction(node, pos, arg)){
                    if(node == queue->tail){
                        queue->tail = passNode;
                        queue->size = queue->size - 1;
                        return node;     
                    }else{
                        passNode->next = node->next;
                        queue->size = queue->size - 1;
                        return node; 
                    }
                }else{
                    passNode = node;
                    node = (struct Node *)node->next;
                    ++pos;
                }
            }
        }
    }
    return NULL;
}


#if DEBUG
	void printQueueAddressChain(struct Queue *queue){
        struct Node *node = queue->head;
        unsigned short pos = 0;
        printf(" ---------- queue chain start ----------\n");
        printf("head : %ld \n", (unsigned long)node);
        if(queue->size != 0){
            while(queue->size != pos){
                printf(" %ld ->\n", (unsigned long)node);
                if(node != queue->tail){
                    node = (struct Node *)node->next;
                }else{
                    printf("tail : %ld \n", (unsigned long)node);
                }
                ++pos;
            }
        }
        printf(" ---------- queue chain end -----------\n");
    }
#endif
