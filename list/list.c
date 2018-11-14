//初始化链表
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
//清空链表 链表不存在时 返回错误
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
//销毁链表 若本来就不存在 返回成功
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
//判断列表是否存在
BOOL list_exist(list * pL)
{
	return (pL == NULL) ? FALSE : TRUE;
}
//判断链表是否为空
BOOL list_empty(list * pL)
{
	if (list_exist(pL) == FALSE)
		return FALSE;
	if (pL->listsize == 0)
		return TRUE;
	return FALSE;
}
//判断位置是否在合理区间 1到元素总数
BOOL getpos_invalid(list * pL, int i)
{
	if (list_exist(pL) == FALSE)
		return FALSE;
	if (i < 1 || i > pL->listsize)
		return FALSE;
	else
		return TRUE;
}
//判断位置是否合理 1到总数+1  尾指针
BOOL putpos_invalid(list * pL, int i)
{
	if (list_exist(pL) == FALSE)
		return FALSE;
	if (i < 1 || i > pL->listsize + 1)
		return FALSE;
	else
		return TRUE;
}
//根据位置返回该位置结点指针 可能是尾指针
listnode * list_getp(list * pL, int i)
{
	int j;
	listnode * p;	//可能指向尾指针
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
//根据位置把该位置的元素复制到pe指向的内存
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
//插入元素 插入在p结点之前 p可能是尾指针
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
//遍历对元素进行visit()操作
BOOL list_travel(list * pL, void visit())
{
	listnode * p;
	int i;
	if (list_exist(pL) == FALSE)
	{
		printf("链表不存在!");
		return FALSE;
	}
	if (list_empty(pL) == TRUE)
	{
		printf("是空表!");
		return FALSE;
	}
	i = 1;
	p = pL->header.next;
	while (i <= pL->listsize)
	{
		printf("第%d个:\t", i);
		visit(p->pelem);
		p = p->next;
		i++;
	}
	return TRUE;
}
//保存到文件
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
//从文件加载
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
//删除单个元素 根据元素内容*pnode找到该节点 并将删除的元素放到p
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
//返回列表有效元素个数
int list_length(list * pL)
{
	if (list_exist(pL) == TRUE)
		return pL->listsize;
	else
		return -1;
}
//根据规则查找列表中第一个满足要求的元素 放到pe中
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
//求前驱元素 
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
//求后继元素
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