#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SqStack.h"
#define INF  2000000000
#define MAX 10000

ElemType ori = {INF,0};//初始化
double Deal(long long x)
{
	double y = x;
	while(y>=1)
		y/=10;
	return y;
}
ElemType readnum(int *i,int len,char *strings)
{
	//ans做临时的变量存数，temp初始化
	long long ans = 0;
	ElemType temp = ori;
	//第一个判断保证不越界 第二个判断保证是数字字符或者小数点
	while((*i)<len && ((strings[(*i)] <='9' && strings[(*i)] >= '0') || strings[(*i)] == '.'))
	{
		if(temp.integer != INF && strings[(*i)] == '.')
		{
			temp.oper = 1;
			return temp;
		}
		if(strings[(*i)] == '.')
		{
			//小数点前半段
			temp.integer = ans;
			ans = 0;
			(*i)++;
			continue;
		}
		ans=ans*10 + strings[(*i)]-'0';
		(*i)++;
	}
	//回退一下，防止影响下一位的读取
	(*i)--;
	if(temp.integer == INF)temp.integer = ans;
	else//小数的处理：前半段加后半段
	{
		temp.decimal = temp.integer;
		temp.decimal += Deal(ans);
		temp.integer = INF;
	}
	return temp;
}
Status readin(SqStack *oper,SqStack *num)
{
	char strings[MAX];
	int len = 0;
	char ch;
	//读入数组中
	while((ch = getchar()) && ch != '\n')strings[len++] = ch;
	for(int i = 0;i < len;i++)
	{
		//空格跳过
		if(strings[i] == ' ')continue;
		//读入数字
		if(strings[i] >= '0' && strings[i] <= '9')
		{
			ElemType temp = readnum(&i,len,strings);
			//因为我们现在读入的是数字，所以oper为0,如果oper不为0，说明表达式有错，返回error
			if(temp.oper)return ERROR;
			//压入栈
			pushStack(num,temp);
		}
		//读入运算符
		else if(strings[i] == '+' || strings[i] == '-' || strings[i] == '*' || strings[i] == '/' || strings[i] == '(' || strings[i] == ')')
		{
			char ch  = strings[i];
			//如果到了尾部且不是运算符 ')' ，返回错误
			//因为其他运算符在尾部是不合法的
			if(ch != ')' && i == len - 1)return ERROR;
			//直接压入运算符栈
			if(ch == '(')
			{
				ElemType temp;
				temp.oper = ch;
				pushStack(oper,temp);
			}
			//把到'('前的所有运算符弹出运算符栈，放到后缀栈里面
			else if(ch == ')')
			{
				ElemType temp;
				//栈不为空
				while(!isEmptyStack(oper))
				{
					popStack(oper,&temp);
					if(temp.oper == '(')break;
					pushStack(num,temp);
				}
				//如果因为到栈底结束，且()不匹配成功，就返回错误
				if(isEmptyStack(oper) && temp.oper != '(')return ERROR;
			}
			else if(ch == '*' || ch == '/')//相同优先级
			{
				ElemType temp = ori;
				//如果运算符栈为空，直接压入
				if(isEmptyStack(oper))
				{
					temp.oper = ch;
					pushStack(oper,temp);
				}
				//否则，与栈顶运算符比较优先级
				else
				{
					while(!isEmptyStack(oper))
					{
						getTopStack(oper,&temp);
						//优先级比栈顶元素高时退出循环
						if(temp.oper == '(' || temp.oper == '-' || temp.oper == '+')break;
						popStack(oper,&temp);
						pushStack(num,temp);
					}
					temp.oper = ch;
					pushStack(oper,temp);
				}
			}
			else if(ch == '-' || ch == '+')//相同优先级
			{
				int flag = 0;//标记是否在'-'号后面的第一个运算符比'-'优先级高
				//'-'号稍微复杂，我们如果要考虑负数，就进行一下转换-a --> +(-a)

				//后面跟的是数字
				if(ch == '-' && strings[i+1] >= '0' && strings[i+1] <= '9')
				{
					//如果是负数的情况,不需要转换
					if(isEmptyStack(oper) && isEmptyStack(num))
					{
						ElemType temp;
						i++;
						temp = readnum(&i,len,strings);
						if(temp.oper)
						return ERROR;
						else if(temp.integer != INF)
							temp.integer = -temp.integer;
						else
							temp.decimal = -temp.decimal;
						pushStack(num,temp);
						continue;
					}
					else
					{
						int sign = 0;//标记
						for(int j = i-1;j>=0;j--)
						{
							if(strings[j] == ' ')continue;
							else if(strings[j] == '(')
							{
								ElemType temp;
								i++;
								temp = readnum(&i,len,strings);
								if(temp.oper)
									return ERROR;
								else if(temp.integer != INF)
									temp.integer = -temp.integer;
								else
									temp.decimal = -temp.decimal;
								pushStack(num,temp);
								sign = 1;
								break;
							}
							else break;
						}
						if(sign)continue;
					}
					/*
					*	检查'-'号的下一个运算符的级别
					*	如果比'-'级别高，说明先进行后面运算符的运算所以不能-a -->+(-a)
					*	例：3-4*2 先进行4*2
					*/
					for(int j = i+1;j<len;j++)
					{
						if(strings[j] == ' ' || strings[j] == '.')continue;
						else if(strings[j] <='9' && strings[j] >= '0')continue;
						else if(strings[j] == '*' || strings[j] == '/')flag = 1;
						else if(strings[j] == '-' || strings[j] == '+' || strings[j] == ')')break;
						else return ERROR;
						if(flag)break;
					}
					//如果下一个优先级较高，直接把'-'号压栈，返回循环
					if(flag)
					{
						ElemType temp = ori;
						while(!isEmptyStack(oper))
						{
							getTopStack(oper,&temp);
							if(temp.oper == '(')break;
							popStack(oper,&temp);
							pushStack(num,temp);
						}
						temp.oper = ch;
						pushStack(oper,temp);
						continue;
					}
					//如果下一个优先级没有高过'-'，转换如下：
					/*
						先把'+'压入运算符栈
						再将数字压入后缀表达式栈
					*/
					//1.把'+'压入运算符栈
					ElemType temp = ori;
					while(!isEmptyStack(oper))
					{
						getTopStack(oper,&temp);
						if(temp.oper == '(')break;
						popStack(oper,&temp);
						pushStack(num,temp);
					}
					temp.oper = '+';
					pushStack(oper,temp);
					//2.数字压入后缀表达式栈
					i++;//跳到数字位
					temp = readnum(&i,len,strings);
					if(temp.oper)
						return ERROR;
					else if(temp.integer != INF)
						temp.integer = -temp.integer;
					else
						temp.decimal = -temp.decimal;
					pushStack(num,temp);

				}
				else//后面跟的不是数字，直接当作'-'运算符压栈
				{
					ElemType temp = ori;
					while(!isEmptyStack(oper))
					{
						getTopStack(oper,&temp);
						if(temp.oper == '(')break;
						popStack(oper,&temp);
						pushStack(num,temp);
					}
					temp.oper = ch;
					pushStack(oper,temp);
				}
			}
		}
		else return ERROR;
	}
	//运算符栈里面还有运算符，全部弹出
	while(!isEmptyStack(oper))
	{
		ElemType temp;
		popStack(oper,&temp);
		pushStack(num,temp);
	}
	return SUCCESS;
}
double sum[MAX];
int right;
int main()
{
	SqStack operators,numbers,Postfixpression;
	initStack(&Postfixpression,MAX);
	initStack(&operators,MAX);
	initStack(&numbers,MAX);
	char ch;
	while((ch = init()) && ch!='q')
	{
		//初始化
		clearStack(&Postfixpression);
		clearStack(&operators);
		clearStack(&operators);
		memset(sum,0,sizeof(sum));
		right = 0;
		printf("\t请输入中缀表达式: ");
		if(!readin(&operators,&numbers))
			printf("\t输入含非法字符，请重新输入!\n");
		else
		{
			ElemType temp;
			int flag = 0;//标记有没有除法
			for(int i = 0;i<=numbers.top;i++)
			{
				if(numbers.elem[i].oper)
					printf("\t%c\n",numbers.elem[i].oper);
				else if(numbers.elem[i].integer!=INF)
					printf("\t%.1f\n",numbers.elem[i].integer*1.0);
				else
					printf("\t%.1f\n",numbers.elem[i].decimal);
			}
			while(!isEmptyStack(&numbers))
			{
				popStack(&numbers,&temp);
				pushStack(&Postfixpression,temp);
			}
			while(Postfixpression.top!=-1)
			{

				ElemType temp;
				popStack(&Postfixpression,&temp);
				char ch = temp.oper;
				if(ch == '-' || ch == '+' || ch == '*' || ch == '/')
				{
					if(ch == '-')sum[right-1] = sum[right-1] - sum[right];
					else if(ch == '+')sum[right-1] = sum[right-1] + sum[right];
					else if(ch == '*')sum[right-1] = sum[right-1] * sum[right];
					else if(ch == '/')
					{
						flag = 1;
						if(sum[right] == 0)
						{
							printf("\t错误操作：除0！\n");
							flag = 2;//有除法且除0
							break;
						}
						sum[right-1] = sum[right-1]/sum[right];
					}
					if(right>0)right--;
				}
				else
				{
					if(temp.integer != INF)
						sum[++right] = temp.integer;
					else
					{
						sum[++right] = temp.decimal;
						flag = 1;
					}
				}
			}

			if(flag == 1)printf("\t计算结果为：%.2f\n",sum[1]);
			else if(flag == 0) printf("\t计算结果为：%d\n",(int)sum[1]);


		}
		printf("\t按Enter键继续...");
		getchar();
		system("cls");
	}
	destroyStack(&operators);
	destroyStack(&numbers);
	printf("\t谢谢您的使用！\n\t祝您生活愉快，谢谢！手动狗头(～￣▽￣)～\n");
	getchar();
	return 0;
}
/*
	1. 12 + 13+(3-4*(3-1))//减4后面的运算符比负号高级 (已解决)
	2.初始化nuion类型问题：初始化int(类型) INF，char(类型) 0;当加到某个值上面去，或者改变某个的值，另外一个也跟着改变(已解决)
	temp.int = 0;//然后另外一个char也加1
	就算不初始化，也可能出问题。。。
	//1*10*(-1 +2 -1+(-1.2*5))
	(3*3-3)
*/
