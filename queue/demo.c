#include "queue.h"
#include "queue.c"

typedef struct student
{
	char name[20];
	int age;
} student;
void display(void *stu);
void menu(void);
void inputstu(student * p);

int main(void)
{
	queue * pQue;
	int op=0;
	student * stu;

	pQue = NULL;
	if ((stu = (student *)malloc(sizeof(student))) == NULL)
		exit(-1);

	do{
		 system("cls");
		 menu();
		 printf("          Please input your option[0-12]:");
		 scanf("%d",&op);
		 switch(op){
			 case 0: break;
			 case 1: //初始化队列
				 if ((pQue = queue_init(sizeof(student))) == NULL)
					 exit(-1);
				 printf("初始化成功!");
							 getchar();getchar();
							 break;
			 case 2: //销毁队列
				 if (queue_destroy(&pQue) == TRUE)
				 {
					 printf("销毁成功!");
							 getchar();getchar();
							 break;
				 }
				 else
				 {
					 printf("销毁失败!");
					 getchar();getchar();
					 break;
				 }
				 
			 case 3: //清空队列
				 if (queue_clear(pQue) == TRUE)
				 {
					 printf("清空成功!");
					 getchar();getchar();
					 break;
				 }
				 else
				 {
					 printf("清空失败!");
					 getchar();getchar();
					 break;
				 }
			 case 4: //判断是否存在
				 if (queue_exist(pQue) == FALSE)
				 {
					 printf("不存在!");
					 getchar();getchar();
					 break;
				 }
				 else
				 {
					 printf("队列存在!");
					 getchar();getchar();
				 }
					break;
			 case 5: //判断是否为空队列
				 if (queue_exist(pQue) == FALSE)
				 {
					 printf("队列不存在!");
					 getchar();getchar();
					 break;
				 }
				 if (queue_empty(pQue) == TRUE)
				 {
					 printf("是空队列!");
					 getchar();getchar();
					 break;
				 }
				 printf("不是空队列!");
							 getchar();getchar();
							 break;
			 case 6: //队列的元素个数
				 printf("元素个数是%d", queue_length(pQue));
							 getchar();getchar();
							 break;
			 case 7: //取队列顶元素
				 if (queue_gethead(pQue, stu) == FALSE)
				 {
					 printf("操作失败!");
					 getchar();getchar();
					 break;
				 }
				 display(stu);
							 getchar();getchar();
							 break;
			 case 8: //入队列
				 inputstu(stu);
				 if (enqueue(pQue, stu) == TRUE)
				 {
					 printf("入队列成功!");
				 	 getchar();getchar();
					 break;
				 }
				 else
				 {
					 printf("入队列失败!");
					 getchar();getchar();
					 break;
				 }

			 case 9: //出队列
				 if (dequeue(pQue, stu) == FALSE)
				 {
					 printf("操作失败!");
					 getchar();getchar();
					 break;
				 }
				 display(stu);
				 getchar();getchar();
				 break;
			 case 10: //遍历
				 if (queue_exist(pQue) == FALSE || queue_empty(pQue) == TRUE)
				 {
					 printf("队列不存在或为空!");
					 getchar();getchar();
					break;
				 }
				 queue_traverse(pQue, &display);
								getchar();getchar();
								break;
			 case 11: //保存到文件
				 if (savequeue(pQue) == TRUE)
				 {
					 printf("保存成功!");
					 getchar();getchar();
					 break;
				 }
				 else
				{
					printf("保存失败!");
					getchar();getchar();
					break;
				 }
			 case 12: //从文件加载
				 if (loadqueue(&pQue) == TRUE)
				 {
					 printf("加载成功!");
					 getchar();getchar();
					 break;
				 }
				 else
				 {
					 printf("加载失败!");
					 getchar();getchar();
					 break;
				 }
			 default: 
				 break;
		 }
	}while(op);
	printf("\n--------------------Welcome again!--------------------\n");
	getchar();getchar();	
	
	return 0;
}


void display(void *stu)
{
	printf("姓名:%s\t年龄%d\n", ((student *)stu)->name, ((student *)stu)->age);
}
void menu(void){
	printf("\n\n");
	printf("      Menu for 队列的链表实现 \n");
	printf("------------------------------------------------------\n");
	printf("\t1. 初始化队列\n");
	printf("\t2. 销毁队列\n");
	printf("\t3. 清空队列\n");
	printf("\t4. 判断是否存在\n");
	printf("\t5. 判断是否为空\n");	
	printf("\t6. 求队列元素个数\n");
	printf("\t7. 取队列顶元素\n");
	printf("\t8. 入队列\n");
	printf("\t9. 出队列\n");
	printf("\t10.遍历队列的元素\n");
	printf("\n\t11. Savelist\t\t12. Loadlist\n");
	printf("    	  0. Exit\n");
	printf("------------------------------------------------------\n");
	
}
void inputstu(student * p)
{
	printf("请输入学生姓名:");
	scanf("%s", p->name);
	printf("请输入年龄:");
	scanf("%d", &p->age);
	
}