//��ʼ������
list * list_init(int elemsize)
{
	list * pL;

	if((pL = (list *)malloc(sizeof(list))) == NULL)
		exit(-1);
	pL->elemsize = elemsize;
	pL->listsize = 0;
	pL->header.pelem = NULL;
	pL->header.next = &(pL->trailer);
	pL->header.pre = NULL;
	pL->trailer.pelem = NULL;
	pL->trailer.pre = &(pL->header);
	pL->trailer.next = NULL;

	return pL;
}
//������� ��������ʱ ���ش���
BOOL list_clear(list * pL)
{
	listnode * p, *q;
	int i;
	if (list_exist(pL) == FALSE)
		return FALSE;
	if (pL->listsize == 0)
		return TRUE;
	p = pL->header.next;
	i = 1;
	while (i <= pL->listsize)
	{
		free(p->pelem);
		q = p;
		p = p->next;
		free(q);
		i++;
	}
	pL->header.next = &pL->trailer;
	pL->trailer.pre = &pL->header;
	pL->listsize = 0;

	return TRUE;
}
//�������� �������Ͳ����� ���سɹ�
BOOL list_destroy(list ** pL)
{
	if (list_exist(*pL) == FALSE)
		return TRUE;
	if (list_clear(*pL) == FALSE)
		return FALSE;
	free(*pL);
	*pL = NULL;
	
	return TRUE;
}
//�ж��б��Ƿ����
BOOL list_exist(list * pL)
{
	return (pL == NULL) ? FALSE : TRUE;
}
//�ж������Ƿ�Ϊ��
BOOL list_empty(list * pL)
{
	if (list_exist(pL) == FALSE)
		return FALSE;
	if (pL->listsize == 0)
		return TRUE;
	return FALSE;
}
//�ж�λ���Ƿ��ں������� 1��Ԫ������
BOOL getpos_invalid(list * pL, int i)
{
	if (list_exist(pL) == FALSE)
		return FALSE;
	if (i < 1 || i > pL->listsize)
		return FALSE;
	else
		return TRUE;
}
//�ж�λ���Ƿ���� 1������+1  βָ��
BOOL putpos_invalid(list * pL, int i)
{
	if (list_exist(pL) == FALSE)
		return FALSE;
	if (i < 1 || i > pL->listsize + 1)
		return FALSE;
	else
		return TRUE;
}
//����λ�÷��ظ�λ�ý��ָ�� ������βָ��
listnode * list_getp(list * pL, int i)
{
	int j;
	listnode * p;	//����ָ��βָ��
	if (putpos_invalid(pL, i) == FALSE)
		return NULL;
	j = 1;
	p = pL->header.next;
	while (j < i)
	{
		p = p->next;
		j++;
	}
	
	return p;
}
//����λ�ðѸ�λ�õ�Ԫ�ظ��Ƶ�peָ����ڴ�
BOOL list_getelem(list * pL, int i, void * pe)
{
	int j;
	listnode * p;
	if (getpos_invalid(pL, i) == FALSE)
		return FALSE;
	j = 1;
	p = pL->header.next;
	while (j < i)
	{
		p = p->next;
		j++;
	}
	memcpy(pe, p->pelem, pL->elemsize);
	return TRUE;
}
//����Ԫ�� ������p���֮ǰ p������βָ��
BOOL list_insert(list * pL, listnode * p, void * pe)
{
	listnode * pnode;

	if((pnode = (listnode *)malloc(sizeof(listnode))) == NULL)
		exit(-1);
	pnode->pelem = malloc(pL->elemsize);
	memcpy(pnode->pelem, pe, pL->elemsize);

	p->pre->next = pnode;
	pnode->pre = p->pre;
	pnode->next = p;
	p->pre = pnode;

	pL->listsize++;
	
	return TRUE;
}
//������Ԫ�ؽ���visit()����
BOOL list_travel(list * pL, void visit())
{
	listnode * p;
	int i;
	if (list_exist(pL) == FALSE)
	{
		printf("��������!");
		return FALSE;
	}
	if (list_empty(pL) == TRUE)
	{
		printf("�ǿձ�!");
		return FALSE;
	}
	i = 1;
	p = pL->header.next;
	while (i <= pL->listsize)
	{
		printf("��%d��:\t", i);
		visit(p->pelem);
		p = p->next;
		i++;
	}
	return TRUE;
}
//���浽�ļ�
BOOL savelist(list * pL)
{
	FILE  * out;
	listnode * p;
	int i;
	if (list_exist(pL) == FALSE)
		return FALSE;
	if ((out = fopen("list.dat", "wb")) == NULL)
		return FALSE;
	fwrite(&pL->listsize, sizeof(pL->listsize), 1, out);
	fwrite(&pL->elemsize, sizeof(pL->elemsize), 1, out);
	p = pL->header.next;
	i = 1;
	while (i <= pL->listsize)
	{
		fwrite(p->pelem, pL->elemsize, 1, out);
		p = p->next;
		i++;
	}
	fclose(out);
	return TRUE;
}
//���ļ�����
BOOL loadlist(list ** pL)
{
	FILE * in;
	listnode * p, * q;
	int i;
	if (list_destroy(pL) == FALSE)
		return FALSE;
	if ((in = fopen("list.dat", "rb")) == NULL)
		return FALSE;
	if (((*pL) = (list *)malloc(sizeof(list))) == NULL)
		exit(-1);

	fread(&(*pL)->listsize, sizeof((*pL)->listsize), 1, in);
	fread(&(*pL)->elemsize, sizeof((*pL)->elemsize), 1, in);
	(*pL)->header.pelem = NULL;
	(*pL)->header.next = &((*pL)->trailer);
	(*pL)->header.pre = NULL;
	(*pL)->trailer.pelem = NULL;
	(*pL)->trailer.pre = &((*pL)->header);
	(*pL)->trailer.next = NULL;

	
	i = 1;
	q = &((*pL)->header);
	while (i <= (*pL)->listsize)
	{
		if((p = (listnode *)malloc(sizeof(listnode))) == NULL)
			exit(-1);
		p->pelem = malloc((*pL)->elemsize);
		fread(p->pelem, (*pL)->elemsize, 1, in);
		q->next = p;
		p->pre = q;
		q = p;
		i++;
	}
	q->next = &(*pL)->trailer;
	(*pL)->trailer.pre = q;

	return TRUE;
}
//ɾ������Ԫ�� ����Ԫ������*pnode�ҵ��ýڵ� ����ɾ����Ԫ�طŵ�p
BOOL list_remove(list * pL, listnode * pnode, void *p)
{
	if (list_exist(pL) == FALSE || list_empty(pL) == TRUE)
		return FALSE;
	pnode->pre->next = pnode->next;
	pnode->next->pre = pnode->pre;
	memcpy(p, pnode->pelem, pL->elemsize);
	free(pnode);
	pL->listsize--;

	return TRUE;
}
//�����б���ЧԪ�ظ���
int list_length(list * pL)
{
	if (list_exist(pL) == TRUE)
		return pL->listsize;
	else
		return -1;
}
//���ݹ�������б��е�һ������Ҫ���Ԫ�� �ŵ�pe��
int list_locateelem(list * pL, void * pe, BOOL compare())
{
	listnode * p;
	int i;
	p = pL->header.next;
	i = 1;
	while (i <= pL->listsize)
	{
		if (compare(p->pelem, pe) == TRUE)
			return i;
		p = p->next;
		i++;
	}
	return 0;	
}
//��ǰ��Ԫ�� 
BOOL list_priorelem(list * pL, void * pe, void * pre_e)
{
	int i;
	if (list_exist(pL) == FALSE || list_empty(pL) == TRUE)
		return FALSE;
	if((i = list_locateelem(pL, pe, &equal)) == 0 || i == 1)
		return FALSE;
	if (list_getelem(pL, i-1, pre_e) == TRUE)
		return TRUE;
	else
		return FALSE;
}
//����Ԫ��
BOOL list_nextelem(list * pL, void * pe, void * next_e)
{
	int i;
	if (list_exist(pL) == FALSE || list_empty(pL) == TRUE)
		return FALSE;
	if((i = list_locateelem(pL, pe, &equal)) == 0 || i == pL->listsize)
		return FALSE;
	if (list_getelem(pL, i+1, next_e) == TRUE)
		return TRUE;
	else
		return FALSE;
}