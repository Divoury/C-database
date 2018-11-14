#include "stack.h"
#include "stack.c"
#include "queue.h"
#include "queue.c"
#include <stdio.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

#define MAX_NAME 20

/******�û�����******/
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
	int size;	//��ģ
	int elemsize;	//ÿ���ڵ�������Ĵ�С
	binnode * root;	//����ָ��
	
} bintree;

BOOL visitnode(binnode * p, BOOL visit(void *),BOOL opernode(binnode * p));//�Խ�����
BOOL donothing(binnode * p);	//ʲôҲ����
BOOL countleafnode(binnode * p);	//����Ҷ�ӽڵ� globalnum����1 


bintree * bintree_init(int elemsize);
BOOL create_by_preorder1(bintree * ptree, binnode * parent, binnode ** p,  student * input(void));
BOOL create_by_preorder(bintree * p, student * input(void));
BOOL pre_traverse1(binnode * p, BOOL visit(void *), BOOL opernode(binnode * p));	//�ݹ��������
BOOL pre_traverse2(binnode * p, BOOL visit(void *), BOOL opernode(binnode * p));	//�ǵݹ���������㷨1
BOOL pre_traverse3(binnode * p, BOOL visit(void *), BOOL opernode(binnode * p));	//�ǵݹ���������㷨2
BOOL visitAlongLeftBranch(binnode * p, BOOL visit(void *), stack * pS, BOOL opernode(binnode * p));//��������������� ���Һ�����ջ
BOOL goAlongLeftBranch(binnode ** p, BOOL visit(void *), stack * pS);//��������� ������ջ
BOOL in_traverse2(binnode * p, BOOL visit(void *), BOOL opernode(binnode * p));	//�ǵݹ��������
BOOL post_traverse1(binnode * p, BOOL visit(void *), BOOL opernode(binnode * p));//�ݹ�������
int getleafnum(bintree * ptree);//����Ҷ����Ŀ
BOOL level_traverse(bintree * ptree, BOOL visit(void *), BOOL opernode(binnode * p));	//��α���
int bintree_height(binnode * p);// ��߶�

BOOL bintree_empty(bintree * p);
BOOL bintree_exist(bintree * p);
BOOL bintree_clear(bintree * ptree);
BOOL bintree_destroy(bintree ** ptree);
BOOL savebintree(bintree * ptree);
BOOL loadbintree(bintree ** ptree);

