#include "../head/linkedList.h"
#include <stdio.h>
#include <stdlib.h>
/**
 *  @name        : Status InitList(LinkList *L);
 *	@description : initialize an empty linked list with only the head node without value
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList(LinkedList *L) {
	*L = NULL;
	*L = (LNode *)malloc(sizeof(LNode));
	(*L)->next = NULL;//һ��Ҫ������next��ΪNULL! 
	return (*L!=NULL);
}

/**
 *  @name        : void DestroyList(LinkedList *L)
 *	@description : destroy a linked list, free all the nodes
 *	@param		 : L(the head node)
 *	@return		 : None
 *  @notice      : None
 */
void DestroyList(LinkedList *L){
	LNode *temp = *L;
	while(*L)
	{
		temp = (*L)->next;
		free(*L);
		*L = temp;
	}
}

/**
 *  @name        : Status InsertList(LNode *p, LNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : Status
 *  @notice      : None
 */
Status InsertList(LNode *p, LNode *q) {
	if(q == NULL)return ERROR;
	if(p->next == NULL)//p�ڵ����Ϊ�� 
	{
		p->next = q;
		q->next = NULL; 
		return SUCCESS;
	}
	q->next = p->next;
	p->next = q;
	return SUCCESS;
}
/**
 *  @name        : Status DeleteList(LNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : Status
 *  @notice      : None
 */
Status DeleteList(LNode *p, ElemType *e) {
	if(p->next == NULL)return ERROR;//p���������Ľ�� 
	else if((p->next)->next == NULL)//p������һ������ҽ�����û��� 
	{
		LNode *temp = p->next;
		*e = temp->data;
		free(temp);
		p->next = NULL;//��ָ��ָ��� 
		return SUCCESS;
	}
	// 
	LNode *temp = p->next;
	*e = temp->data;
	p->next = (p->next)->next;
	free(temp);
	return SUCCESS;
}

/**
 *  @name        : void TraverseList(LinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : None
 *  @notice      : None
 */
void TraverseList(LinkedList L, void (*visit)(ElemType e)) {
	LNode *temp = L;
	while(temp != NULL)
	{
		(*visit)(temp->data);
		temp = temp->next;
	}
	printf("NULL\n"); 

}

/**
 *  @name        : Status SearchList(LinkedList L, ElemType e)
 *	@description : find the first node in the linked list according to e
 *	@param		 : L(the head node), e
 *	@return		 : Status
 *  @notice      : None
 */
Status SearchList(LinkedList L, ElemType e){
	LNode *temp = L;
	while(temp!=NULL)
	{
		if(temp->data == e)return SUCCESS;
		temp = temp->next;
	}
	return ERROR;
}

/**
 *  @name        : Status ReverseList(LinkedList *L)
 *	@description : reverse the linked list
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status ReverseList(LinkedList *L) {
	if(*L == NULL)
		return ERROR;
	else if((*L)->next == NULL)
		return SUCCESS;

	LNode *current, *pre ,*Next;
	pre = NULL;//ǰһ�����
	Next = (*L)->next;//��һ�����
	current = (*L);//��ǰ���
	while(current != NULL)
	{
		current->next = pre;
		pre = current;
		current = Next;
		if(current == NULL)break;//ע����Щ���Ž����ε�λ�ã�Ҫ�ж�ǰһ���ǲ��ǿյ� 
		Next = Next->next;
	}
	*L = pre;
	
	return SUCCESS;
}

/**
 *  @name        : Status IsLoopList(LinkedList L)
 *	@description : judge whether the linked list is looped
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status IsLoopList(LinkedList L) {
	LNode *fast,*slow;
	fast = slow = L;
	while(fast->next!=NULL && (fast->next)->next != NULL && slow->next != NULL)
	{
		fast = (fast->next)->next;
		slow = slow->next;
		if(fast == slow)return SUCCESS;
	}
	return ERROR;
}

/**
 *  @name        : LNode* ReverseEvenList(LinkedList *L)
 *	@description : reverse the nodes which value is an even number in the linked list, input: 1 -> 2 -> 3 -> 4  output: 2 -> 1 -> 4 -> 3
 *	@param		 : L(the head node)
 *	@return		 : LNode(the new head node)
 *  @notice      : choose to finish
 */
