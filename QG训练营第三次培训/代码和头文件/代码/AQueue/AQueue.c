#include "AQueue.h"
#include <stdlib.h>
#include <stdio.h>
/**
 *  @name        : void InitAQueue(AQueue *Q)
 *    @description : 初始化队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void InitAQueue(AQueue *Q)
{
	int i;
	for(i = 0;i < MAXQUEUE;i++)
	{
		Q->data[i] = (void *)malloc(sizeof(void *));
		Q->data[i] = NULL;
		//printf("%p %p\n",&(Q->data[i]),Q->data[i]);
	}
	//printf("%d",sizeof(Q->data));
	Q->front = 0;
	Q->rear = 0;
	Q->length = 0;
}
/**
 *  @name        : void DestoryAQueue(AQueue *Q)
 *    @description : 销毁队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void DestoryAQueue(AQueue *Q)
{
	//循环释放空间
	for(int i = 0;i < MAXQUEUE; i++)
	{
		free(Q->data[i]);
		Q->data[i] = NULL;
	}
}


/**
 *  @name        : Status IsFullAQueue(const AQueue *Q)
 *    @description : 检查队列是否已满
 *    @param         Q 队列指针Q
 *    @return         : 满-TRUE; 未满-FALSE
 *  @notice      : None
 */
Status IsFullAQueue(const AQueue *Q)
{
	//return (Q->rear-Q->front == MAXQUEUE)?TRUE:FALSE;
	return Q->length == MAXQUEUE?TRUE:FALSE;

}
/**
 *  @name        : Status IsEmptyAQueue(const AQueue *Q)
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针Q
 *    @return         : 空-TRUE; 未空-FALSE
 *  @notice      : None
 */
Status IsEmptyAQueue(const AQueue *Q)
{
	//if(Q->front == Q->rear)return TRUE;
	//return FALSE;
	return (Q->length == 0)?TRUE:FALSE;
}

/**
 *  @name        : Status GetHeadAQueue(AQueue *Q, void *e)
 *    @description : 查看队头元素
 *    @param         Q 队列指针Q，存放元素e
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
Status GetHeadAQueue(AQueue *Q, void *e)
{
	//队列为空，返回错误
	if(IsEmptyAQueue(Q))return FALSE;
	*(Type *)e = *((Type *)(Q->data[Q->front]));
	//Type *p = (Type *)e;
	//Type *q = (Type *)Q->data[Q->front];
	//p = (Type *)malloc(sizeof(Type));
	//*p = *q;
	return TRUE;
}

/**
 *  @name        : int LengthAQueue(AQueue *Q)
 *    @description : 确定队列长度
 *    @param         Q 队列指针Q
 *    @return         : 队列长度count
 *  @notice      : None
 */
int LengthAQueue(AQueue *Q)
{
	return Q->length;
}

/**
 *  @name        : Status EnAQueue(AQueue *Q, void *data)
 *    @description : 入队操作
 *    @param         Q 队列指针Q,入队数据指针data
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否满了或为空
 */
Status EnAQueue(AQueue *Q, void *data)
{
	//队列已满，无法添加
	if(IsFullAQueue(Q))return FALSE;
	else
	{
		Q->data[(Q->rear++) % MAXQUEUE] = data;
		Q->length++;
	}
	return TRUE;
}
/**
 *  @name        : Status DeAQueue(AQueue *Q)
 *    @description : 出队操作
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status DeAQueue(AQueue *Q)
{
	//队列为空，无法取出
	if(IsEmptyAQueue(Q))return FALSE;
	else
	{
		free(Q->data[Q->front]);
		Q->data[Q->front++] = NULL;
		Q->length--;
	}
	return TRUE;
}
/**
 *  @name        : void ClearAQueue(Queue *Q)
 *    @description : 清空队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void ClearAQueue(AQueue *Q)
{
	//指向同一位置
	Q->front = Q->rear;
	Q->length = 0;
}

/**
 *  @name        : Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q))
 *    @description : 遍历函数操作
 *    @param         Q 队列指针Q，操作函数指针foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q))
{
	if(IsEmptyAQueue(Q))return FALSE;
	for(int i = Q->front;i<Q->rear;i++)
		foo(Q->data[i%MAXQUEUE]);
	return TRUE;
}


/**
 *  @name        : void APrint(void *q)
 *    @description : 操作函数
 *    @param         q 指针q
 *  @notice      : None
 */
void APrint(void *q)
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
/*
int Type_select(Type a)
{
	if(a.character)return CHARACTER;
	else if(a.strings[0])return STRING;
	else if(a.integer != INF)return INTEGER;
	else return REAL_NUMBER;
}
*/
