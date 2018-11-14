/*
* 函数名称：list_init
* 函数功能：初始化顺序结构线性表
* 输入参数：表中单个元素大小
* 返回值：若初始化成功 返回线性表地址 否则返回NULL
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

//判断列表是否存在
BOOL list_exist(LinearList * pL)
{
	return (pL == NULL) ? FALSE : TRUE;
}
//判断取值元素的位置是否符合要求
BOOL getpos_invalid(LinearList * pL, int i)
{
	return (i <= pL->_size && i > 0) ? TRUE : FALSE;

}
//判断要插入元素的位置是否符合要求
BOOL putpos_invalid(LinearList * pL, int i)
{
	return (i <= pL->_size + 1 && i > 0) ? TRUE : FALSE;

}
/*
* 函数名称：list_insert
* 函数功能：在某一位置前插入元素
* 输入参数：线性表地址 位置 要插入的元素地址
* 返回值：若成功返回TRUE 否则返回FALSE
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
//	扩容数组容量
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
* 函数名称：list_travel
* 函数功能：按某种方式遍历列表元素
* 输入参数：线性表地址 对元素进行的操作函数地址
* 返回值：若成功返回TRUE 否则返回FALSE
*/
BOOL list_travel(LinearList * pL, BOOL (* visit)(ElemType e))
{
	int i;
	if (list_exist(pL) == FALSE)
	{
		printf("列表不存在");
		return TRUE;
	}
	if (list_empty(pL) == TRUE)
	{
		printf("列表为空!");
		return TRUE;
	}
	i = 0;
	while (i < pL->_size)
	{
		printf("第%d个元素:\t", i+1);
		visit(pL->_elem[i]);
		i++;
	}
	return TRUE;
}
//销毁线性表
BOOL list_destroy(LinearList ** pL)
{
	if (list_exist(*pL) == FALSE)
		return TRUE;
	free((*pL)->_elem);
	free(*pL);
	*pL = NULL;

	return TRUE;
}
//清空列表
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
//判断列表是否为空 为空返回TRUE
BOOL list_empty(LinearList * pL)
{
	if (list_exist(pL) == FALSE)
		return FALSE;
	if (pL->_size == 0)
		return TRUE;
	return FALSE;
}
//求列表长度 有效元素个数
int list_length(LinearList * pL)
{
	if(list_exist(pL) == FALSE)
		return -1;
	return pL->_size;
}
/*
* 函数名称：list_getelem
* 函数功能：按位置取元素值送入pe
* 输入参数：线性表地址 位置 存储的元素地址
* 返回值：若成功返回TRUE 否则返回FALSE
*/
BOOL list_getelem(LinearList * pL, int i, ElemType * pe)
{
	if (list_exist(pL) == FALSE || getpos_invalid(pL, i) == FALSE)
		return FALSE;
	*pe = pL->_elem[i - 1];
	return TRUE;
}
/*
* 函数名称：list_locateelem
* 函数功能：寻找列表中满足某一关系的第一个元素的位置
* 输入参数：线性表地址 元素地址 比较函数地址
* 返回值：若成功返回元素位置 否则返回0
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
//查找前驱元素
BOOL list_priorelem(LinearList * pL, const ElemType * pe, ElemType * pre_e)
{
	int i = list_locateelem(pL, pe, &equal);
	if (i == 0 || i == 1)
		return FALSE;
	if(list_getelem(pL, i - 1, pre_e) == TRUE)
		return TRUE;
	return FALSE;
}
//查找后继元素
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
* 函数名称：list_delete
* 函数功能：删除列表中lo到hi的所有元素
* 输入参数：线性表地址 lo hi
* 返回值：若成功返回TRUE 否则返回FALSE
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
* 函数名称：list_remove
* 函数功能：删除列表中某个位置的元素 并把值存放到pe中
* 输入参数：线性表地址 位置 pe地址
* 返回值：若成功返回TRUE 否则返回FALSE
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
//判断两个元素是否相等
BOOL equal(ElemType a, ElemType b)
{
	if ((strcmp(a.name, b.name) == 0) && a.age == b.age)
		return TRUE;
	else
		return FALSE;
}
//保存到文件
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
//从文件加载
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