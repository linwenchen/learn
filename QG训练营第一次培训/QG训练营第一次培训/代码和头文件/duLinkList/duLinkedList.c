#include "../head/duLinkedList.h"
#include <stdio.h>
#include <stdlib.h>
/**
 *  @name        : Status InitList_DuL(DuLinkedList *L)
 *	@description : initialize an empty linked list with only the head node
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList_DuL(DuLinkedList *L) {
	*L = NULL;
	*L = (DuLNode *)malloc(sizeof(DuLNode));
	(*L)->prior = (*L)->next = NULL;
	return (*L != NULL);
}

/**
 *  @name        : void DestroyList_DuL(DuLinkedList *L)
 *	@description : destroy a linked list
 *	@param		 : L(the head node)
 *	@return		 : status
 *  @notice      : None
 */
void DestroyList_DuL(DuLinkedList *L) {
	DuLNode *temp = *L;
	while(*L != NULL)
	{
		temp = (*L)->next;
		free(*L);
		*L = temp;
	}
}

/**
 *  @name        : Status InsertBeforeList_DuL(DuLNode *p, LNode *q)
 *	@description : insert node q before node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertBeforeList_DuL(DuLNode *p, DuLNode *q) {
	DuLNode *temp = p->prior;//p��ǰһ�����
	if(temp == NULL)//���p���ǰ��Ϊ�գ��ǾͰ�q�ӵ�ǰ��
	{
		q->prior = NULL;
		q->next = p;
		p->prior = q;
		return SUCCESS;
	}
	//q��ǰ���
	temp->next = q;
	q->prior = temp->next;
	//q�����
	p->prior = q;
	q->next = p;
	return SUCCESS;
}

/**
 *  @name        : Status InsertAfterList_DuL(DuLNode *p, DuLNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertAfterList_DuL(DuLNode *p, DuLNode *q) {
	if(p->next == NULL)//p������Ϊ��
	{
		p->next = q;
		q->prior = p;
		q->next = NULL;
	}
	else
	{
		DuLNode *temp = p->next;//��һ�����
		//q��ǰ���
		q->prior = p;
		p->next = q;
		//q�����
		temp->prior = q;
		q->next = temp;

	}
	return SUCCESS;
}

/**
 *  @name        : Status DeleteList_DuL(DuLNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : status
 *  @notice      : None
 */
Status DeleteList_DuL(DuLNode *p, ElemType *e) {
	if(p->next == NULL)return ERROR;//p����û�н��
	else if((p->next)->next == NULL)//p����ֻ��һ�����
	{
		DuLNode *temp = p->next;
		*e = temp->data;
		free(temp);
		p->next = NULL;
		return SUCCESS;
	}
	else//p���������������ϵĽ��
	{
		DuLNode *temp = p->next;
		*e = temp->data;
		p->next = temp->next;
		(temp->next)->prior = p;
		free(temp);
		return SUCCESS;
	}

}

/**
 *  @name        : void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : Status
 *  @notice      : None
 */
void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)) {
	DuLNode *temp = L;
	while(temp!=NULL)
	{
		(*visit)(temp->data);
		temp = temp->next;
	}
	printf("\n");
}
//��β�� 
DuLNode *SearchEnd(DuLinkedList *L,char size)
{
	DuLNode *temp = *L;
	if(size == 'r')//���Ҳ��� 
	{
		while(temp->next != NULL)
		temp = temp->next;
	}
	else//������� 
	{
		while(temp->prior != NULL)
		temp = temp->prior;
	}
	return temp;
}
//β������� 
Status Insert(DuLinkedList *L,int sum,ElemType item,char size)
{
	DuLNode *temp = (DuLNode *)malloc(sizeof(DuLNode));
	if(temp == NULL)return ERROR;	
	temp->data = item;
	if(sum == 0)//��ʼ��ͷ��� 
	{
		(*L) = temp;
		temp->next = temp->prior = NULL;
	}
	else if(size == 'r')
	{
		InsertAfterList_DuL(SearchEnd(L,size), temp);
	}
	else
	{
		InsertBeforeList_DuL(SearchEnd(L,size), temp);
		if((*L)->prior!=NULL)*L = (*L)->prior; 
	}
	return SUCCESS;
}
//����ĳ��Ŀ�Ƿ����
DuLNode *FindItem(DuLinkedList L,ElemType e){
	DuLNode *temp = L;
	while(temp != NULL)
	{
		if(temp->data == e)return temp;
		temp = temp->next;
	}
	return NULL;
}
//�������Ԫ��
void out(ElemType c)
{
	printf("%d->",c);
}
//�ɲ����ĺ����б� 
char init()
{
	char ch,temp;
	printf(
			
			"-------------------------------------------------------\n"
			"a:��ʼ�����б�\n"
			"b:ɾ���б�\n"
			"c:����i����Ŀ��߲���һ����Ŀ\n"
			"d:����i����Ŀ�ұ߲���һ����Ŀ\n"
			"e:���б�β������һ����Ŀ\n"
			"f:ɾ����Ӧֵ����һ����Ŀ\n"
			"g:��ӡ������Ŀ\n"
			"h:������Ŀ\n"  
			"q:�˳�����\n"
			"-------------------------------------------------------\n"
			);
	printf("������������еĲ���(ֻ�е�һ����ĸ��Ч)��");
	scanf(" %c",&ch);
	while((temp = getchar())!='\n')continue;
	//������ 
	while(ch!='q' && (ch < 'a' || ch > 'h'))
	{
		printf("��������: %c ����!���������룺",ch); 
		scanf(" %c",&ch);
		while((temp = getchar())!='\n')continue;
	}
	 return ch;
}
