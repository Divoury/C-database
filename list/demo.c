#include "list.h"
#include "list.c"

#define ElemType student
typedef struct {
	char name[20];
	int age;
} student;

void display(void *stu);
void menu(void);
void inputstu(student * p);	//����ѧ����Ϣ
void inputindex(int *);	//����λ����Ϣ


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
			 case 1: //��ʼ���б�
				 if (list_exist(pL) == TRUE || list_empty(pL) == FALSE)
					 list_destroy(&pL);
				 if ((pL = list_init(sizeof(student))) != NULL)
				 {
					 printf("��ʼ���ɹ�!");
					  getchar();getchar();
				 }
				 else
				 {
					 printf("��ʼ��ʧ��!");
					  getchar();getchar();
				 }			 break;
			 case 2: //����Ԫ��
				 inputindex(&i);
				 inputstu(pe);

				 if ((pnode = (list_getp(pL, i))) == NULL)
				 {
					 printf("λ�ò��Ի�����������!");
					 getchar();getchar();
					 break;
				 }
				 if (list_insert(pL, pnode, pe) == TRUE)
					 printf("����ɹ�!");
				 else
					 printf("����ʧ��!");
				 getchar();getchar();
							 break;
			 case 3: //�����б�
				 if(list_destroy(&pL) == TRUE)
					 printf("���ٳɹ�!");
				getchar();getchar();
				break;
			 case 4: //����б�
				 if(list_clear(pL) == TRUE)
				 {
					 printf("��ճɹ�!");
					getchar();getchar();
				 }
				 else
				 {
					printf("�б�����!");
				 	getchar();getchar();
				 }
				break;
		/*	 case 5: //ɾ������
				 printf("����������");
				 scanf("%d %d", &lo, &hi);
				 if(list_delete(pL, lo, hi) == FALSE)
				 {
					 printf("ɾ��ʧ��");
					getchar();getchar();
				 }
				 else
				{
					 printf("ɾ���ɹ�!");
					getchar();getchar();
				 }
				 break;*/
			 case 6: //ɾ��ĳԪ��
				inputindex(&i);
				if (getpos_invalid(pL, i) == FALSE)
				{
					printf("λ�ò��Ϸ����б�����");
					getchar();getchar();
					break;
				}
				if ((pnode = list_getp(pL, i)) == NULL)
				{
					printf("ɾ��ʧ��!");
					getchar();getchar();
					break;
				}
				if(list_remove(pL, pnode, pe) == TRUE)
				{
					printf("��%d��Ԫ��", i);
					display(pe);
					printf("ɾ���ɹ�");
					getchar();getchar();
				}
				else
				{
					printf("ɾ��ʧ��!");
					getchar();getchar();
				}
							 
							 break;
			 case 7: //�ж��б��Ƿ����
				 if (list_exist(pL) == TRUE)
				 {
					 printf("�б����!");
					 getchar();getchar();
				 }
				 else
				 {
					 printf("�б�����!");
					 getchar();getchar();
				 }
				break;
			 case 8: //�ж��б��Ƿ�Ϊ��
				 if (list_exist(pL) == FALSE)
				 {
					 printf("�б�����!");
					getchar();getchar();
					break;
				 }
				if (list_empty(pL) == TRUE)
				 {
					 printf("�б�Ϊ��!");
					 getchar();getchar();
				 }
				 else
				 {
					 printf("�б�Ϊ��!");
					 getchar();getchar();
				 }
				 break;
			 case 9: //����Ԫ��
				 list_travel(pL, &display);
							 getchar();getchar();
							 break;
			 case 10: //���б���
				 if (list_exist(pL) == FALSE)
				 {
					 printf("�б�����!");
					getchar();getchar();
					break;
				 }
				 printf("�б�����%d", list_length(pL));
					getchar();getchar();
				break;
			 case 11: //��λ�ò���Ԫ��
				 inputindex(&i);
				if (getpos_invalid(pL, i) == FALSE)
				{
					printf("λ�ò��Ϸ����б�����");
					getchar();getchar();
					break;
				}
				if ((pnode = list_getp(pL, i)) == NULL)
				{
					printf("ʧ��!");
					getchar();getchar();
					break;
				}
				display(pnode->pelem);
				getchar();getchar();
				break;
			 case 12: //��Ԫ�ز���λ��
				 inputstu(pe);
				 if ((i = list_locateelem(pL, (void *)pe, &equal)) == 0)
				 {
					 printf("����ʧ��!");
					getchar(); getchar();
				 }
				 else
				 {
					 printf("�ǵ�%d��Ԫ��", i);
					 getchar(); getchar();
				 }
								 break;
			 case 13: //��ǰ��Ԫ��
				 inputstu(pe);
				 if(list_priorelem(pL, pe, &pre_e) == TRUE)
				 {
					 display(pe);
					 printf("��ǰ��Ԫ����");
					 display(&pre_e);
					getchar(); getchar();
				 }
				 else
				 {
					 printf("����ǰ��Ԫ��ʧ��!");
					 getchar(); getchar();
				 }
								 break; 
			 case 14: //����Ԫ��
				 	inputstu(pe);
				 if(list_nextelem(pL, pe, &next_e) == TRUE)
				 {
					 display(pe);
					 printf("�ĺ��Ԫ����");
					 display(&next_e);
					getchar(); getchar();
				 }
				 else
				 {
					 printf("���Һ��Ԫ��ʧ��!");
					 getchar(); getchar();
				 }
								 break;
			 case 15: //���浽�ļ�
				 if(savelist(pL) == TRUE)
				 {
					 printf("����ɹ�!");
					 getchar(); getchar();
				 }
				 else
				 {
					 printf("����ʧ��!");
					 getchar(); getchar();
				 }
				break;
			 case 16: //���ļ�����
				  if(loadlist(&pL) == TRUE)
				  {
					 printf("���سɹ�!");
					 getchar(); getchar();
				  }
				  else
				  {
					 printf("����ʧ��!");
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
	printf("����:%s\t����%d\n", ((student *)stu)->name, ((student *)stu)->age);
}

void menu(void){
	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("------------------------------------------------------\n");
	printf("\t�޸���\t\t\t������\n");
	printf("\t1. ��ʼ���б�\t\t7. �ж��б��Ƿ����\n");
	printf("\t2. ����Ԫ��\t\t8. �ж��б��Ƿ�Ϊ��\n");
	printf("\t3. �����б�\t\t9. �����б�Ԫ��\n");
	printf("\t4. ����б�\t\t10. �б���\n");
	printf("\t5. ɾ������\t\t11. ��λ�ò���Ԫ��\n");
	printf("\t6. ɾ��ĳԪ��\t\t12. ��Ԫ�ز���λ��\n");
	printf("\t\t\t\t13. ��ĳԪ��ǰ��Ԫ��\n");
	printf("\t\t\t\t14. ��ĳԪ�غ��Ԫ��\n");
	printf("\t�ļ���");
	printf("\n\t15. Savelist\t\t16. Loadlist\n");
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
void inputindex(int * i)
{
	printf("������λ��:");
	scanf("%d", i);
}

//�ж�����Ԫ���Ƿ����
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