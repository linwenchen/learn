#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "LQueue.h"
/**
 *  @name        : void InitLQueue(LQueue *Q)
 *    @description : 初始化队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void InitLQueue(LQueue *Q)
{
	if(Q->front)DestoryLQueue(Q);
	Q->front = NULL;
	Q->length = 0;
	Q->rear = NULL;
}
/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : 销毁队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue *Q)
{
	while(Q->front)
	{
		Node *temp;
		temp = Q->front;
		Q->front = temp->next;
		//释放结点内容
		free(temp->data);
		//释放结点
		free(temp);
	}
}

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针Q
 *    @return         : 空-TRUE; 未空-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q)
{
	return Q->length == 0?TRUE:FALSE;
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : 查看队头元素
 *    @param         Q e 队列指针Q,返回数据指针e
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
Status GetHeadLQueue(LQueue *Q, void *e)
{
	//队列为空，返回错误
	if(IsEmptyLQueue(Q))return FALSE;
	//不确定类型指针强转然后修改e的值
	*(Type *)e = *((Type *)(Q->front->data));
	return TRUE;
}

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : 确定队列长度
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
int LengthLQueue(LQueue *Q)
{
	return Q->length;
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : 入队操作
 *    @param         Q 队列指针Q,入队数据指针data
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否为空
 */
Status EnLQueue(LQueue *Q, void *data)
{
	if(Q->rear == NULL)//还没有队列
	{
		Node *temp = (Node *)malloc(sizeof(Node));
		if(temp == NULL)return FALSE;
		temp->data = data;
		temp->next = NULL;
		//头尾指针指向第一个结点
		Q->front = Q->rear = temp;
		Q->length++;
	}
	else if(Q->rear->next == NULL)//有队列但是下一个还没有结点
	{
		Node *temp = (Node *)malloc(sizeof(Node));
		if(temp == NULL)return FALSE;
		temp->data = data;
		temp->next = NULL;
		//尾指针后移
		Q->rear->next = temp;
		Q->rear = temp;
		Q->length++;

	}
	else
	{
		Q->rear->data = data;
		Q->rear = Q->rear->next;
		Q->length++;
	}
	return TRUE;
}

/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : 出队操作
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q)
{
	//队列为空
	if(IsEmptyLQueue(Q))return FALSE;
	if(Q->length == 1)Q->rear = NULL;
	//头指针后移
	Node *temp = Q->front;
	Q->front = temp->next;
	//释放内容
	free(temp->data);
	//释放结点
	free(temp);
	Q->length--;
	return TRUE;

}

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : 清空队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void ClearLQueue(LQueue *Q)
{
	Q->rear = Q->front;
	Q->length = 0;
}

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : 遍历函数操作
 *    @param         Q 队列指针Q，操作函数指针foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
{
	if(IsEmptyLQueue(Q))return FALSE;
	Node *temp = Q->front;
	int i = 0;
	while(temp && i<Q->length)
	{
		foo(temp->data);
		temp = temp->next;
		i++;
	}
	return TRUE;
}

/**
 *  @name        : void LPrint(void *q)
 *    @description : 操作函数
 *    @param         q 指针q

 *  @notice      : None
 */
void LPrint(void *q)
{
	//void* 指针为空，返回
	if(q == NULL)return;
	Type *temp = (Type *)q;

	switch(temp->type)
	{
		case CHARACTER:
		{
			printf("\t%c\n",temp->character);

			break;
		}
		case STRING:
		{
			printf("\t%s\n",temp->strings);
			break;
		}
		case INTEGER:
		{
			printf("\t%d\n",temp->integer);
			break;
		}
		case REAL_NUMBER:
		{
			printf("\t%f\n",temp->real_number);
			break;
		}

	}
}
