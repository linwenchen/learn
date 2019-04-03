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
	(*L)->next = NULL;//一定要将结点的next置为NULL! 
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
	if(p->next == NULL)//p节点后面为空 
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
	if(p->next == NULL)return ERROR;//p是链表最后的结点 
	else if((p->next)->next == NULL)//p存在下一个结点且结点后面没结点 
	{
		LNode *temp = p->next;
		*e = temp->data;
		free(temp);
		p->next = NULL;//让指针指向空 
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
	pre = NULL;//前一个结点
	Next = (*L)->next;//下一个结点
	current = (*L);//当前结点
	while(current != NULL)
	{
		current->next = pre;
		pre = current;
		current = Next;
		if(current == NULL)break;//注意这些连着进两次的位置，要判断前一个是不是空的 
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
	if((*L)->next == NULL)//链表只有一个结点 
	{
		printf("链表元素小于两个！\n");
		return *L;
	}
	//first second 指向每两对结点
	//left right 指向上面两个结点的两边 
	LNode *first, *second, *left, *right;
	//返回的地址，也就是第二个结点地址 
	LNode *head = (*L)->next;
	//初始化 
	first = *L;
	second = first->next;
	left = NULL;
	//如果存在两对，交换 
	while(first && second)
	{
		right = second->next;
		if(left)
			left->next = second;
		second->next = first;
		first->next = right;
		left = first;
		first = right;
		if(!first)break;//如果没有下一个结点，直接退出循环 
		second = first->next;
	}
	return head;
	

	
	/*另外的思路：直接交换每两对的值 
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
		if(!first)break;//如果后面没有元素，结束
		second = first->next;
	}
	printf("翻转成功！\n");
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
	//通过差开两个指针的步伐，可以保证mid指针指向的结点是在开始结点到end指向的结点之间的
	while(end != NULL && end->next != NULL)//保证end指针不会乱指
	{
		//前进两步
		end = (end->next)->next;
		if(!end)break;
		//当下一个end存在时,前进一步
		mid = mid->next;
	}
	return mid;
}

//输出函数 
void out(ElemType c)
{
	printf("%d->",c);
}

//查找函数 ：返回值为e的前一个结点地址 
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

//找到尾部指针：返回链表尾部结点地址同时把结点创建好 
LNode *SearchEnd(LinkedList *L)
{
	LNode *temp = *L;
	while(temp->next != NULL)
		temp = temp->next;
	return temp;
}

//尾插入操作 
Status Insert(LinkedList *L,int sum,ElemType item)
{
	LNode *temp = (LNode *)malloc(sizeof(LNode));
	if(temp == NULL)return ERROR;	
	temp->data = item;
	if(sum == 0)//初始化头结点 
	{
		(*L) = temp;
		temp->next = NULL;
	}
	else 
		InsertList(SearchEnd(L),temp);
	return SUCCESS;
}

//删除操作
Status  Delete(LinkedList *L,ElemType e,int sum)
{
	int a;//我也不知道什么用。。。要求了就写 
	
	//如果该结点存在，删除该结点 
	if(SearchList(*L, e)) 
	{
		if((*L)->data == e)//如果是头结点 
		{
			//单独一个点 ,直接返回就行 
			if((*L)->next == NULL)return SUCCESS;
			LNode *temp = *L;
				*L = (*L)->next;
			free(temp);
			return SUCCESS;
		}
		//否则找到该结点的上一个结点 
		LNode *temp = SearchNode(L,e);
		DeleteList(temp, &a);
		return SUCCESS;		
	}
	else
		return ERROR;
		
}
//返回第i个结点的指针 
LNode *LNodeI(LinkedList *L,int x)
{
	LNode *temp = *L;
	int i;
	for(i = 1; i<x; i++)//找到结点的位置 
		temp = temp->next;
	return temp;
}
//可操作的函数列表 
char init()
{
	char ch,temp;
	printf(
			
			"-------------------------------------------------------\n"
			"a:初始化空列表\n"
			"b:删除列表\n"
			"c:往列表尾部插入一个项目\n"
			"d:删除一个项目\n"
			"e:打印链表项目\n"
			"f:查找项目\n" 
			"g:链表翻转\n"
			"h:判断链表是否成环\n"
			"i:翻转偶数项目\n"
			"j:查找中间项目\n"
			"k:在第i个结点后插入一个项目\n" 
			"q:退出程序\n"
			"-------------------------------------------------------\n"
			);
	printf("请输入你想进行的操作(只有第一个字母有效)：");
	scanf(" %c",&ch);
	while((temp = getchar())!='\n')continue;
	//输入检测 
	while(ch!='q' && (ch < 'a' || ch > 'k'))
	{
		printf("您的输入: %c 有误!请重新输入：",ch); 
		scanf(" %c",&ch);
		while((temp = getchar())!='\n')continue;
	}
	 return ch;
}
