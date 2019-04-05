#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "LQueue.h"
/**
 *  @name        : void InitLQueue(LQueue *Q)
 *    @description : ��ʼ������
 *    @param         Q ����ָ��Q
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
 *    @description : ���ٶ���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue *Q)
{
	while(Q->front)
	{
		Node *temp;
		temp = Q->front;
		Q->front = temp->next;
		//�ͷŽ������
		free(temp->data);
		//�ͷŽ��
		free(temp);
	}
}

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : �������Ƿ�Ϊ��
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q)
{
	return Q->length == 0?TRUE:FALSE;
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : �鿴��ͷԪ��
 *    @param         Q e ����ָ��Q,��������ָ��e
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ��
 */
Status GetHeadLQueue(LQueue *Q, void *e)
{
	//����Ϊ�գ����ش���
	if(IsEmptyLQueue(Q))return FALSE;
	//��ȷ������ָ��ǿתȻ���޸�e��ֵ
	*(Type *)e = *((Type *)(Q->front->data));
	return TRUE;
}

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : ȷ�����г���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
int LengthLQueue(LQueue *Q)
{
	return Q->length;
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : ��Ӳ���
 *    @param         Q ����ָ��Q,�������ָ��data
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ�Ϊ��
 */
Status EnLQueue(LQueue *Q, void *data)
{
	if(Q->rear == NULL)//��û�ж���
	{
		Node *temp = (Node *)malloc(sizeof(Node));
		if(temp == NULL)return FALSE;
		temp->data = data;
		temp->next = NULL;
		//ͷβָ��ָ���һ�����
		Q->front = Q->rear = temp;
		Q->length++;
	}
	else if(Q->rear->next == NULL)//�ж��е�����һ����û�н��
	{
		Node *temp = (Node *)malloc(sizeof(Node));
		if(temp == NULL)return FALSE;
		temp->data = data;
		temp->next = NULL;
		//βָ�����
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
 *    @description : ���Ӳ���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q)
{
	//����Ϊ��
	if(IsEmptyLQueue(Q))return FALSE;
	if(Q->length == 1)Q->rear = NULL;
	//ͷָ�����
	Node *temp = Q->front;
	Q->front = temp->next;
	//�ͷ�����
	free(temp->data);
	//�ͷŽ��
	free(temp);
	Q->length--;
	return TRUE;

}

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : ��ն���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void ClearLQueue(LQueue *Q)
{
	Q->rear = Q->front;
	Q->length = 0;
}

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : ������������
 *    @param         Q ����ָ��Q����������ָ��foo
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
 *    @description : ��������
 *    @param         q ָ��q

 *  @notice      : None
 */
void LPrint(void *q)
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
