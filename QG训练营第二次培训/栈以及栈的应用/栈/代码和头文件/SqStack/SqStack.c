#include <stdio.h>
#include <stdlib.h>
#include "SqStack.h"
//顺序栈(基于数组的)
Status initStack(SqStack *s,int sizes)  //初始化栈
{
	if(s->elem != NULL)destroyStack(s);
	s->elem = (ElemType *)malloc(sizes * sizeof(ElemType));
	//栈初始化失败！
	if(NULL == s->elem)return ERROR;
	s->top = -1;
	s->size = sizes;
	return SUCCESS;
}
Status isEmptyStack(SqStack *s)   //判断栈是否为空
{
	//指针指向栈底，说明栈为空。
	if(s->top == -1)return SUCCESS;
	else return ERROR;
}
Status getTopStack(SqStack *s,ElemType *e)   //得到栈顶元素
{
	//栈为空返回ERROR！
	if(isEmptyStack(s))return ERROR;
	else
	{
		//取栈顶元素
		*e = s->elem[s->top];
		return SUCCESS;
	}
}
Status clearStack(SqStack *s)   //清空栈
{
	//如果栈为空返回ERROR！
	if(s->top == -1)return ERROR;
	//让指针指向栈底
	s->top = -1;
	return SUCCESS;
}
Status destroyStack(SqStack *s)  //销毁栈
{
	//如果栈空间不存在,返回ERROR！
	if(s->elem == NULL)return ERROR;
	//释放数组空间
	free(s->elem);
	//指针指向空
	s->elem = NULL;
	return SUCCESS;
}
Status stackLength(SqStack *s,int *length)   //检测栈长度
{
	if(s->elem == NULL)return ERROR;
	*length = s->size;
	return SUCCESS;
}
Status pushStack(SqStack *s,ElemType data)  //入栈
{
	//栈已满返回ERROR！
	if(s->size == s->top + 1)return ERROR;
	s->elem[++(s->top)] = data;
	return SUCCESS;
}
Status popStack(SqStack *s,ElemType *data)   //出栈
{
	//栈为空返回ERROR！
	if(isEmptyStack(s))return ERROR;
	*data = s->elem[(s->top)--];
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
