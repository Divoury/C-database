queue * queue_init(int elemsize)
{
	queue * p;
	queuenode * pnode;
	if ((p = (queue *)malloc(sizeof(queue))) == NULL)
		exit(-1);

	if ((pnode = (queuenode *)malloc(sizeof(queuenode))) == NULL)
		exit(-1);
	pnode->pNext = NULL;
	p->rear = pnode;
	p->front = pnode;
	p->queuesize = 0;
	p->elemsize = elemsize;

	return p;
}
BOOL enqueue(queue * pQue, void * pe)
{
	queuenode * pnode;
	void * p;
	if ((pnode = (queuenode *)malloc(sizeof(queuenode))) == NULL)
		exit(-1);
	pnode->pNext = NULL;
	pQue->rear->pNext = pnode;
	pQue->rear = pnode;
	pQue->queuesize++;
	if ((p = malloc(pQue->elemsize)) == NULL)
		exit(-1);
	memcpy(p, pe, pQue->elemsize);
	pnode->pdata = p;
	
	return TRUE;
}
BOOL queue_traverse(const queue * pQue, void visit(void *stu))
{
	queuenode * p;
	int i;
	if (queue_exist(pQue) == FALSE || queue_empty(pQue) == TRUE)
		return FALSE;
	p = pQue->front;
	i = 1;
	while (i <= pQue->queuesize)
	{
		p = p->pNext;
		visit(p->pdata);
		i++;
	}

	return TRUE;	
}
BOOL queue_exist(const queue * pQue)
{
	return pQue == NULL ? FALSE : TRUE;
}
BOOL queue_empty(const queue * pQue)
{
	if (queue_exist(pQue) == FALSE)
		return FALSE;
	if (pQue->queuesize == 0)
		return TRUE;
	return FALSE;
}
BOOL queue_clear(queue * pQue)
{
	int i;
	queuenode * p, * q;
	if (queue_exist(pQue) == FALSE)
		return FALSE;
	p = pQue->front->pNext;

	i = 1;
	while (i <= pQue->queuesize)
	{
		free(p->pdata);
		q = p;
		p = p->pNext;
		free(q);
		i++;
	}
	pQue->rear = pQue->front;
	pQue->queuesize = 0;

	return TRUE;
}
BOOL queue_destroy(queue ** pQue)
{
	if (queue_exist(*pQue) == FALSE)
		return TRUE;
	queue_clear(*pQue);
	free((*pQue)->rear);
	free(*pQue);
	*pQue = NULL;

	return TRUE;
}
//若队列不存在返回-1
int queue_length(const queue * pQue)
{
	if (queue_exist(pQue) == FALSE)
		return -1;
	return pQue->queuesize;
}
BOOL queue_gethead(const queue * pQue, void * pe)
{
	if (queue_exist(pQue) == FALSE || queue_empty(pQue) == TRUE)
		return FALSE;
	memcpy(pe, pQue->front->pNext->pdata, pQue->elemsize);

	return TRUE;
}
BOOL dequeue(queue * pQue, void * pe)
{
	queuenode * p;
	if (queue_gethead(pQue, pe) == FALSE)
		return FALSE;

	p = pQue->front->pNext;
	pQue->front->pNext = p->pNext;
	free(p);
	if (--pQue->queuesize == 0)
		pQue->rear = pQue->front;
	
	return TRUE;
}


BOOL savequeue(const queue * pQue)
{
	FILE * out;
	queuenode * p;
	if ((out = fopen("data.dat", "wb")) == NULL)
		return FALSE;
	fwrite(&pQue->elemsize, sizeof(pQue->elemsize), 1, out);
	fwrite(&pQue->queuesize, sizeof(pQue->queuesize), 1, out);
	
	p = pQue->front;
	while (p != pQue->rear)
	{
		p = p->pNext;
		fwrite(p->pdata, pQue->elemsize, 1, out);
		
	}
	fclose(out);

	return TRUE;
}
BOOL loadqueue(queue ** pQue)
{

	FILE * in;
	queuenode * p, * q;
	int i;
	if (queue_destroy(pQue) == FALSE)
		return FALSE;
	if ((in = fopen("data.dat", "rb")) == NULL)
		return FALSE;
	*pQue = (queue *)malloc(sizeof(queue));
	fread(&((*pQue)->elemsize), sizeof((*pQue)->elemsize), 1, in);
	fread(&((*pQue)->queuesize), sizeof((*pQue)->queuesize), 1, in);
	if ((q = (queuenode *)malloc(sizeof(queuenode))) == NULL)
			return FALSE;
	(*pQue)->front = q;
	

	i = 1;

	while (i <= (*pQue)->queuesize)
	{
		if ((p = (queuenode *)malloc(sizeof(queuenode))) == NULL)
			return FALSE;
		p->pdata = malloc((*pQue)->elemsize);
		fread(p->pdata, (*pQue)->elemsize, 1, in);
		q->pNext = p;
		q = p;
		i++;
	}
	
	(*pQue)->rear = p;


	fclose(in);
	
	return TRUE;
}
