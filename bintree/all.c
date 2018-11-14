#include "stack.h"
#include "stack.c"
#include "queue.h"
#include "queue.c"
#include <stdio.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

#define MAX_NAME 20

/******用户定义******/
typedef struct student
{
	char name[MAX_NAME];
	int age;
} student;
student * inputstu(void);
BOOL display(void * p);
void menu(void);
/************/

typedef struct binnode
{
	struct binnode * lchild;
	struct binnode * rchild;
	struct binnode * parent;
	void * pdata;
	int height;
} binnode;
typedef struct bintree
{	
	int size;	//规模
	int elemsize;	//每个节点数据域的大小
	binnode * root;	//树根指针
	
} bintree;

BOOL visitnode(binnode * p, BOOL visit(void *),BOOL opernode(binnode * p));//对结点操作
BOOL donothing(binnode * p);	//什么也不做
BOOL countleafnode(binnode * p);	//计数叶子节点 globalnum增加1 


bintree * bintree_init(int elemsize);
BOOL create_by_preorder1(bintree * ptree, binnode * parent, binnode ** p,  student * input(void));
BOOL create_by_preorder(bintree * p, student * input(void));
BOOL pre_traverse1(binnode * p, BOOL visit(void *), BOOL opernode(binnode * p));	//递归先序遍历
BOOL pre_traverse2(binnode * p, BOOL visit(void *), BOOL opernode(binnode * p));	//非递归先序遍历算法1
BOOL pre_traverse3(binnode * p, BOOL visit(void *), BOOL opernode(binnode * p));	//非递归先序遍历算法2
BOOL visitAlongLeftBranch(binnode * p, BOOL visit(void *), stack * pS, BOOL opernode(binnode * p));//沿左侧链遍历左孩子 并右孩子入栈
BOOL goAlongLeftBranch(binnode ** p, BOOL visit(void *), stack * pS);//沿左侧深入 左孩子入栈
BOOL in_traverse2(binnode * p, BOOL visit(void *), BOOL opernode(binnode * p));	//非递归中序遍历
BOOL post_traverse1(binnode * p, BOOL visit(void *), BOOL opernode(binnode * p));//递归后序遍历
int getleafnum(bintree * ptree);//计算叶子数目
BOOL level_traverse(bintree * ptree, BOOL visit(void *), BOOL opernode(binnode * p));	//层次遍历
int bintree_height(binnode * p);// 求高度

BOOL bintree_empty(bintree * p);
BOOL bintree_exist(bintree * p);
BOOL bintree_clear(bintree * ptree);
BOOL bintree_destroy(bintree ** ptree);
BOOL savebintree(bintree * ptree);
BOOL loadbintree(bintree ** ptree);

int globalnum = 0;	//全局变量

