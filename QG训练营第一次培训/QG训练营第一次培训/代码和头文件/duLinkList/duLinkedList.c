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
	DuLNode *temp = p->prior;//p的前一个结点
	if(temp == NULL)//如果p结点前面为空，那就把q接到前面
	{
		q->prior = NULL;
		q->next = p;
		p->prior = q;
		return SUCCESS;
	}
	//q与前结点
	temp->next = q;
	q->prior = temp->next;
	//q与后结点
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
	if(p->next == NULL)//p后面结点为空
	{
		p->next = q;
		q->prior = p;
		q->next = NULL;
	}
	else
	{
		DuLNode *temp = p->next;//下一个结点
		//q与前结点
		q->prior = p;
		p->next = q;
		//q与后结点
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
	if(p->next == NULL)return ERROR;//p后面没有结点
	else if((p->next)->next == NULL)//p后面只有一个结点
	{
		DuLNode *temp = p->next;
		*e = temp->data;
		free(temp);
		p->next = NULL;
		return SUCCESS;
	}
	else//p后面有两个或以上的结点
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
//查尾端 
DuLNode *SearchEnd(DuLinkedList *L,char size)
{
	DuLNode *temp = *L;
	if(size == 'r')//向右插入 
	{
		while(temp->next != NULL)
		temp = temp->next;
	}
	else//向左插入 
	{
		while(temp->prior != NULL)
		temp = temp->prior;
	}
	return temp;
}
//尾插入操作 
Status Insert(DuLinkedList *L,int sum,ElemType item,char size)
{
	DuLNode *temp = (DuLNode *)malloc(sizeof(DuLNode));
	if(temp == NULL)return ERROR;	
	temp->data = item;
	if(sum == 0)//初始化头结点 
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
//查找某项目是否存在
DuLNode *FindItem(DuLinkedList L,ElemType e){
	DuLNode *temp = L;
	while(temp != NULL)
	{
		if(temp->data == e)return temp;
		temp = temp->next;
	}
	return NULL;
}
//输出链表元素
void out(ElemType c)
{
	printf("%d->",c);
}
//可操作的函数列表 
char init()
{
	char ch,temp;
	printf(
			
			"-------------------------------------------------------\n"
			"a:初始化空列表\n"
			"b:删除列表\n"
			"c:往第i个项目左边插入一个项目\n"
			"d:往第i个项目右边插入一个项目\n"
			"e:往列表尾部插入一个项目\n"
			"f:删除对应值的下一个项目\n"
			"g:打印链表项目\n"
			"h:查找项目\n"  
			"q:退出程序\n"
			"-------------------------------------------------------\n"
			);
	printf("请输入你想进行的操作(只有第一个字母有效)：");
	scanf(" %c",&ch);
	while((temp = getchar())!='\n')continue;
	//输入检测 
	while(ch!='q' && (ch < 'a' || ch > 'h'))
	{
		printf("您的输入: %c 有误!请重新输入：",ch); 
		scanf(" %c",&ch);
		while((temp = getchar())!='\n')continue;
	}
	 return ch;
}