LNode* ReverseEvenList(LinkedList *L) {
	if((*L)->next == NULL)//����ֻ��һ����� 
	{
		printf("����Ԫ��С��������\n");
		return *L;
	}
	//first second ָ��ÿ���Խ��
	//left right ָ������������������ 
	LNode *first, *second, *left, *right;
	//���صĵ�ַ��Ҳ���ǵڶ�������ַ 
	LNode *head = (*L)->next;
	//��ʼ�� 
	first = *L;
	second = first->next;
	left = NULL;
	//����������ԣ����� 
	while(first && second)
	{
		right = second->next;
		if(left)
			left->next = second;
		second->next = first;
		first->next = right;
		left = first;
		first = right;
		if(!first)break;//���û����һ����㣬ֱ���˳�ѭ�� 
		second = first->next;
	}
	return head;
	

	
	/*�����˼·��ֱ�ӽ���ÿ���Ե�ֵ 
	*	
	LNode *first, *second;
	first = *L;
	second = first->next;
	while(first && second)
	{
		ElemType temp;
		temp = first->data;
		first->data = second->data;
		second->data = temp;

		first = second->next;
		if(!first)break;//�������û��Ԫ�أ�����
		second = first->next;
	}
	printf("��ת�ɹ���\n");
	return *L;
	*/
}

/**
 *  @name        : LNode* FindMidNode(LinkedList *L)
 *	@description : find the middle node in the linked list
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : choose to finish
 */
LNode* FindMidNode(LinkedList *L) {
	LNode *mid,*end;
	mid = end = *L;
	//ͨ�������ָ��Ĳ��������Ա�֤midָ��ָ��Ľ�����ڿ�ʼ��㵽endָ��Ľ��֮���
	while(end != NULL && end->next != NULL)//��֤endָ�벻����ָ
	{
		//ǰ������
		end = (end->next)->next;
		if(!end)break;
		//����һ��end����ʱ,ǰ��һ��
		mid = mid->next;
	}
	return mid;
}

//������� 
void out(ElemType c)
{
	printf("%d->",c);
}

//���Һ��� ������ֵΪe��ǰһ������ַ 
LNode *SearchNode(LinkedList *L,ElemType e)
{
	LNode *temp = *L;
	while(temp->next != NULL)
	{
		if((temp->next)->data == e)
			return temp;
		temp = temp->next;
	}
}

//�ҵ�β��ָ�룺��������β������ַͬʱ�ѽ�㴴���� 
LNode *SearchEnd(LinkedList *L)
{
	LNode *temp = *L;
	while(temp->next != NULL)
		temp = temp->next;
	return temp;
}

//β������� 
Status Insert(LinkedList *L,int sum,ElemType item)
{
	LNode *temp = (LNode *)malloc(sizeof(LNode));
	if(temp == NULL)return ERROR;	
	temp->data = item;
	if(sum == 0)//��ʼ��ͷ��� 
	{
		(*L) = temp;
		temp->next = NULL;
	}
	else 
		InsertList(SearchEnd(L),temp);
	return SUCCESS;
}

//ɾ������
Status  Delete(LinkedList *L,ElemType e,int sum)
{
	int a;//��Ҳ��֪��ʲô�á�����Ҫ���˾�д 
	
	//����ý����ڣ�ɾ���ý�� 
	if(SearchList(*L, e)) 
	{
		if((*L)->data == e)//�����ͷ��� 
		{
			//����һ���� ,ֱ�ӷ��ؾ��� 
			if((*L)->next == NULL)return SUCCESS;
			LNode *temp = *L;
				*L = (*L)->next;
			free(temp);
			return SUCCESS;
		}
		//�����ҵ��ý�����һ����� 
		LNode *temp = SearchNode(L,e);
		DeleteList(temp, &a);
		return SUCCESS;		
	}
	else
		return ERROR;
		
}
//���ص�i������ָ�� 
LNode *LNodeI(LinkedList *L,int x)
{
	LNode *temp = *L;
	int i;
	for(i = 1; i<x; i++)//�ҵ�����λ�� 
		temp = temp->next;
	return temp;
}
//�ɲ����ĺ����б� 
char init()
{
	char ch,temp;
	printf(
			
			"-------------------------------------------------------\n"
			"a:��ʼ�����б�\n"
			"b:ɾ���б�\n"
			"c:���б�β������һ����Ŀ\n"
			"d:ɾ��һ����Ŀ\n"
			"e:��ӡ������Ŀ\n"
			"f:������Ŀ\n" 
			"g:����ת\n"
			"h:�ж������Ƿ�ɻ�\n"
			"i:��תż����Ŀ\n"
			"j:�����м���Ŀ\n"
			"k:�ڵ�i���������һ����Ŀ\n" 
			"q:�˳�����\n"
			"-------------------------------------------------------\n"
			);
	printf("������������еĲ���(ֻ�е�һ����ĸ��Ч)��");
	scanf(" %c",&ch);
	while((temp = getchar())!='\n')continue;
	//������ 
	while(ch!='q' && (ch < 'a' || ch > 'k'))
	{
		printf("��������: %c ����!���������룺",ch); 
		scanf(" %c",&ch);
		while((temp = getchar())!='\n')continue;
	}
	 return ch;
}
