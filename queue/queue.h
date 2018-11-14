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
	int queuesize;	//������Ԫ�ظ���
	int elemsize;	//ÿ�����ݵĴ�С
} queue;

queue * queue_init(int elemsize);	//����һ���ն���
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