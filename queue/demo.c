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
			 case 1: //��ʼ������
				 if ((pQue = queue_init(sizeof(student))) == NULL)
					 exit(-1);
				 printf("��ʼ���ɹ�!");
							 getchar();getchar();
							 break;
			 case 2: //���ٶ���
				 if (queue_destroy(&pQue) == TRUE)
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
				 
			 case 3: //��ն���
				 if (queue_clear(pQue) == TRUE)
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
				 if (queue_exist(pQue) == FALSE)
				 {
					 printf("������!");
					 getchar();getchar();
					 break;
				 }
				 else
				 {
					 printf("���д���!");
					 getchar();getchar();
				 }
					break;
			 case 5: //�ж��Ƿ�Ϊ�ն���
				 if (queue_exist(pQue) == FALSE)
				 {
					 printf("���в�����!");
					 getchar();getchar();
					 break;
				 }
				 if (queue_empty(pQue) == TRUE)
				 {
					 printf("�ǿն���!");
					 getchar();getchar();
					 break;
				 }
				 printf("���ǿն���!");
							 getchar();getchar();
							 break;
			 case 6: //���е�Ԫ�ظ���
				 printf("Ԫ�ظ�����%d", queue_length(pQue));
							 getchar();getchar();
							 break;
			 case 7: //ȡ���ж�Ԫ��
				 if (queue_gethead(pQue, stu) == FALSE)
				 {
					 printf("����ʧ��!");
					 getchar();getchar();
					 break;
				 }
				 display(stu);
							 getchar();getchar();
							 break;
			 case 8: //�����
				 inputstu(stu);
				 if (enqueue(pQue, stu) == TRUE)
				 {
					 printf("����гɹ�!");
				 	 getchar();getchar();
					 break;
				 }
				 else
				 {
					 printf("�����ʧ��!");
					 getchar();getchar();
					 break;
				 }

			 case 9: //������
				 if (dequeue(pQue, stu) == FALSE)
				 {
					 printf("����ʧ��!");
					 getchar();getchar();
					 break;
				 }
				 display(stu);
				 getchar();getchar();
				 break;
			 case 10: //����
				 if (queue_exist(pQue) == FALSE || queue_empty(pQue) == TRUE)
				 {
					 printf("���в����ڻ�Ϊ��!");
					 getchar();getchar();
					break;
				 }
				 queue_traverse(pQue, &display);
								getchar();getchar();
								break;
			 case 11: //���浽�ļ�
				 if (savequeue(pQue) == TRUE)
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
				 if (loadqueue(&pQue) == TRUE)
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
	printf("      Menu for ���е�����ʵ�� \n");
	printf("------------------------------------------------------\n");
	printf("\t1. ��ʼ������\n");
	printf("\t2. ���ٶ���\n");
	printf("\t3. ��ն���\n");
	printf("\t4. �ж��Ƿ����\n");
	printf("\t5. �ж��Ƿ�Ϊ��\n");	
	printf("\t6. �����Ԫ�ظ���\n");
	printf("\t7. ȡ���ж�Ԫ��\n");
	printf("\t8. �����\n");
	printf("\t9. ������\n");
	printf("\t10.�������е�Ԫ��\n");
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