#include "stack.h"
#include "stack.c"


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
	stack * pS;
	int op=0;
	student * stu;

	pS = NULL;
	if ((stu = (student *)malloc(sizeof(student))) == NULL)
		exit(-1);

	do{
		 system("cls");
		 menu();
		 printf("          Please input your option[0-12]:");
		 scanf("%d",&op);
		 switch(op){
			 case 0: break;
			 case 1: //初始化栈
				 if ((pS = stack_init(sizeof(student))) == NULL)
					 exit(-1);
				 printf("初始化成功!");
							 getchar();getchar();
							 break;
			 case 2: //销毁栈
				 if (stack_destroy(&pS) == TRUE)
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
				 
			 case 3: //清空栈
				 if (stack_clear(pS) == TRUE)
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
				 if (stack_exist(pS) == FALSE)
				 {
					 printf("不存在!");
					 getchar();getchar();
					 break;
				 }
				 else
				 {
					 printf("栈存在!");
					 getchar();getchar();
				 }
					break;
			 case 5: //判断是否为空栈
				 if (stack_exist(pS) == FALSE)
				 {
					 printf("栈不存在!");
					 getchar();getchar();
					 break;
				 }
				 if (stack_empty(pS) == TRUE)
				 {
					 printf("是空栈!");
					 getchar();getchar();
					 break;
				 }
				 printf("不是空栈!");
							 getchar();getchar();
							 break;
			 case 6: //栈的元素个数
				 printf("元素个数是%d", stack_length(pS));
							 getchar();getchar();
							 break;
			 case 7: //取栈顶元素
				 if (stack_gettop(pS, stu) == FALSE)
				 {
					 printf("操作失败!");
					 getchar();getchar();
					 break;
				 }
				 display(stu);
							 getchar();getchar();
							 break;
			 case 8: //入栈
				 inputstu(stu);
				 if (stack_push(pS, stu) == TRUE)
				 {
					 printf("入栈成功!");
				 	 getchar();getchar();
					 break;
				 }
				 else
				 {
					 printf("入栈失败!");
					 getchar();getchar();
					 break;
				 }

			 case 9: //出栈
				 if (stack_pop(pS, stu) == FALSE)
				 {
					 printf("操作失败!");
					 getchar();getchar();
					 break;
				 }
				 display(stu);
				 getchar();getchar();
				 break;
			 case 10: //遍历
				 if (stack_exist(pS) == FALSE || stack_empty(pS) == TRUE)
				 {
					 printf("栈不存在或为空!");
					 getchar();getchar();
					break;
				 }
				 stack_traverse(pS, &display);
								getchar();getchar();
								break;
			 case 11: //保存到文件
				 if (savestack(pS) == TRUE)
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
				 if (loadstack(&pS) == TRUE)
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
	printf("      Menu for 栈的链表实现 \n");
	printf("------------------------------------------------------\n");
	printf("\t1. 初始化栈\n");
	printf("\t2. 销毁栈\n");
	printf("\t3. 清空栈\n");
	printf("\t4. 判断是否存在\n");
	printf("\t5. 判断是否为空\n");	
	printf("\t6. 求栈元素个数\n");
	printf("\t7. 取栈顶元素\n");
	printf("\t8. 入栈\n");
	printf("\t9. 出栈\n");
	printf("\t10.遍历栈的元素\n");
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