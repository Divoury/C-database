#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

#define INIT_LENGTH 10

typedef struct LinearList{
	ElemType * _elem;	//指向具体元素的指针
	int _size;		//当前元素规模
	int capacity;	//总容量
	int elemsize;	//每个元素大小
} LinearList;

//内部
BOOL putpos_invalid(LinearList * pL, int i);	//判断要插入元素的位置是否符合要求
BOOL getpos_invalid(LinearList * pL, int i);	////判断取值元素的位置是否符合要求
BOOL list_expand(LinearList * pL);	//扩大数组容量
BOOL equal(ElemType a, ElemType b);	//判断元素是否相等

//查找类
BOOL list_exist(LinearList * pL);	//判断列表是否存在
BOOL list_travel(LinearList * pL, BOOL (* visit)(ElemType e));	//遍历元素
BOOL list_empty(LinearList * pL);	//判断是否为空表
int list_length(LinearList * pL);	//求列表元素个数
BOOL list_getelem(LinearList * pL, int i, ElemType * pe);	//将L中第i个元素送入e中
int list_locateelem(LinearList * pL,const ElemType * pe, BOOL compare());	//查找L中第一个和pe满足关系compare的元素 返回位置
BOOL list_priorelem(LinearList * pL, const ElemType * pe, ElemType * pre_e);
BOOL list_nextelem(LinearList * pL, const ElemType * pe, ElemType * next_e);

//修改类
LinearList * list_init(int elemsize);	//初始化列表
BOOL list_insert(LinearList * pL, int i, ElemType * pe);	//插入元素
BOOL list_destroy(LinearList ** pL);	//销毁列表
BOOL list_clear(LinearList * pL);	//清空列表
BOOL list_delete(LinearList * pL, int lo, int hi);	//删除lo至hi区间的所有元素
BOOL list_remove(LinearList * pL, int i, ElemType * pe);	//删除i元素并放到pe中

//文件类
BOOL savelist(LinearList * pL);
BOOL loadlist(LinearList ** pL);