void main(void){
	bintree * ptree;
	binnode * pnode;
	student * pstu;
	int num;
	int op=0;
	num = 0;
	ptree = NULL;
	do{
		 system("cls");
		 menu();
		 printf("          Please input your option[0-12]:");
		 scanf("%d",&op);
		 getchar();
		 switch(op){
			 case 0: break;
			 case 1: //初始化二叉树
				 if ((ptree = bintree_init(sizeof(student))) == NULL)
				 {
					 printf("初始化失败!");
					 getchar();
							 break;
				 }
				 printf("初始化成功!");
							 getchar();
							 break;
			 case 2: //按先序序列生成二叉树
				 if ((create_by_preorder(ptree,&inputstu)) == FALSE)
				 {
					 printf("建立失败!");
					 getchar();
					 break;
				 }
				 printf("建立成功!");
				 getchar();
							 break;
			 case 3: //先序遍历
				 if (bintree_exist(ptree) == FALSE)
				 {
					 printf("树不存在!");
					 getchar();
					 break;
				 }

				 if ((pre_traverse3(ptree->root, &display, &donothing)) == FALSE)
					 printf("空树!");
							 getchar();
							 break;
			 case 4: //中序遍历
				 if (bintree_exist(ptree) == FALSE)
				 {
					 printf("树不存在!");
					 getchar();
					 break;
				 }
				 
				 if ((in_traverse2(ptree->root, &display, &donothing)) == FALSE)
					 printf("空树!");
				 getchar();
							 break;
							
			 case 5: //后序遍历
				 if (bintree_exist(ptree) == FALSE || bintree_empty(ptree) == TRUE)
				 {
					 printf("树不存在或为空!");
					 getchar();
					 break;
				 }				 
				 post_traverse1(ptree->root, &display, &donothing);
				 getchar();
							 break;
			 case 6: //层次遍历
				 if (bintree_exist(ptree) == FALSE || bintree_empty(ptree) == TRUE)
				 {
					 printf("树不存在或为空!");
					 getchar();
					 break;
				 }				 
				level_traverse(ptree, &display, &donothing);
				 getchar();
							 break;
			 case 7: //叶子数目
				 num = getleafnum(ptree);
				 printf("叶子节点有%d个!\n", num);
							 getchar();
							 break;
			 case 8: //求二叉树高度
				 if (bintree_exist(ptree) == FALSE)
				 {
					 printf("树不存在");
					 getchar();
					 break;
				 }				 
				 printf("树的高度是%d\n", bintree_height(ptree->root));
				 getchar();
							 break;
			 case 9: //判断是否为空
				 if (bintree_empty(ptree) == TRUE)
				 {
					 printf("是空树!");
					 getchar();
					 break;
				 }
				 printf("不是空树!");
				 getchar();
							 break;
			 case 10: //判断是否存在
				 if (bintree_exist(ptree) == TRUE)
				 {
					 printf("树存在!");
					 getchar();
					 break;
				 }
				 printf("树不存在!");
				 getchar();
							 break;
			 case 11: //清空二叉树
				 if (bintree_clear(ptree) == TRUE)
				 {
					 printf("清空成功!");
					 getchar();
					 break;
				 }
				 printf("清空失败!");
				 getchar();
							 break;
			 case 12: //销毁二叉树
				 if (bintree_destroy(&ptree) == TRUE)
				 {
					 printf("销毁成功!");
					 getchar();
					 break;
				 }
				 printf("销毁失败!");
				 getchar();
							 break;
			 case 21: //保存到文件
								getchar();
								break;
			 case 22: //从文件加载

								 
								 getchar();
								 break;
								
			 default: ;
		 }
	}while(op);
	printf("\n--------------------Welcome again!--------------------\n");
	getchar();getchar();

	return 0;
}

bintree * bintree_init(int elemsize)
{
	bintree * p;
	if ((p = (bintree *)malloc(sizeof(bintree))) == NULL)
		exit(-1);
	p->elemsize = elemsize;
	p->root = NULL;
	p->size = 0;

	return p;
}
BOOL create_by_preorder(bintree * p, student * input(void))
{
	binnode * pnode;
	void * data;
	
	data = input();
	if (data == NULL)
		p->root = NULL;
	else
	{
		if ((pnode = (binnode *)malloc(sizeof(binnode))) == NULL)
			exit(-1);
		p->root = pnode;
		pnode->pdata = malloc(p->elemsize);
		memcpy(pnode->pdata, data, p->elemsize);
		p->size++;

		create_by_preorder1(p, pnode, &pnode->lchild, input);
		create_by_preorder1(p, pnode, &pnode->rchild, input);

	}
	return TRUE;
}

