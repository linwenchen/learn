#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "LinkBiTree.h"
//#include "LQueue.h"
Status InitBiTree(BiTree *T)
{
	(*T) = (BiTree)malloc(sizeof(BiTNode));
	//内存分配失败
	if(T == NULL)return ERROR;
	(*T)->lchild = (*T)->rchild = NULL;
	return SUCCESS;
}
Status DestroyBiTree(BiTree T)
{
	if(T == NULL)return ERROR;
	if(T->lchild)//左孩子
		DestroyBiTree(T->lchild);
	if(T->rchild)//右孩子
		DestroyBiTree(T->rchild);
	free(T);
	return SUCCESS;
}

Status CreateBiTree(BiTree T, char* definition)
{
	char *str = definition;
	int index = IndexOfOperator(str);
	//printf("index:%d\n",index);

	int len = strlen(str);
	int left = 0;
	int right = len - 1;
	if(index == -1)//操作数
	{
		while(str[left] == '(' && str[right] == ')' )
		{
			str[left++] = '\0';//清除
			str[right--] = '\0';//清除
		}
		T->data = str[left];
		str[left] = '\0';//清除
		//叶子节点没有左右孩子
		T->lchild = NULL;
		T->rchild = NULL;
		//printf("²Ù×÷Êý:%c\n",T->data);
	}
	else
	{
		T->data = str[index];
		str[index] = '\0';//清除
		//printf("²Ù×÷·û:%c\n",T->data);
		while(str[left] == '(' && str[right] == ')')//去除最外层的括号
		{
			//判断是否能清除(1)+(2)
			//方法：括号匹配
			int flag = 0;
			int bracket = 0;
			int i = left + 1;
			while(i<right)
			{
				if(str[i] == ')')bracket--;
				else if(str[i] == '(')bracket++;
				if(bracket < 0)flag = 1;
				if(flag)break;
				i++;
			}
			if(flag)break;
			str[left++] = '\0';//清除
			str[right--] = '\0';//清除
		}
		//左右孩子
		T->lchild = (BiTNode *)malloc(sizeof(BiTNode));
		if(T->lchild == NULL)return ERROR;
		T->rchild = (BiTNode *)malloc(sizeof(BiTNode));
		if(T->rchild == NULL)return ERROR;
		int a = CreateBiTree(T->lchild,str+left);
		int b = CreateBiTree(T->rchild,str + index + 1);
		if(!(a&&b))return ERROR;
	}
	return SUCCESS;
}

Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
	int a = 1,b = 1;
	if(!visit(T->data))return ERROR;
	if(T->lchild)
		a = PreOrderTraverse(T->lchild,visit);
	if(T->rchild)
		b = PreOrderTraverse(T->rchild,visit);
	if(!(a&&b))return ERROR;
	return SUCCESS;
}
Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
	int a = 1,b = 1;
	if(T->lchild)
		a =  InOrderTraverse(T->lchild,visit);
	if(!visit(T->data))return ERROR;
	if(T->rchild)
		b =  InOrderTraverse(T->rchild,visit);
	if(!(a&&b))return ERROR;
	return SUCCESS;
}
Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
	int a = 1,b = 1;
	if(T->lchild)
		a =  PostOrderTraverse(T->lchild,visit);
	if(T->rchild)
		b = PostOrderTraverse(T->rchild,visit);
	if(!visit(T->data))return ERROR;
	if(!(a&&b))return ERROR;
	return SUCCESS;
}
Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
	//链表模拟队列
	QueueNode q;
	Node *front,*rear;//头尾指针
	q = (QueueNode)malloc(sizeof(Node));
	if(q == NULL)return ERROR;
	q->next = NULL;
	q->now = T;
	front = rear = q;
	while(front)
	{
		BiTNode *temp = front->now;
		visit(temp->data);
		if(temp->lchild)
		{
			Node *p = (Node *)malloc(sizeof(Node));
			if(p == NULL)return ERROR;
			p->now = temp->lchild;
			p->next = NULL;
			rear->next = p;
			rear = p;
		}
		if(temp->rchild)
		{
			Node *p = (Node *)malloc(sizeof(Node));
			if(p == NULL)return ERROR;
			p->now = temp->rchild;
			p->next = NULL;
			rear->next = p;
			rear = p;
		}
		Node *pp = front;
		front = front->next;
		free(pp);
	}
	return SUCCESS;
}
int Value(BiTree T)			//表达式求值
{
	static int error = 0;
	if(T->data >= '0' && T->data <= '9')
		return (T->data-'0');
	else
	{
		int a,b;
		a = Value(T->lchild);
		b = Value(T->rchild);
		if(error)return error;
		switch(T->data)
		{
			case '+':return (a+b);
			case '-':return (a-b);
			case '*':return (a*b);
			case '/':
				{
					if(b == 0)error = -2000001000;
					else return (a/b);
				}
			default: return error;
		}
	}
}

