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
			 case 1: //��ʼ��ջ
				 if ((pS = stack_init(sizeof(student))) == NULL)
					 exit(-1);
				 printf("��ʼ���ɹ�!");
							 getchar();getchar();
							 break;
			 case 2: //����ջ
				 if (stack_destroy(&pS) == TRUE)
				 {
					 printf("���ٳɹ�!");
							 getchar();getchar();
							 break;
				 }
				 else
				 {
					 printf("����ʧ��!");
					 getchar();getchar();
					 break;
				 }
				 
			 case 3: //���ջ
				 if (stack_clear(pS) == TRUE)
				 {
					 printf("��ճɹ�!");
					 getchar();getchar();
					 break;
				 }
				 else
				 {
					 printf("���ʧ��!");
					 getchar();getchar();
					 break;
				 }
			 case 4: //�ж��Ƿ����
				 if (stack_exist(pS) == FALSE)
				 {
					 printf("������!");
					 getchar();getchar();
					 break;
				 }
				 else
				 {
					 printf("ջ����!");
					 getchar();getchar();
				 }
					break;
			 case 5: //�ж��Ƿ�Ϊ��ջ
				 if (stack_exist(pS) == FALSE)
				 {
					 printf("ջ������!");
					 getchar();getchar();
					 break;
				 }
				 if (stack_empty(pS) == TRUE)
				 {
					 printf("�ǿ�ջ!");
					 getchar();getchar();
					 break;
				 }
				 printf("���ǿ�ջ!");
							 getchar();getchar();
							 break;
			 case 6: //ջ��Ԫ�ظ���
				 printf("Ԫ�ظ�����%d", stack_length(pS));
							 getchar();getchar();
							 break;
			 case 7: //ȡջ��Ԫ��
				 if (stack_gettop(pS, stu) == FALSE)
				 {
					 printf("����ʧ��!");
					 getchar();getchar();
					 break;
				 }
				 display(stu);
							 getchar();getchar();
							 break;
			 case 8: //��ջ
				 inputstu(stu);
				 if (stack_push(pS, stu) == TRUE)
				 {
					 printf("��ջ�ɹ�!");
				 	 getchar();getchar();
					 break;
				 }
				 else
				 {
					 printf("��ջʧ��!");
					 getchar();getchar();
					 break;
				 }

			 case 9: //��ջ
				 if (stack_pop(pS, stu) == FALSE)
				 {
					 printf("����ʧ��!");
					 getchar();getchar();
					 break;
				 }
				 display(stu);
				 getchar();getchar();
				 break;
			 case 10: //����
				 if (stack_exist(pS) == FALSE || stack_empty(pS) == TRUE)
				 {
					 printf("ջ�����ڻ�Ϊ��!");
					 getchar();getchar();
					break;
				 }
				 stack_traverse(pS, &display);
								getchar();getchar();
								break;
			 case 11: //���浽�ļ�
				 if (savestack(pS) == TRUE)
				 {
					 printf("����ɹ�!");
					 getchar();getchar();
					 break;
				 }
				 else
				{
					printf("����ʧ��!");
					getchar();getchar();
					break;
				 }
			 case 12: //���ļ�����
				 if (loadstack(&pS) == TRUE)
				 {
					 printf("���سɹ�!");
					 getchar();getchar();
					 break;
				 }
				 else
				 {
					 printf("����ʧ��!");
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
	printf("����:%s\t����%d\n", ((student *)stu)->name, ((student *)stu)->age);
}
void menu(void){
	printf("\n\n");
	printf("      Menu for ջ������ʵ�� \n");
	printf("------------------------------------------------------\n");
	printf("\t1. ��ʼ��ջ\n");
	printf("\t2. ����ջ\n");
	printf("\t3. ���ջ\n");
	printf("\t4. �ж��Ƿ����\n");
	printf("\t5. �ж��Ƿ�Ϊ��\n");	
	printf("\t6. ��ջԪ�ظ���\n");
	printf("\t7. ȡջ��Ԫ��\n");
	printf("\t8. ��ջ\n");
	printf("\t9. ��ջ\n");
	printf("\t10.����ջ��Ԫ��\n");
	printf("\n\t11. Savelist\t\t12. Loadlist\n");
	printf("    	  0. Exit\n");
	printf("------------------------------------------------------\n");
	
}
void inputstu(student * p)
{
	printf("������ѧ������:");
	scanf("%s", p->name);
	printf("����������:");
	scanf("%d", &p->age);
	
}