BOOL create_by_preorder1(bintree * ptree, binnode * parent, binnode ** p,  student * input(void))
{
	binnode * pnode;
	void * data;
	
	data = input();
	if (data == NULL)
		(*p) = NULL;
	else
	{
		if (((*p) = (binnode *)malloc(sizeof(binnode))) == NULL)
			exit(-1);
		(*p)->pdata = malloc(ptree->elemsize);
		memcpy((*p)->pdata, data, ptree->elemsize);
		(*p)->parent = parent;
		ptree->size++;
		create_by_preorder1(ptree, (*p), &(*p)->lchild, input);
		create_by_preorder1(ptree, (*p), &(*p)->rchild, input);
	}
	return TRUE;
}
BOOL pre_traverse1(binnode * p, BOOL visit(void *), BOOL opernode(binnode * p))
{
	if (p != NULL)
	{
		if (visitnode(p, visit, opernode) == TRUE)
		{
			if (pre_traverse1(p->lchild, visit, opernode))
			{
				if (pre_traverse1(p->rchild, visit, opernode))
					return TRUE;
			}

		}
		return FALSE;

	}
	else
	{
		return TRUE;
	}

}
BOOL pre_traverse2(binnode * p, BOOL visit(void *), BOOL opernode(binnode * p))
{
	stack * pS;	//构造辅助栈
	if (p == NULL) return FALSE;
	if ((pS = stack_init(sizeof(binnode))) == NULL)
		return FALSE;
	stack_push(pS,p);//根节点入栈
	while (stack_empty(pS) == FALSE)
	{
		stack_pop(pS, p);
		visitnode(p, visit, opernode);
		if (p->rchild != NULL) stack_push(pS, p->rchild);
		if (p->lchild != NULL) stack_push(pS, p->lchild);
	}
	stack_destroy(&pS);	//销毁栈
	return TRUE;
}
BOOL visitAlongLeftBranch(binnode * p, BOOL visit(void *), stack * pS, BOOL opernode(binnode * p))
{
	while (p != NULL)
	{
		visitnode(p, visit, opernode);
		stack_push(pS, &p->rchild);	//右孩子入栈 将来逆序出栈 可能为NULL
		p = p->lchild;	//沿左侧链下行
	}
	return TRUE;
}
BOOL pre_traverse3(binnode * p, BOOL visit(void *), BOOL opernode(binnode * p))
{
	
	stack * pS;
	if (p == NULL)
		return FALSE;
	
	pS = stack_init(sizeof(binnode *));
	while(TRUE)
	{
		visitAlongLeftBranch(p, visit, pS, opernode) == FALSE;	//访问左侧链
		if (stack_empty(pS) == TRUE)
			break;
		stack_pop(pS, &p);
	}
	return TRUE;
}
BOOL goAlongLeftBranch(binnode ** p, BOOL visit(void *), stack * pS)
{
	while (*p != NULL)
	{
		stack_push(pS, p);
		(*p) = (*p)->lchild;
	}

}
BOOL in_traverse2(binnode * p, BOOL visit(void *), BOOL opernode(binnode * p))
{
	stack * pS;
	pS = stack_init(sizeof(binnode *));
	if (p == NULL)
		return FALSE;
	while (TRUE)
	{
		goAlongLeftBranch(&p, visit, pS);
		if (stack_empty(pS) == TRUE)
			break;
		stack_pop(pS, &p);	//此时位于左侧链最下方
		visitnode(p, visit, opernode);//访问根节点
		p = p->rchild;	//访问右子树，可能为NULL
	}
	return TRUE;
}
BOOL post_traverse1(binnode * p, BOOL visit(void *), BOOL opernode(binnode * p))
{
	if (p == NULL)
		return TRUE;
	post_traverse1(p->lchild, visit, opernode);
	post_traverse1(p->rchild, visit, opernode);

	visitnode(p, visit, opernode);
}
int getleafnum(bintree * ptree)
{
	binnode * p;
	int i;
	i = 0;
	if (bintree_empty(ptree) == TRUE || bintree_exist(ptree) == FALSE)
		return 0;
	p = ptree->root;

	pre_traverse3(p, &donothing, &countleafnode);

	return globalnum;
}
BOOL level_traverse(bintree * ptree, BOOL visit(void *), BOOL opernode(binnode * p))
{
	queue * pQ;
	binnode ** temp;
	binnode * pnode;
	pQ = queue_init(sizeof(binnode *));	//该队列存放节点的位置
	temp = malloc(sizeof(binnode *));
	if (bintree_exist(ptree) == FALSE)
		return FALSE;
	if (bintree_empty(ptree) == TRUE)
		return FALSE;
	pnode = ptree->root;
	enqueue(pQ, &pnode);

	while (queue_empty(pQ) == FALSE)
	{
		dequeue(pQ, temp);
		visitnode((*temp), visit, opernode);
		
		if ((*temp)->lchild != NULL)
			enqueue(pQ, &(*temp)->lchild);
		if ((*temp)->rchild != NULL)
			enqueue(pQ, &(*temp)->rchild);
	}
}
int bintree_height(binnode * p)
{
	int m, n;
	if (p == NULL)
		return 0;
	else
	{
		m = bintree_height(p->lchild);
		n = bintree_height(p->rchild);
		
		return m > n ? (m+1) : (n+1);
	}
}



