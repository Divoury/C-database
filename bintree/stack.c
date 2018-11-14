
stack * stack_init(int elemsize)
{
	stack * p;
	stacknode * pnode;
	if ((p = (stack *)malloc(sizeof(stack))) == NULL)
		exit(-1);
	if ((pnode = (stacknode *)malloc(sizeof(stacknode))) == NULL)
		exit(-1);
	pnode->pNext = NULL;
	p->base = pnode;
	p->top = pnode;
	p->stacksize = 0;
	p->elemsize = elemsize;

	return p;
}
BOOL stack_push(stack * pS, void * pe)
{
	stacknode * pnode;
	void * p;
	if ((pnode = (stacknode *)malloc(sizeof(stacknode))) == NULL)
		exit(-1);
	pnode->pNext = pS->top;
	pS->top = pnode;
	pS->stacksize++;
	if ((p = malloc(pS->elemsize)) == NULL)
		exit(-1);
	memcpy(p, pe, pS->elemsize);
	pnode->pdata = p;
	
	return TRUE;
}
BOOL stack_traverse(const stack * pS, void visit(void *stu))
{
	stacknode * p;
	int i;
	if (stack_exist(pS) == FALSE || stack_empty(pS) == TRUE)
		return FALSE;
	p = pS->top;
	i = 1;
	while (i <= pS->stacksize)
	{
		visit(p->pdata);
		p = p->pNext;
		i++;
	}

	return TRUE;	
}
BOOL stack_exist(const stack * pS)
{
	return pS == NULL ? FALSE : TRUE;
}
BOOL stack_empty(const stack * pS)
{
	if (stack_exist(pS) == FALSE)
		return FALSE;
	if (pS->stacksize == 0)
		return TRUE;
	return FALSE;
}
BOOL stack_clear(stack * pS)
{
	stacknode * p, * q;
	if (stack_exist(pS) == FALSE)
		return FALSE;
	p = pS->top;
	while (p != pS->base)
	{
		free(p->pdata);
		q = p;
		p = p->pNext;
		free(q);
	}
	pS->top = p;
	pS->stacksize = 0;

	return TRUE;
}
BOOL stack_destroy(stack ** pS)
{
	if (stack_exist(*pS) == FALSE)
		return TRUE;
	stack_clear(*pS);
	free((*pS)->base);
	free(*pS);
	*pS = NULL;

	return TRUE;
}
//ÈôÕ»²»´æÔÚ·µ»Ø-1
int stack_length(const stack * pS)
{
	if (stack_exist(pS) == FALSE)
		return -1;
	return pS->stacksize;
}
BOOL stack_gettop(const stack * pS, void * pe)
{
	if (stack_exist(pS) == FALSE || stack_empty(pS) == TRUE)
		return FALSE;
	memcpy(pe, pS->top->pdata, pS->elemsize);

	return TRUE;
}
BOOL stack_pop(stack * pS, void * pe)
{
	stacknode * p;
	if (stack_gettop(pS, pe) == FALSE)
		return FALSE;
	p = pS->top;
	pS->top = p->pNext;
	free(p);
	pS->stacksize--;

	return TRUE;
}


BOOL savestack(const stack * pS)
{
	FILE * out;
	stacknode * p;
	if ((out = fopen("data.dat", "wb")) == NULL)
		return FALSE;
	fwrite(&pS->elemsize, sizeof(pS->elemsize), 1, out);
	fwrite(&pS->stacksize, sizeof(pS->stacksize), 1, out);
	
	p = pS->top;
	while (p != pS->base)
	{
		fwrite(p->pdata, pS->elemsize, 1, out);
		p = p->pNext;
	}
	fclose(out);

	return TRUE;
}
BOOL loadstack(stack ** pS)
{

	FILE * in;
	stacknode * p, * q, * temp;
	int i;
	if (stack_destroy(pS) == FALSE)
		return FALSE;
	if ((in = fopen("data.dat", "rb")) == NULL)
		return FALSE;
	*pS = (stack *)malloc(sizeof(stack));
	fread(&((*pS)->elemsize), sizeof((*pS)->elemsize), 1, in);
	fread(&((*pS)->stacksize), sizeof((*pS)->stacksize), 1, in);
	if ((q = (stacknode *)malloc(sizeof(stacknode))) == NULL)
			return FALSE;
	i = 1;
	temp = q;
	while (i <= (*pS)->stacksize)
	{
		if ((p = (stacknode *)malloc(sizeof(stacknode))) == NULL)
			return FALSE;
		p->pdata = malloc((*pS)->elemsize);
		fread(p->pdata, (*pS)->elemsize, 1, in);
		q->pNext = p;
		q = p;
		i++;
	}
	if ((p = (stacknode *)malloc(sizeof(stacknode))) == NULL)
			return FALSE;
	q->pNext = p;

	(*pS)->base = p;
	(*pS)->top = temp->pNext;
	free(temp);
	fclose(in);
	
	return TRUE;
}
