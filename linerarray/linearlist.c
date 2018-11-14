/*
* �������ƣ�list_init
* �������ܣ���ʼ��˳��ṹ���Ա�
* ������������е���Ԫ�ش�С
* ����ֵ������ʼ���ɹ� �������Ա��ַ ���򷵻�NULL
*/
LinearList * list_init(int elemsize)
{
	LinearList * p;
	if ((p = (LinearList *)malloc(sizeof(LinearList))) == NULL)
		exit(-1);
	if((p->_elem = malloc(elemsize * INIT_LENGTH)) == NULL)
		exit(-1);
	p->_size = 0;
	p->capacity = INIT_LENGTH;
	p->elemsize = elemsize;

	return p;
}

//�ж��б��Ƿ����
BOOL list_exist(LinearList * pL)
{
	return (pL == NULL) ? FALSE : TRUE;
}
//�ж�ȡֵԪ�ص�λ���Ƿ����Ҫ��
BOOL getpos_invalid(LinearList * pL, int i)
{
	return (i <= pL->_size && i > 0) ? TRUE : FALSE;

}
//�ж�Ҫ����Ԫ�ص�λ���Ƿ����Ҫ��
BOOL putpos_invalid(LinearList * pL, int i)
{
	return (i <= pL->_size + 1 && i > 0) ? TRUE : FALSE;

}
/*
* �������ƣ�list_insert
* �������ܣ���ĳһλ��ǰ����Ԫ��
* ������������Ա��ַ λ�� Ҫ�����Ԫ�ص�ַ
* ����ֵ�����ɹ�����TRUE ���򷵻�FALSE
*/
BOOL list_insert(LinearList * pL, int i, ElemType * pe)
{
	int size;
	if (pL->_size == pL->capacity)
	{
		if(list_expand(pL) == FALSE)
			return FALSE;
	}
	if (putpos_invalid(pL, i) == FALSE) return FALSE;
	size = pL->_size;
	while (size != i - 1)
	{
		pL->_elem[size] = pL->_elem[size - 1];
		size--;
	}
	memcpy(&pL->_elem[i - 1], pe, pL->elemsize);
	pL->_size++;

	return TRUE;
}
//	������������
BOOL list_expand(LinearList * pL)
{
	ElemType * p;
	if((p = (ElemType *)realloc(pL->_elem, sizeof(ElemType) * (pL->capacity <<= 1))) != NULL)
	{
		pL->_elem = p;
		if (pL->_elem != p)
			free(p);
		printf("%d", pL->_size);
		return TRUE;
	}
	else
		return FALSE;
}
/*
* �������ƣ�list_travel
* �������ܣ���ĳ�ַ�ʽ�����б�Ԫ��
* ������������Ա��ַ ��Ԫ�ؽ��еĲ���������ַ
* ����ֵ�����ɹ�����TRUE ���򷵻�FALSE
*/
BOOL list_travel(LinearList * pL, BOOL (* visit)(ElemType e))
{
	int i;
	if (list_exist(pL) == FALSE)
	{
		printf("�б�����");
		return TRUE;
	}
	if (list_empty(pL) == TRUE)
	{
		printf("�б�Ϊ��!");
		return TRUE;
	}
	i = 0;
	while (i < pL->_size)
	{
		printf("��%d��Ԫ��:\t", i+1);
		visit(pL->_elem[i]);
		i++;
	}
	return TRUE;
}
//�������Ա�
BOOL list_destroy(LinearList ** pL)
{
	if (list_exist(*pL) == FALSE)
		return TRUE;
	free((*pL)->_elem);
	free(*pL);
	*pL = NULL;

	return TRUE;
}
//����б�
BOOL list_clear(LinearList * pL)
{
	if (list_exist(pL) == FALSE)
		return FALSE;
	free(pL->_elem);
	pL->_size = 0;
	pL->capacity = 0;
	pL->elemsize = 0;
	pL->_elem = NULL;
	return TRUE;
}
//�ж��б��Ƿ�Ϊ�� Ϊ�շ���TRUE
BOOL list_empty(LinearList * pL)
{
	if (list_exist(pL) == FALSE)
		return FALSE;
	if (pL->_size == 0)
		return TRUE;
	return FALSE;
}
//���б��� ��ЧԪ�ظ���
int list_length(LinearList * pL)
{
	if(list_exist(pL) == FALSE)
		return -1;
	return pL->_size;
}
/*
* �������ƣ�list_getelem
* �������ܣ���λ��ȡԪ��ֵ����pe
* ������������Ա��ַ λ�� �洢��Ԫ�ص�ַ
* ����ֵ�����ɹ�����TRUE ���򷵻�FALSE
*/
BOOL list_getelem(LinearList * pL, int i, ElemType * pe)
{
	if (list_exist(pL) == FALSE || getpos_invalid(pL, i) == FALSE)
		return FALSE;
	*pe = pL->_elem[i - 1];
	return TRUE;
}
/*
* �������ƣ�list_locateelem
* �������ܣ�Ѱ���б�������ĳһ��ϵ�ĵ�һ��Ԫ�ص�λ��
* ������������Ա��ַ Ԫ�ص�ַ �ȽϺ�����ַ
* ����ֵ�����ɹ�����Ԫ��λ�� ���򷵻�0
*/
int list_locateelem(LinearList * pL,const ElemType * pe, BOOL compare())
{
	int i;
	if (list_exist(pL) == FALSE || list_empty(pL) == TRUE)
		return 0;
	i = 0;
	while (i < pL->_size)
	{
		if (compare(pL->_elem[i], *pe) == TRUE)
			return i + 1;
		i++;
	}
	return 0;
}
//����ǰ��Ԫ��
BOOL list_priorelem(LinearList * pL, const ElemType * pe, ElemType * pre_e)
{
	int i = list_locateelem(pL, pe, &equal);
	if (i == 0 || i == 1)
		return FALSE;
	if(list_getelem(pL, i - 1, pre_e) == TRUE)
		return TRUE;
	return FALSE;
}
//���Һ��Ԫ��
BOOL list_nextelem(LinearList * pL, const ElemType * pe, ElemType * next_e)
{
	int i = list_locateelem(pL, pe, &equal);
	if (i == 0 || i == pL->_size)
		return FALSE;
	if(list_getelem(pL, i + 1, next_e) == TRUE)
		return TRUE;
	return FALSE;
}
/*
* �������ƣ�list_delete
* �������ܣ�ɾ���б���lo��hi������Ԫ��
* ������������Ա��ַ lo hi
* ����ֵ�����ɹ�����TRUE ���򷵻�FALSE
*/
BOOL list_delete(LinearList * pL, int lo, int hi)
{
	int n = hi - lo;
	if(list_exist(pL) == FALSE || list_empty(pL) == TRUE)
		return FALSE;
	if (getpos_invalid(pL, lo) == FALSE || getpos_invalid(pL, hi) == FALSE)
		return FALSE;

	while(getpos_invalid(pL, ++hi) == TRUE)
	{
		pL->_elem[lo++ - 1] = pL->_elem[hi-1];
	}
	pL->_size = pL->_size - n - 1;
	return TRUE;
}
/*
* �������ƣ�list_remove
* �������ܣ�ɾ���б���ĳ��λ�õ�Ԫ�� ����ֵ��ŵ�pe��
* ������������Ա��ַ λ�� pe��ַ
* ����ֵ�����ɹ�����TRUE ���򷵻�FALSE
*/
BOOL list_remove(LinearList * pL, int i, ElemType * pe)
{
	if(list_exist(pL) == FALSE || list_empty(pL) == TRUE)
		return FALSE;
	if (getpos_invalid(pL, i) == FALSE)
		return FALSE;
	list_getelem(pL, i, pe);
	while(getpos_invalid(pL, ++i) == TRUE)
	{
		pL->_elem[i - 2] = pL->_elem[i-1];
	}
	pL->_size--;
	return TRUE;
}
//�ж�����Ԫ���Ƿ����
BOOL equal(ElemType a, ElemType b)
{
	if ((strcmp(a.name, b.name) == 0) && a.age == b.age)
		return TRUE;
	else
		return FALSE;
}
//���浽�ļ�
BOOL savelist(LinearList * pL)
{
	FILE * out;
	ElemType * p;
	int i = 0;
	if (list_exist(pL) == FALSE)
		return FALSE;
	if ((out = fopen("list.dat", "wb")) == NULL)
		return FALSE;
	fwrite(&pL->_size, sizeof(pL->_size), 1, out);
	fwrite(&pL->capacity, sizeof(pL->capacity), 1, out);
	fwrite(&pL->elemsize, sizeof(pL->elemsize), 1, out);
	p = pL->_elem;
	while(i < pL->_size)
	{
		fwrite(p, sizeof(ElemType), 1, out);
		p++;
		i++;
	}
	fclose(out);
	return TRUE;
}
//���ļ�����
BOOL loadlist(LinearList ** pL)
{
	FILE * in;

	if ((in = fopen("list.dat", "rb")) == NULL)
		return FALSE;
	if (list_destroy(pL) == FALSE)
		return FALSE;
	if((*pL = (LinearList *)malloc(sizeof(LinearList))) == NULL)
		exit(-1);

	fread(&(*pL)->_size, sizeof((*pL)->_size), 1, in);
	fread(&(*pL)->capacity, sizeof((*pL)->capacity), 1, in);
	fread(&(*pL)->elemsize, sizeof((*pL)->elemsize), 1, in);
	
	if(((*pL)->_elem = (ElemType *)malloc((*pL)->capacity * sizeof(ElemType))) == NULL)
		exit(-1);
	fread((*pL)->_elem, sizeof(ElemType), (*pL)->_size, in);
	return TRUE;
	fclose(in);
}