Status Print(TElemType e)
{
	printf("%c ",e);
	return SUCCESS;
}
char * PreProcess(char str[])
{
	int len = strlen(str);
	char *p = (char *)malloc(len * sizeof(char));
	int i = 0,j = 0;
	int parleft = 0;//左括号
	int parright = 0;//右括号
	while(i<len)
	{
		if(str[i] == ' ')
		{
			i++;
			continue;
		}
		//括号匹配
		else if(str[i] == '(')parleft++;
		else if(str[i] == ')')parright++;
		if(parleft < parright)return NULL;
		p[j++] = str[i++];
	}
	if(parleft != parright)return NULL;
	p[j] = '\0';
	len = j;
	j = 0;
	while(j<len)
	{
		if(p[j] == '+' || p[j] == '-' || p[j] == '*' || p[j] == '/')//操作符
		{
			//操作符没有操作数
			if(j-1 < 0 || j+1 == len)return NULL;
			// )- || -( 的形式 或者 操作数
			if(!(p[j-1] == ')' || isdigit(p[j-1])))return NULL;
			if(!(p[j+1] == '(' || isdigit(p[j+1])))return NULL;
			if(p[j] == '-')
			{
				if( !(p[j-1] == ')' || (p[j-1] >= 0 && p[j-1] <= '9')))//判断是否未负号
					return NULL;
			}
		}
		else if((p[j] <= '9' && p[j] >= '0') || p[j] == '(' || p[j] == ')')//括号和操作数
		{
			if(p[j] <= '9' && p[j] >= '0')//数字
			{
				//数字两边可以没有东西
				if(j == len - 1 && j == 0);
				else
				{
					if(j != 0)//左
						if(!(isoperator(p[j-1]) || p[j-1] == '('))return NULL;
					if(j != len-1)//右
						if(!(isoperator(p[j+1]) || p[j+1] == ')'))return NULL;
				}
			}
			//左右括号
			else if(p[j] == '(')
			{
				//左边一定要是操作符或者左括号或者没有
				//右边一定要是数字或者左括号
				if(j != 0)
					if(!(isoperator(p[j-1]) || p[j-1] == '('))return NULL;
				if(!(isdigit(p[j+1]) || p[j+1] == '('))return NULL;
			}
			else if(p[j] == ')')
			{
				//左边一定要是数字或者右括号
				//右边一定要是操作符或者左括号或者没有
				if(j != len-1)
					if(!(isoperator(p[j+1]) || p[j+1] == ')'))return NULL;
				if(!(isdigit(p[j-1]) || p[j-1] == ')'))return NULL;
			}
		}
		else return NULL;
		j++;
	}
/*
	len = j;
	j = 0;
	while(j<len)
	{
		if(p[j] == '-')
		{
			if(!( p[j-1] == ')' || (p[j-1] >= 0 && p[j-1] <= '9')))//ÅÐ¶ÏÊÇ·ñ¿ÉÒÔµ±³É¸ººÅ
			{
				p[j] = '#';
			}
			j++;
		}

	}
*/
	return p;
}

int IndexOfOperator(char *str)//寻找最后执行的操作符的下标
{
	int i;
	int brackets = 0;//括号级别
	int index = -1;//返回下标
	int existAddOrMinus = 0;//减号
	int len = strlen(str);
	int left = 0;
	int right = len - 1;
	//判断是否能清除(1)+(2)
	//方法：括号匹配
	while(str[left] == '(' && str[right] == ')')//去除最外层的括号
	{
		int flag = 0;
		int bracket = 0;
		i = left + 1;
		while(i<right)
		{
			if(str[i] == ')')bracket--;
			else if(str[i] == '(')bracket++;
			if(bracket < 0)flag = 1;
			if(flag)break;
			i++;
		}
		if(flag)break;
		left++;
		right--;
	}
	for(i = left;i<=right;i++)
	{
		if(str[i] == '(')brackets++;//左括号
		else if(str[i] == ')')brackets--;//右括号
		else if((str[i] == '+' || str[i] == '-') && brackets == 0)
		{
			index = i;
			existAddOrMinus = 1;//存在加减号
		}
		 else if((str[i]=='*'||str[i]=='/')&&brackets==0 && existAddOrMinus==0)
        {
            index = i;
        }
	}
	return index;
}

int isoperator(char ch)
{
	if(ch == '+' || ch == '-' || ch == '*' || ch == '/')return 1;
	else return 0;
}
