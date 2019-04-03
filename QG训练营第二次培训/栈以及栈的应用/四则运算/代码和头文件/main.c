#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SqStack.h"
#define INF  2000000000
#define MAX 10000

ElemType ori = {INF,0};//��ʼ��
double Deal(long long x)
{
	double y = x;
	while(y>=1)
		y/=10;
	return y;
}
ElemType readnum(int *i,int len,char *strings)
{
	//ans����ʱ�ı���������temp��ʼ��
	long long ans = 0;
	ElemType temp = ori;
	//��һ���жϱ�֤��Խ�� �ڶ����жϱ�֤�������ַ�����С����
	while((*i)<len && ((strings[(*i)] <='9' && strings[(*i)] >= '0') || strings[(*i)] == '.'))
	{
		if(temp.integer != INF && strings[(*i)] == '.')
		{
			temp.oper = 1;
			return temp;
		}
		if(strings[(*i)] == '.')
		{
			//С����ǰ���
			temp.integer = ans;
			ans = 0;
			(*i)++;
			continue;
		}
		ans=ans*10 + strings[(*i)]-'0';
		(*i)++;
	}
	//����һ�£���ֹӰ����һλ�Ķ�ȡ
	(*i)--;
	if(temp.integer == INF)temp.integer = ans;
	else//С���Ĵ���ǰ��μӺ���
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
	//����������
	while((ch = getchar()) && ch != '\n')strings[len++] = ch;
	for(int i = 0;i < len;i++)
	{
		//�ո�����
		if(strings[i] == ' ')continue;
		//��������
		if(strings[i] >= '0' && strings[i] <= '9')
		{
			ElemType temp = readnum(&i,len,strings);
			//��Ϊ�������ڶ���������֣�����operΪ0,���oper��Ϊ0��˵�����ʽ�д�����error
			if(temp.oper)return ERROR;
			//ѹ��ջ
			pushStack(num,temp);
		}
		//���������
		else if(strings[i] == '+' || strings[i] == '-' || strings[i] == '*' || strings[i] == '/' || strings[i] == '(' || strings[i] == ')')
		{
			char ch  = strings[i];
			//�������β���Ҳ�������� ')' �����ش���
			//��Ϊ�����������β���ǲ��Ϸ���
			if(ch != ')' && i == len - 1)return ERROR;
			//ֱ��ѹ�������ջ
			if(ch == '(')
			{
				ElemType temp;
				temp.oper = ch;
				pushStack(oper,temp);
			}
			//�ѵ�'('ǰ��������������������ջ���ŵ���׺ջ����
			else if(ch == ')')
			{
				ElemType temp;
				//ջ��Ϊ��
				while(!isEmptyStack(oper))
				{
					popStack(oper,&temp);
					if(temp.oper == '(')break;
					pushStack(num,temp);
				}
				//�����Ϊ��ջ�׽�������()��ƥ��ɹ����ͷ��ش���
				if(isEmptyStack(oper) && temp.oper != '(')return ERROR;
			}
			else if(ch == '*' || ch == '/')//��ͬ���ȼ�
			{
				ElemType temp = ori;
				//��������ջΪ�գ�ֱ��ѹ��
				if(isEmptyStack(oper))
				{
					temp.oper = ch;
					pushStack(oper,temp);
				}
				//������ջ��������Ƚ����ȼ�
				else
				{
					while(!isEmptyStack(oper))
					{
						getTopStack(oper,&temp);
						//���ȼ���ջ��Ԫ�ظ�ʱ�˳�ѭ��
						if(temp.oper == '(' || temp.oper == '-' || temp.oper == '+')break;
						popStack(oper,&temp);
						pushStack(num,temp);
					}
					temp.oper = ch;
					pushStack(oper,temp);
				}
			}
			else if(ch == '-' || ch == '+')//��ͬ���ȼ�
			{
				int flag = 0;//����Ƿ���'-'�ź���ĵ�һ���������'-'���ȼ���
				//'-'����΢���ӣ��������Ҫ���Ǹ������ͽ���һ��ת��-a --> +(-a)

				//�������������
				if(ch == '-' && strings[i+1] >= '0' && strings[i+1] <= '9')
				{
					//����Ǹ��������,����Ҫת��
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
						int sign = 0;//���
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
					*	���'-'�ŵ���һ��������ļ���
					*	�����'-'����ߣ�˵���Ƚ��к�����������������Բ���-a -->+(-a)
					*	����3-4*2 �Ƚ���4*2
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
					//�����һ�����ȼ��ϸߣ�ֱ�Ӱ�'-'��ѹջ������ѭ��
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
					//�����һ�����ȼ�û�и߹�'-'��ת�����£�
					/*
						�Ȱ�'+'ѹ�������ջ
						�ٽ�����ѹ���׺���ʽջ
					*/
					//1.��'+'ѹ�������ջ
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
					//2.����ѹ���׺���ʽջ
					i++;//��������λ
					temp = readnum(&i,len,strings);
					if(temp.oper)
						return ERROR;
					else if(temp.integer != INF)
						temp.integer = -temp.integer;
					else
						temp.decimal = -temp.decimal;
					pushStack(num,temp);

				}
				else//������Ĳ������֣�ֱ�ӵ���'-'�����ѹջ
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
	//�����ջ���滹���������ȫ������
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
		//��ʼ��
		clearStack(&Postfixpression);
		clearStack(&operators);
		clearStack(&operators);
		memset(sum,0,sizeof(sum));
		right = 0;
		printf("\t��������׺���ʽ: ");
		if(!readin(&operators,&numbers))
			printf("\t���뺬�Ƿ��ַ�������������!\n");
		else
		{
			ElemType temp;
			int flag = 0;//�����û�г���
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
							printf("\t�����������0��\n");
							flag = 2;//�г����ҳ�0
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

			if(flag == 1)printf("\t������Ϊ��%.2f\n",sum[1]);
			else if(flag == 0) printf("\t������Ϊ��%d\n",(int)sum[1]);


		}
		printf("\t��Enter������...");
		getchar();
		system("cls");
	}
	destroyStack(&operators);
	destroyStack(&numbers);
	printf("\tлл����ʹ�ã�\n\tף��������죬лл���ֶ���ͷ(��������)��\n");
	getchar();
	return 0;
}
/*
	1. 12 + 13+(3-4*(3-1))//��4�����������ȸ��Ÿ߼� (�ѽ��)
	2.��ʼ��nuion�������⣺��ʼ��int(����) INF��char(����) 0;���ӵ�ĳ��ֵ����ȥ�����߸ı�ĳ����ֵ������һ��Ҳ���Ÿı�(�ѽ��)
	temp.int = 0;//Ȼ������һ��charҲ��1
	���㲻��ʼ����Ҳ���ܳ����⡣����
	//1*10*(-1 +2 -1+(-1.2*5))
	(3*3-3)
*/
