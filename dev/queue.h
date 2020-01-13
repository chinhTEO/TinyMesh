#ifndef QUEUE_H_
#define QUEUE_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdbool.h>

enum STATUS {
    QUEUE_FAIL,
    QUEUE_SUCCESS
};

struct Node {
    struct node *next;
};

struct Queue {
	unsigned short size;
	unsigned short max_size;
	struct Node *head;
	struct Node *tail;
};

void queue_init(struct Queue *queue, unsigned short max_size);
void *queue_frond(struct Queue *queue);
void *queue_back(struct Queue *queue);
void queue_pop(struct Queue *queue);
enum STATUS queue_push(struct Queue *queue, void *element);
unsigned short queue_size(struct Queue *queue);

void *queue_find(struct Queue *queue, bool (*conditionFunction)(void *element, unsigned short pos, void *arg), void *arg);
enum STATUS queue_remove(struct Queue *queue, bool (*conditionFunction)(void *element, unsigned short pos));

#ifdef __cplusplus
} // closing brace for extern "C"
#endif
#endif