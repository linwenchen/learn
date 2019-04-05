#include "AQueue.h"
#include <stdlib.h>
#include <stdio.h>
/**
 *  @name        : void InitAQueue(AQueue *Q)
 *    @description : ��ʼ������
 *    @param         Q ����ָ��Q
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
 *    @description : ���ٶ���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void DestoryAQueue(AQueue *Q)
{
	//ѭ���ͷſռ�
	for(int i = 0;i < MAXQUEUE; i++)
	{
		free(Q->data[i]);
		Q->data[i] = NULL;
	}
}


/**
 *  @name        : Status IsFullAQueue(const AQueue *Q)
 *    @description : �������Ƿ�����
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsFullAQueue(const AQueue *Q)
{
	//return (Q->rear-Q->front == MAXQUEUE)?TRUE:FALSE;
	return Q->length == MAXQUEUE?TRUE:FALSE;

}
/**
 *  @name        : Status IsEmptyAQueue(const AQueue *Q)
 *    @description : �������Ƿ�Ϊ��
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
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
 *    @description : �鿴��ͷԪ��
 *    @param         Q ����ָ��Q�����Ԫ��e
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ��
 */
Status GetHeadAQueue(AQueue *Q, void *e)
{
	//����Ϊ�գ����ش���
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
 *    @description : ȷ�����г���
 *    @param         Q ����ָ��Q
 *    @return         : ���г���count
 *  @notice      : None
 */
int LengthAQueue(AQueue *Q)
{
	return Q->length;
}

/**
 *  @name        : Status EnAQueue(AQueue *Q, void *data)
 *    @description : ��Ӳ���
 *    @param         Q ����ָ��Q,�������ָ��data
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ����˻�Ϊ��
 */
Status EnAQueue(AQueue *Q, void *data)
{
	//�����������޷����
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
 *    @description : ���Ӳ���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
Status DeAQueue(AQueue *Q)
{
	//����Ϊ�գ��޷�ȡ��
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
 *    @description : ��ն���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void ClearAQueue(AQueue *Q)
{
	//ָ��ͬһλ��
	Q->front = Q->rear;
	Q->length = 0;
}

/**
 *  @name        : Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q))
 *    @description : ������������
 *    @param         Q ����ָ��Q����������ָ��foo
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
 *    @description : ��������
 *    @param         q ָ��q
 *  @notice      : None
 */
void APrint(void *q)
{
	//void* ָ��Ϊ�գ�����
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
