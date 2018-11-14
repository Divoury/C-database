#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define BOOL int
#define TRUE 1
#define FALSE 0

//������ṹ �洢һ�����
typedef struct listnode{
	void * pelem;	//����������� ����ָ���κ�����
	struct listnode * pre;	//ָ����һ�����
	struct listnode * next;	//ָ����һ�����
} listnode;
//����ṹ ������������
typedef struct list{
	int elemsize;	//������ָ���������Ĵ�С
	int listsize;	//������Ԫ�صĸ���
	struct listnode header;	//ͷ���
	struct listnode trailer;	//β���
} list;

list * list_init(int elemsize);	//��ʼ������
BOOL getpos_invalid(list * pL, int i);	//�ж�ȡֵԪ�ص�λ���Ƿ����Ҫ��
BOOL list_exist(list * pL);	//�ж������Ƿ����
BOOL list_empty(list * pL);	//�ж������Ƿ�Ϊ�� ����������Ϊ��
BOOL getpos_invalid(list * pL, int i);	//�ж�Ԫ��λ���Ƿ�Ϸ�
BOOL putpos_invalid(list * pL, int i);	//�ж�Ҫ�����λ���Ƿ�Ϸ� βָ����һ��
BOOL list_getelem(list * pL, int i, void * pe);	//ȡ�ڼ���Ԫ�طŵ�peָ��Ľṹ
listnode * list_getp(list * pL, int i);	//����λ�÷��ظ�λ�õĽ��ָ�룬������βָ��
BOOL list_insert(list * pL, listnode * p, void * pe);	//��ĳ���λ��ǰ������ ������β���֮ǰ
BOOL list_travel(list * pL, void visit());	//�������� ִ��visit����
BOOL list_clear(list * pL);	//�������
BOOL list_destroy(list ** pL);	//��������
BOOL list_remove(list * pL, listnode * pnode, void *p);	//ɾ��һ��Ԫ��
int list_length(list * pL);	//�ж��б���
int list_locateelem(list * pL, void * pe, BOOL compare());
BOOL list_priorelem(list * pL, void * pe, void * pre_e);
BOOL list_nextelem(list * pL, void * pe, void * pre_e);
BOOL equal(void * a, void * b);

BOOL savelist(list * pL);
BOOL loadlist(list ** pL);