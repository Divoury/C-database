#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

//链表结点结构 存储一个结点
typedef struct listnode{
	void * pelem;	//抽象的数据域 可以指向任何类型
	struct listnode * pre;	//指向上一个结点
	struct listnode * next;	//指向下一个结点
} listnode;
//链表结构 储存整个链表
typedef struct list{
	int elemsize;	//链表结点指向的数据域的大小
	int listsize;	//链表中元素的个数
	struct listnode header;	//头结点
	struct listnode trailer;	//尾结点
} list;

list * list_init(int elemsize);	//初始化链表
BOOL getpos_invalid(list * pL, int i);	//判断取值元素的位置是否符合要求
BOOL list_exist(list * pL);	//判断链表是否存在
BOOL list_empty(list * pL);	//判断链表是否为空 若不存在则不为空
BOOL getpos_invalid(list * pL, int i);	//判断元素位置是否合法
BOOL putpos_invalid(list * pL, int i);	//判断要插入的位置是否合法 尾指针算一个
BOOL list_getelem(list * pL, int i, void * pe);	//取第几个元素放到pe指向的结构
listnode * list_getp(list * pL, int i);	//根据位置返回该位置的结点指针，可能是尾指针
BOOL list_insert(list * pL, listnode * p, void * pe);	//在某结点位置前插入结点 可能是尾结点之前
BOOL list_travel(list * pL, void visit());	//遍历链表 执行visit操作
BOOL list_clear(list * pL);	//清空链表
BOOL list_destroy(list ** pL);	//销毁链表
BOOL list_remove(list * pL, listnode * pnode, void *p);	//删除一个元素
int list_length(list * pL);	//判断列表长度
int list_locateelem(list * pL, void * pe, BOOL compare());
BOOL list_priorelem(list * pL, void * pe, void * pre_e);
BOOL list_nextelem(list * pL, void * pe, void * pre_e);
BOOL equal(void * a, void * b);

BOOL savelist(list * pL);
BOOL loadlist(list ** pL);