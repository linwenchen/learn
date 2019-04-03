#include <stdio.h>
#include <stdlib.h>
#include "SqStack.h"
//˳��ջ(���������)
Status initStack(SqStack *s,int sizes)  //��ʼ��ջ
{
	if(s->elem != NULL)destroyStack(s);
	s->elem = (ElemType *)malloc(sizes * sizeof(ElemType));
	//ջ��ʼ��ʧ�ܣ�
	if(NULL == s->elem)return ERROR;
	s->top = -1;
	s->size = sizes;
	return SUCCESS;
}
Status isEmptyStack(SqStack *s)   //�ж�ջ�Ƿ�Ϊ��
{
	//ָ��ָ��ջ�ף�˵��ջΪ�ա�
	if(s->top == -1)return SUCCESS;
	else return ERROR;
}
Status getTopStack(SqStack *s,ElemType *e)   //�õ�ջ��Ԫ��
{
	//ջΪ�շ���ERROR��
	if(isEmptyStack(s))return ERROR;
	else
	{
		//ȡջ��Ԫ��
		*e = s->elem[s->top];
		return SUCCESS;
	}
}
Status clearStack(SqStack *s)   //���ջ
{
	//���ջΪ�շ���ERROR��
	if(s->top == -1)return ERROR;
	//��ָ��ָ��ջ��
	s->top = -1;
	return SUCCESS;
}
Status destroyStack(SqStack *s)  //����ջ
{
	//���ջ�ռ䲻����,����ERROR��
	if(s->elem == NULL)return ERROR;
	//�ͷ�����ռ�
	free(s->elem);
	//ָ��ָ���
	s->elem = NULL;
	return SUCCESS;
}
Status stackLength(SqStack *s,int *length)   //���ջ����
{
	if(s->elem == NULL)return ERROR;
	*length = s->size;
	return SUCCESS;
}
Status pushStack(SqStack *s,ElemType data)  //��ջ
{
	//ջ��������ERROR��
	if(s->size == s->top + 1)return ERROR;
	s->elem[++(s->top)] = data;
	return SUCCESS;
}
Status popStack(SqStack *s,ElemType *data)   //��ջ
{
	//ջΪ�շ���ERROR��
	if(isEmptyStack(s))return ERROR;
	*data = s->elem[(s->top)--];
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
