#include <stdio.h>
#include "LinkStrack.h"
#include <stdlib.h>
//链栈(基于链表的)
Status initLStack(LinkStack *s)   //初始化
{
	//在有链栈的基础上初始化,先销毁栈
	if(s->top != NULL)destroyLStack(s);
	//链表指向空,计数初始化为0
	s->top = NULL;
	s->count = 0;
	return SUCCESS;
}
Status isEmptyLStack(LinkStack *s)  //判断链栈是否为空
{
	//若元素个数为0即为空
	if(s->count == 0)return SUCCESS;
	else return ERROR;
}
Status getTopLStack(LinkStack *s,ElemType *e)  //得到栈顶元素
{
	//如果栈为空,返回
	if(isEmptyLStack(s))return ERROR;
	//top指针指向的数据赋值给e
	*e = (s->top)->data;
	return SUCCESS;
}
Status clearLStack(LinkStack *s)   //清空栈
{
	//如果栈为空,返回
	if(isEmptyLStack(s))return SUCCESS;
	//循环释放空间
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
Status destroyLStack(LinkStack *s)   //销毁栈
{
	//如果栈为空,返回
	if(isEmptyLStack(s))return SUCCESS;
	//循环释放空间
	while(s->top != NULL)
	{
		StackNode *temp;
		temp = s->top;
		s->top = (s->top)->next;
		free(temp);
	}
	return SUCCESS;
}
Status LStackLength(LinkStack *s,int *length)    //检测栈长度
{
	*length = s->count;
	return SUCCESS;
}
Status pushLStack(LinkStack *s,ElemType data)   //入栈
{
	//初始化一个结点,并分配空间
	StackNode *temp;
	temp = (StackNode *)malloc(sizeof(StackNode));
	if(temp == NULL)return ERROR;
	temp->data = data;//赋值
	temp->next = s->top;//temp的下一个指向
	s->top = temp;//移动头指针
	s->count+=1;//计数加1
	return SUCCESS;
}
Status popLStack(LinkStack *s,ElemType *data)   //出栈
{
	//栈为空,返回
	if(s->count == 0)return ERROR;
	//初始化一个指针,用来释放空间
	StackNode *temp;
	temp = s->top;
	*data = temp->data;
	//头指针跳到下一个结点
	s->top = (s->top)->next;
	free(temp);
	return SUCCESS;
}
char init()
{
	char ch,temp;
	printf(

			"\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\t\n"
			"\t|a:初始化栈                                             |\t\n"
			"\t|b:入栈                                                 |\t\n"
			"\t|c:出栈                                                 |\t\n"
			"\t|d:检测栈长度                                           |\t\n"
			"\t|e:判断栈是否为空                                       |\t\n"
			"\t|f:得到栈顶元素                                         |\t\n"
			"\t|g:清空栈                                               |\t\n"
			"\t|h:销毁栈                                               |\t\n"
			"\t|i:快速入栈                                             |\t\n"
			"\t|q:退出程序                                             |\t\n"
			"\t|_______________________________________________________|\t\n\n"
			);
	printf("\t请输入你想进行的操作(只有第一个字母有效)：");
	scanf(" %c",&ch);
	while((temp = getchar())!='\n')continue;
	//输入检测
	while(ch!='q' && (ch < 'a' || ch > 'i'))
	{
		printf("\t您的输入: '%c' 有误!请重新输入：",ch);
		scanf(" %c",&ch);
		while((temp = getchar())!='\n')continue;
	}
	 return ch;
}
