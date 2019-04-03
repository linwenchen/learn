#include <stdio.h>
#include "LinkStrack.h"
#include <stdlib.h>
//��ջ(���������)
Status initLStack(LinkStack *s)   //��ʼ��
{
	//������ջ�Ļ����ϳ�ʼ��,������ջ
	if(s->top != NULL)destroyLStack(s);
	//����ָ���,������ʼ��Ϊ0
	s->top = NULL;
	s->count = 0;
	return SUCCESS;
}
Status isEmptyLStack(LinkStack *s)  //�ж���ջ�Ƿ�Ϊ��
{
	//��Ԫ�ظ���Ϊ0��Ϊ��
	if(s->count == 0)return SUCCESS;
	else return ERROR;
}
Status getTopLStack(LinkStack *s,ElemType *e)  //�õ�ջ��Ԫ��
{
	//���ջΪ��,����
	if(isEmptyLStack(s))return ERROR;
	//topָ��ָ������ݸ�ֵ��e
	*e = (s->top)->data;
	return SUCCESS;
}
Status clearLStack(LinkStack *s)   //���ջ
{
	//���ջΪ��,����
	if(isEmptyLStack(s))return SUCCESS;
	//ѭ���ͷſռ�
	while(s->top != NULL)
	{
		StackNode *temp;
		temp = s->top;
		s->top = (s->top)->next;
		free(temp);
	}
	s->count = 0;
	return SUCCESS;
}
Status destroyLStack(LinkStack *s)   //����ջ
{
	//���ջΪ��,����
	if(isEmptyLStack(s))return SUCCESS;
	//ѭ���ͷſռ�
	while(s->top != NULL)
	{
		StackNode *temp;
		temp = s->top;
		s->top = (s->top)->next;
		free(temp);
	}
	return SUCCESS;
}
Status LStackLength(LinkStack *s,int *length)    //���ջ����
{
	*length = s->count;
	return SUCCESS;
}
Status pushLStack(LinkStack *s,ElemType data)   //��ջ
{
	//��ʼ��һ�����,������ռ�
	StackNode *temp;
	temp = (StackNode *)malloc(sizeof(StackNode));
	if(temp == NULL)return ERROR;
	temp->data = data;//��ֵ
	temp->next = s->top;//temp����һ��ָ��
	s->top = temp;//�ƶ�ͷָ��
	s->count+=1;//������1
	return SUCCESS;
}
Status popLStack(LinkStack *s,ElemType *data)   //��ջ
{
	//ջΪ��,����
	if(s->count == 0)return ERROR;
	//��ʼ��һ��ָ��,�����ͷſռ�
	StackNode *temp;
	temp = s->top;
	*data = temp->data;
	//ͷָ��������һ�����
	s->top = (s->top)->next;
	free(temp);
	return SUCCESS;
}
char init()
{
	char ch,temp;
	printf(

			"\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\t\n"
			"\t|a:��ʼ��ջ                                             |\t\n"
			"\t|b:��ջ                                                 |\t\n"
			"\t|c:��ջ                                                 |\t\n"
			"\t|d:���ջ����                                           |\t\n"
			"\t|e:�ж�ջ�Ƿ�Ϊ��                                       |\t\n"
			"\t|f:�õ�ջ��Ԫ��                                         |\t\n"
			"\t|g:���ջ                                               |\t\n"
			"\t|h:����ջ                                               |\t\n"
			"\t|i:������ջ                                             |\t\n"
			"\t|q:�˳�����                                             |\t\n"
			"\t|_______________________________________________________|\t\n\n"
			);
	printf("\t������������еĲ���(ֻ�е�һ����ĸ��Ч)��");
	scanf(" %c",&ch);
	while((temp = getchar())!='\n')continue;
	//������
	while(ch!='q' && (ch < 'a' || ch > 'i'))
	{
		printf("\t��������: '%c' ����!���������룺",ch);
		scanf(" %c",&ch);
		while((temp = getchar())!='\n')continue;
	}
	 return ch;
}