BOOL bintree_clear(bintree * ptree)
{
	binnode * pnode;
	binnode ** temp;
	stack * pS1;
	stack * pS2;
	temp = malloc(sizeof(binnode *));
	if (bintree_exist(ptree) == FALSE)
		return FALSE;
	if (bintree_empty(ptree) == TRUE)
		return TRUE;
	pnode = ptree->root;

	pS1 = stack_init(sizeof(binnode *));
	pS2 = stack_init(sizeof(binnode *));
	stack_push(pS1, &pnode);

	while (stack_empty(pS1) == FALSE)
	{
		stack_pop(pS1, temp);
		stack_push(pS2, temp);

		free((*temp)->pdata);

		if ((*temp)->rchild != NULL) stack_push(pS1, &(*temp)->rchild);
		if ((*temp)->lchild != NULL) stack_push(pS1, &(*temp)->lchild);
	}
	while (stack_empty(pS2) == FALSE)
	{
		stack_pop(pS2, temp);
		free((*temp));
	}
	ptree->root = NULL;
	ptree->size = 0;

	stack_destroy(&pS1);
	stack_destroy(&pS2);

	return TRUE;
}
BOOL bintree_destroy(bintree ** ptree)
{
	if ((*ptree) == NULL)
		return TRUE;
	if (bintree_clear(*ptree) == FALSE)
		return FALSE;
	free(*ptree);
	(*ptree) = NULL;
	return TRUE;
}

BOOL bintree_empty(bintree * p)
{
	if (bintree_exist(p) == FALSE)
		return FALSE;
	if (p->size == 0)
		return TRUE;
	return FALSE;

}
BOOL bintree_exist(bintree * p)
{
	return p==NULL ? FALSE : TRUE;
}




BOOL savebintree(bintree * ptree)
{

}
BOOL loadbintree(bintree ** ptree)
{

}
//树的节点 第二个函数是对节点数据的操作 第三个函数是对结点的操作
BOOL visitnode(binnode * p, BOOL visit(void *),BOOL opernode(binnode * p))
{
	opernode(p);
	if (visit(p->pdata) == TRUE)
		return TRUE;

}
BOOL donothing(binnode * p)
{
	return TRUE;
}
BOOL countleafnode(binnode * p)
{
	if (p->lchild == NULL && p->rchild == NULL)
		globalnum++;

	return TRUE;
}


/*用户定义*/
student * inputstu(void)
{
	char c;
	int i;
	student * p;
	if ((p = malloc(sizeof(student))) == NULL)
		exit(-1);
	printf("请输入姓名 年龄。如果是空 直接输入空格并回车\n");
	if ((c = getchar()) == ' ')
	{	getchar();
		return NULL;
	}

	scanf("%s %d", p->name, &p->age);
	getchar();
	for (i = 0; p->name[i] != '\0' && i < MAX_NAME; i++)
		;
	for (; i >= 0; i--)
		p->name[i+1] = p->name[i];
	
	p->name[0] = c;

	return p;	
}
BOOL display(void * p)
{
	student * stu;
	if (p == NULL)
		return FALSE;
	
	stu = (student *)p;
	printf("姓名:%s", stu->name);
	printf("\t年龄:%d\n", stu->age);
	return TRUE;
}
void menu(void){
	printf("\n\n");
	printf("      二叉树操作 \n");
	printf("------------------------------------------------------\n");
	printf("    	  1. 初始化二叉树\t11.清空二叉树\n");
	printf("    	  2. 按先序遍历建立二叉树\t12.销毁二叉树\n");
	printf("    	  3. 先序遍历\n");
	printf("    	  4. 中序遍历\n");
	printf("    	  5. 后序遍历\n");
	printf("    	  6. 层次遍历\n");
	printf("    	  7. 计算叶子数目\n");
	printf("    	  8. 求二叉树高度\n");
	printf("    	  9.判断是否为空\n");
	printf("    	  10.判断是否存在\n");
	printf("    	  0. Exit\n");
//	printf("    	  21.保存到文件\t\t22.从文件加载\n");
	printf("------------------------------------------------------\n");
	
}