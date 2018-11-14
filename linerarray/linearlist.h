#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

#define INIT_LENGTH 10

typedef struct LinearList{
	ElemType * _elem;	//ָ�����Ԫ�ص�ָ��
	int _size;		//��ǰԪ�ع�ģ
	int capacity;	//������
	int elemsize;	//ÿ��Ԫ�ش�С
} LinearList;

//�ڲ�
BOOL putpos_invalid(LinearList * pL, int i);	//�ж�Ҫ����Ԫ�ص�λ���Ƿ����Ҫ��
BOOL getpos_invalid(LinearList * pL, int i);	////�ж�ȡֵԪ�ص�λ���Ƿ����Ҫ��
BOOL list_expand(LinearList * pL);	//������������
BOOL equal(ElemType a, ElemType b);	//�ж�Ԫ���Ƿ����

//������
BOOL list_exist(LinearList * pL);	//�ж��б��Ƿ����
BOOL list_travel(LinearList * pL, BOOL (* visit)(ElemType e));	//����Ԫ��
BOOL list_empty(LinearList * pL);	//�ж��Ƿ�Ϊ�ձ�
int list_length(LinearList * pL);	//���б�Ԫ�ظ���
BOOL list_getelem(LinearList * pL, int i, ElemType * pe);	//��L�е�i��Ԫ������e��
int list_locateelem(LinearList * pL,const ElemType * pe, BOOL compare());	//����L�е�һ����pe�����ϵcompare��Ԫ�� ����λ��
BOOL list_priorelem(LinearList * pL, const ElemType * pe, ElemType * pre_e);
BOOL list_nextelem(LinearList * pL, const ElemType * pe, ElemType * next_e);

//�޸���
LinearList * list_init(int elemsize);	//��ʼ���б�
BOOL list_insert(LinearList * pL, int i, ElemType * pe);	//����Ԫ��
BOOL list_destroy(LinearList ** pL);	//�����б�
BOOL list_clear(LinearList * pL);	//����б�
BOOL list_delete(LinearList * pL, int lo, int hi);	//ɾ��lo��hi���������Ԫ��
BOOL list_remove(LinearList * pL, int i, ElemType * pe);	//ɾ��iԪ�ز��ŵ�pe��

//�ļ���
BOOL savelist(LinearList * pL);
BOOL loadlist(LinearList ** pL);


