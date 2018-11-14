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
}stacknode;
typedef struct stack
{
	stacknode * top;
	stacknode * base;
	int stacksize;	//栈中元素个数
	int elemsize;	//每个数据的大小
} stack;

stack * stack_init(int elemsize);	//构造一个空栈
BOOL stack_push(stack * pS, void * stu);
BOOL stack_traverse(const stack * pS, void visit(void *stu));
BOOL stack_exist(const stack * pS);
BOOL stack_empty(const stack * pS);
BOOL stack_clear(stack * pS);
BOOL stack_destroy(stack ** pS);
int stack_length(const stack * pS);
BOOL stack_gettop(const stack * pS, void * pe);
BOOL stack_pop(stack * pS, void * pe);

BOOL savestack(const stack * pS);
BOOL loadstack(stack ** pS);
