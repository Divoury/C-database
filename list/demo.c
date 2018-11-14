#include "list.h"
#include "list.c"

#define ElemType student
typedef struct {
	char name[20];
	int age;
} student;

void display(void *stu);
void menu(void);
void inputstu(student * p);	//输入学生信息
void inputindex(int *);	//输入位置信息


int main(void){
	list * pL;
	student * pe;
	listnode * pnode;
	student pre_e, next_e;
	int op;
	int i;
	op = 0;
	pL = NULL;
	if ((pe = (student *)malloc(sizeof(student))) == NULL)
		exit(-1);
	do{
		 system("cls");
		 menu();
		 printf("          Please input your option[0-12]:");
		 scanf("%d",&op);
		 switch(op){
			 case 0: break;
			 case 1: //初始化列表
				 if (list_exist(pL) == TRUE || list_empty(pL) == FALSE)
					 list_destroy(&pL);
				 if ((pL = list_init(sizeof(student))) != NULL)
				 {
					 printf("初始化成功!");
					  getchar();getchar();
				 }
				 else
				 {
					 printf("初始化失败!");
					  getchar();getchar();
				 }			 break;
			 case 2: //插入元素
				 inputindex(&i);
				 inputstu(pe);

				 if ((pnode = (list_getp(pL, i))) == NULL)
				 {
					 printf("位置不对或者链表不存在!");
					 getchar();getchar();
					 break;
				 }
				 if (list_insert(pL, pnode, pe) == TRUE)
					 printf("插入成功!");
				 else
					 printf("插入失败!");
				 getchar();getchar();
							 break;
			 case 3: //销毁列表
				 if(list_destroy(&pL) == TRUE)
					 printf("销毁成功!");
				getchar();getchar();
				break;
			 case 4: //清空列表
				 if(list_clear(pL) == TRUE)
				 {
					 printf("清空成功!");
					getchar();getchar();
				 }
				 else
				 {
					printf("列表不存在!");
				 	getchar();getchar();
				 }
				break;
		/*	 case 5: //删除区间
				 printf("请输入区间");
				 scanf("%d %d", &lo, &hi);
				 if(list_delete(pL, lo, hi) == FALSE)
				 {
					 printf("删除失败");
					getchar();getchar();
				 }
				 else
				{
					 printf("删除成功!");
					getchar();getchar();
				 }
				 break;*/
			 case 6: //删除某元素
				inputindex(&i);
				if (getpos_invalid(pL, i) == FALSE)
				{
					printf("位置不合法或列表不存在");
					getchar();getchar();
					break;
				}
				if ((pnode = list_getp(pL, i)) == NULL)
				{
					printf("删除失败!");
					getchar();getchar();
					break;
				}
				if(list_remove(pL, pnode, pe) == TRUE)
				{
					printf("第%d个元素", i);
					display(pe);
					printf("删除成功");
					getchar();getchar();
				}
				else
				{
					printf("删除失败!");
					getchar();getchar();
				}
							 
							 break;
			 case 7: //判断列表是否存在
				 if (list_exist(pL) == TRUE)
				 {
					 printf("列表存在!");
					 getchar();getchar();
				 }
				 else
				 {
					 printf("列表不存在!");
					 getchar();getchar();
				 }
				break;
			 case 8: //判断列表是否为空
				 if (list_exist(pL) == FALSE)
				 {
					 printf("列表不存在!");
					getchar();getchar();
					break;
				 }
				if (list_empty(pL) == TRUE)
				 {
					 printf("列表为空!");
					 getchar();getchar();
				 }
				 else
				 {
					 printf("列表不为空!");
					 getchar();getchar();
				 }
				 break;
			 case 9: //遍历元素
				 list_travel(pL, &display);
							 getchar();getchar();
							 break;
			 case 10: //求列表长度
				 if (list_exist(pL) == FALSE)
				 {
					 printf("列表不存在!");
					getchar();getchar();
					break;
				 }
				 printf("列表长度是%d", list_length(pL));
					getchar();getchar();
				break;
			 case 11: //按位置查找元素
				 inputindex(&i);
				if (getpos_invalid(pL, i) == FALSE)
				{
					printf("位置不合法或列表不存在");
					getchar();getchar();
					break;
				}
				if ((pnode = list_getp(pL, i)) == NULL)
				{
					printf("失败!");
					getchar();getchar();
					break;
				}
				display(pnode->pelem);
				getchar();getchar();
				break;
			 case 12: //按元素查找位置
				 inputstu(pe);
				 if ((i = list_locateelem(pL, (void *)pe, &equal)) == 0)
				 {
					 printf("查找失败!");
					getchar(); getchar();
				 }
				 else
				 {
					 printf("是第%d个元素", i);
					 getchar(); getchar();
				 }
								 break;
			 case 13: //求前驱元素
				 inputstu(pe);
				 if(list_priorelem(pL, pe, &pre_e) == TRUE)
				 {
					 display(pe);
					 printf("的前驱元素是");
					 display(&pre_e);
					getchar(); getchar();
				 }
				 else
				 {
					 printf("查找前驱元素失败!");
					 getchar(); getchar();
				 }
								 break; 
			 case 14: //求后继元素
				 	inputstu(pe);
				 if(list_nextelem(pL, pe, &next_e) == TRUE)
				 {
					 display(pe);
					 printf("的后继元素是");
					 display(&next_e);
					getchar(); getchar();
				 }
				 else
				 {
					 printf("查找后继元素失败!");
					 getchar(); getchar();
				 }
								 break;
			 case 15: //保存到文件
				 if(savelist(pL) == TRUE)
				 {
					 printf("保存成功!");
					 getchar(); getchar();
				 }
				 else
				 {
					 printf("保存失败!");
					 getchar(); getchar();
				 }
				break;
			 case 16: //从文件加载
				  if(loadlist(&pL) == TRUE)
				  {
					 printf("加载成功!");
					 getchar(); getchar();
				  }
				  else
				  {
					 printf("加载失败!");
					 getchar(); getchar();
				  }
				 break;							
			 default: ;
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
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("------------------------------------------------------\n");
	printf("\t修改类\t\t\t查找类\n");
	printf("\t1. 初始化列表\t\t7. 判断列表是否存在\n");
	printf("\t2. 插入元素\t\t8. 判断列表是否为空\n");
	printf("\t3. 销毁列表\t\t9. 遍历列表元素\n");
	printf("\t4. 清空列表\t\t10. 列表长度\n");
	printf("\t5. 删除区间\t\t11. 按位置查找元素\n");
	printf("\t6. 删除某元素\t\t12. 按元素查找位置\n");
	printf("\t\t\t\t13. 求某元素前驱元素\n");
	printf("\t\t\t\t14. 求某元素后继元素\n");
	printf("\t文件类");
	printf("\n\t15. Savelist\t\t16. Loadlist\n");
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
void inputindex(int * i)
{
	printf("请输入位置:");
	scanf("%d", i);
}

//判断两个元素是否相等
BOOL equal(void * a, void * b)
{
	student * p1 , * p2;
	p1 = a;
	p2 = b;
	if ((strcmp(p1->name, p2->name) == 0) && p1->age == p2->age)
		return TRUE;
	else
		return FALSE;
}