int globalnum = 0;	//ȫ�ֱ���

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
			 case 1: //��ʼ��������
				 if ((ptree = bintree_init(sizeof(student))) == NULL)
				 {
					 printf("��ʼ��ʧ��!");
					 getchar();
							 break;
				 }
				 printf("��ʼ���ɹ�!");
							 getchar();
							 break;
			 case 2: //�������������ɶ�����
				 if ((create_by_preorder(ptree,&inputstu)) == FALSE)
				 {
					 printf("����ʧ��!");
					 getchar();
					 break;
				 }
				 printf("�����ɹ�!");
				 getchar();
							 break;
			 case 3: //�������
				 if (bintree_exist(ptree) == FALSE)
				 {
					 printf("��������!");
					 getchar();
					 break;
				 }

				 if ((pre_traverse3(ptree->root, &display, &donothing)) == FALSE)
					 printf("����!");
							 getchar();
							 break;
			 case 4: //�������
				 if (bintree_exist(ptree) == FALSE)
				 {
					 printf("��������!");
					 getchar();
					 break;
				 }
				 
				 if ((in_traverse2(ptree->root, &display, &donothing)) == FALSE)
					 printf("����!");
				 getchar();
							 break;
							
			 case 5: //�������
				 if (bintree_exist(ptree) == FALSE || bintree_empty(ptree) == TRUE)
				 {
					 printf("�������ڻ�Ϊ��!");
					 getchar();
					 break;
				 }				 
				 post_traverse1(ptree->root, &display, &donothing);
				 getchar();
							 break;
			 case 6: //��α���
				 if (bintree_exist(ptree) == FALSE || bintree_empty(ptree) == TRUE)
				 {
					 printf("�������ڻ�Ϊ��!");
					 getchar();
					 break;
				 }				 
				level_traverse(ptree, &display, &donothing);
				 getchar();
							 break;
			 case 7: //Ҷ����Ŀ
				 num = getleafnum(ptree);
				 printf("Ҷ�ӽڵ���%d��!\n", num);
							 getchar();
							 break;
			 case 8: //��������߶�
				 if (bintree_exist(ptree) == FALSE)
				 {
					 printf("��������");
					 getchar();
					 break;
				 }				 
				 printf("���ĸ߶���%d\n", bintree_height(ptree->root));
				 getchar();
							 break;
			 case 9: //�ж��Ƿ�Ϊ��
				 if (bintree_empty(ptree) == TRUE)
				 {
					 printf("�ǿ���!");
					 getchar();
					 break;
				 }
				 printf("���ǿ���!");
				 getchar();
							 break;
			 case 10: //�ж��Ƿ����
				 if (bintree_exist(ptree) == TRUE)
				 {
					 printf("������!");
					 getchar();
					 break;
				 }
				 printf("��������!");
				 getchar();
							 break;
			 case 11: //��ն�����
				 if (bintree_clear(ptree) == TRUE)
				 {
					 printf("��ճɹ�!");
					 getchar();
					 break;
				 }
				 printf("���ʧ��!");
				 getchar();
							 break;
			 case 12: //���ٶ�����
				 if (bintree_destroy(&ptree) == TRUE)
				 {
					 printf("���ٳɹ�!");
					 getchar();
					 break;
				 }
				 printf("����ʧ��!");
				 getchar();
							 break;
			 case 21: //���浽�ļ�
								getchar();
								break;
			 case 22: //���ļ�����

								 
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
	stack * pS;	//���츨��ջ
	if (p == NULL) return FALSE;
	if ((pS = stack_init(sizeof(binnode))) == NULL)
		return FALSE;
	stack_push(pS,p);//���ڵ���ջ
	while (stack_empty(pS) == FALSE)
	{
		stack_pop(pS, p);
		visitnode(p, visit, opernode);
		if (p->rchild != NULL) stack_push(pS, p->rchild);
		if (p->lchild != NULL) stack_push(pS, p->lchild);
	}
	stack_destroy(&pS);	//����ջ
	return TRUE;
}
BOOL visitAlongLeftBranch(binnode * p, BOOL visit(void *), stack * pS, BOOL opernode(binnode * p))
{
	while (p != NULL)
	{
		visitnode(p, visit, opernode);
		stack_push(pS, &p->rchild);	//�Һ�����ջ ���������ջ ����ΪNULL
		p = p->lchild;	//�����������
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
		visitAlongLeftBranch(p, visit, pS, opernode) == FALSE;	//���������
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
		stack_pop(pS, &p);	//��ʱλ����������·�
		visitnode(p, visit, opernode);//���ʸ��ڵ�
		p = p->rchild;	//����������������ΪNULL
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
	pQ = queue_init(sizeof(binnode *));	//�ö��д�Žڵ��λ��
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
//���Ľڵ� �ڶ��������ǶԽڵ����ݵĲ��� �����������ǶԽ��Ĳ���
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


/*�û�����*/
student * inputstu(void)
{
	char c;
	int i;
	student * p;
	if ((p = malloc(sizeof(student))) == NULL)
		exit(-1);
	printf("���������� ���䡣����ǿ� ֱ������ո񲢻س�\n");
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
	printf("����:%s", stu->name);
	printf("\t����:%d\n", stu->age);
	return TRUE;
}
void menu(void){
	printf("\n\n");
	printf("      ���������� \n");
	printf("------------------------------------------------------\n");
	printf("    	  1. ��ʼ��������\t11.��ն�����\n");
	printf("    	  2. �������������������\t12.���ٶ�����\n");
	printf("    	  3. �������\n");
	printf("    	  4. �������\n");
	printf("    	  5. �������\n");
	printf("    	  6. ��α���\n");
	printf("    	  7. ����Ҷ����Ŀ\n");
	printf("    	  8. ��������߶�\n");
	printf("    	  9.�ж��Ƿ�Ϊ��\n");
	printf("    	  10.�ж��Ƿ����\n");
	printf("    	  0. Exit\n");
//	printf("    	  21.���浽�ļ�\t\t22.���ļ�����\n");
	printf("------------------------------------------------------\n");
	
}