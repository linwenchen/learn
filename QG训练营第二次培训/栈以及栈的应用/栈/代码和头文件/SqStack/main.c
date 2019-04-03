#include <stdio.h>
#include <stdlib.h>
#include "SqStack.h"
#define INF 10000000000

int readint()
{
	char ch;
	int flag = 0;//+-符号
	long long sum = 0;
	int test = 0;
	while((ch = getchar()) && ch != '\n')
	{
		if(flag == 0 && ch == '-'){
			flag = 1;
			continue;
		}
		if(ch<'0' || ch>'9' || sum > 2147483647 || sum <-2147483647)
		{
			while((ch = getchar())!='\n')continue;
			sum = INF;
			break;
		}
		sum=sum*10+ch-'0';
		if(!test)test = 1;
	}

	if(sum == INF || test == 0)
	{
		printf("\t错误！\n\t请输入正确的值:");
		return readint();
	}
	if(flag)sum =-sum;
	return (int)(sum);
}
int main()
{
	SqStack s;
	char ch;
	int flag = 0;//标记
	while((ch = init()) && ch != 'q')
	{
		if(!flag && ch != 'a')
		{
			printf("\t请先初始化栈！\n");
			printf("\t按Enter键继续...");
			getchar();
			system("cls");
			continue;
		}
		switch(ch){
			case 'a':{
				printf("\t请输入需要初始化栈的长度:");
				int size = readint();
				if(initStack(&s,size))
				{
					printf("\t初始化成功！\n");
					flag = 1;//打上标记
				}
				else
					printf("\t初始化失败！内存不足！\n");
				break;
			}
			case 'b':{
				printf("\t请输入需要压入栈的元素:");
				int data = readint();
				if(pushStack(&s,data))
					printf("\t入栈成功！\n");
				else
					printf("\t栈已满！\n");
				break;
			}
			case 'c':{
				int data;
				if(popStack(&s,&data))
					printf("\t出栈元素为：%d\n",data);
				else
					printf("\t栈为空,请先添加元素！\n");
				break;
			}
			case 'd':{
				int length;
				if(stackLength(&s,&length))
					printf("\t栈长度为：%d!\n",length);
				else
					printf("\t栈未初始化！\n");
				break;
			}
			case 'e':{
				if(isEmptyStack(&s))
					printf("\t栈为空！\n");
				else
					printf("\t栈不为空！\n");
				break;
			}
			case 'f':{
				int e;
				if(getTopStack(&s,&e))
					printf("\t栈顶元素为：%d\n",e);
				else
					printf("\t栈为空,请先添加元素！\n");
				break;
			}
			case 'g':{
				if(clearStack(&s))
					printf("\t栈已清空！\n");
				else
					printf("\t栈为空，无需清理！\n");
				break;
			}
			case 'h':{
				if(destroyStack(&s))
				{
					printf("\t栈已成功销毁！\n");
					//需重新初始化
					flag = 0;
				}
				break;
			}
			case 'i':{
				printf("\t快速读入,停止时请输入0\n");
				int temp;
				do{
					printf("\t请输入:");
					temp = readint();
					if(temp)
					{
						if(!pushStack(&s,temp))
						{
							printf("\t栈已满!\n");
							break;
						}
					}
					else break;
				}while(1);
				break;
			}
		};
		printf("\t按Enter键继续...");
		getchar();
		system("cls");
	}
	printf("\t谢谢您的使用！\n\t祝您生活愉快，谢谢！手动狗头(～￣▽￣)～\n");
	getchar();
	return 0;
}
