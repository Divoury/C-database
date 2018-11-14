#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define BOOL int
#define TRUE 1
#define FALSE 0


typedef struct Node
{
	void * pdata;
	struct Node * pNext;
}queuenode;
typedef struct queue
{
	queuenode * front;
	queuenode * rear;
	int queuesize;	//队列中元素个数
	int elemsize;	//每个数据的大小
} queue;

queue * queue_init(int elemsize);	//构造一个空队列
BOOL enqueue(queue * pQue, void * stu);
BOOL queue_traverse(const queue * pQue, void visit(void *stu));
BOOL queue_exist(const queue * pQue);
BOOL queue_empty(const queue * pQue);
BOOL queue_clear(queue * pQue);
BOOL queue_destroy(queue ** pQue);
int queue_length(const queue * pQue);
BOOL queue_gethead(const queue * pQue, void * pe);
BOOL dequeue(queue * pQue, void * pe);

BOOL savequeue(const queue * pQue);
BOOL loadqueue(queue ** pQue);