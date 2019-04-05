#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LQueue.h"
char init()
{
	char ch,temp;
	printf(

			"\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\t\n"
			"\t|a:初始化队列                                             |\t\n"
			"\t|b:入队                                                   |\t\n"
			"\t|c:出队                                                   |\t\n"
			"\t|d:检测队列长度                                           |\t\n"
			"\t|e:判断队列是否为空                                       |\t\n"
			"\t|f:打印队顶元素                                           |\t\n"
			"\t|g:清空队列                                               |\t\n"
			"\t|h:销毁队列                                               |\t\n"
			"\t|i:快速入队                                               |\t\n"
			"\t|j:打印队列                                               |\t\n"
			"\t|q:退出程序                                               |\t\n"
			"\t|_________________________________________________________|\t\n\n"
			);
	printf("\t请输入你想进行的操作(只有第一个字母有效)：");
	scanf(" %c",&ch);
	while((temp = getchar())!='\n')continue;
	//输入检测
	while(ch!='q' && (ch < 'a' || ch > 'j'))
	{
		printf("\t您的输入: '%c' 有误!请重新输入：",ch);
		scanf(" %c",&ch);
		while((temp = getchar())!='\n')continue;
	}
	 return ch;
}

Type ORI = {.type = 0};
//将x转化为小数点后面的值
double divnum(int x)
{
	double ret = x;
	//保证精度
	while((ret+0.00001) >= 1)
		ret/=10;
	return ret;
}
//返回指向类型的不确定类型指针
void* readin(Type *temp)
{
	*temp = ORI;
	void *p;
	p = temp;
	//标记是否成功读取输入
	int flag = 0;

	//读入用户输入
	char ch;
	char s[MAX_STRINGS_LENGTH];
	int len = 0;
	while((ch = getchar()) && ch != '\n')s[len++] = ch;
	s[len] = '\0';

	//处理用户输入
	int i = 0;
	while(s[i]!='\0')
	{
		if(s[i] == ' ')continue;
		if(s[i] == '\'')//字符类型
		{
			i++;
			while(s[i] != '\'' && s[i] != '\0')
			{
				if(!flag)
				{
					flag = 1;
					temp->type = CHARACTER;
					temp->character = s[i];
					i++;
				}
				else
				{
					//两个及以上字符
					flag = 0;
					break;
				}
			}
		}
		else if(s[i] == '\"')//字符串类型
		{
			i++;
			int left = i;
			while(s[i] != '\"' && s[i] != '\0')
				i++;
			if(s[i] == '\"')
			{
				strncpy(temp->strings,s+left,i-left);
				temp->strings[i-left] = '\0';
				temp->type = STRING;
				flag = 1;
			}
		}
		else if(s[i] >= '0' && s[i] <= '9')//常数类型
		{
			int ans = 0;
			int flag1 = 0;//浮点数标记
			while(s[i] != '\0')
			{
				if(s[i] == '.')
				{
					//两个及以上小数点
					if(flag1)
					{
						flag = 0;
						break;
					}
					temp->real_number = ans;
					ans = 0;
					flag1 = 1;
					i++;
					continue;
				}
				else if(s[i] >= '0' && s[i] <= '9')
				{
					ans = ans*10 + s[i]-'0';
					i++;
					flag = 1;
				}
				else
				{
					flag = 0;
					break;
				}
			}
			//如果输入的是浮点数
			if(flag1 && flag)
			{
				temp->real_number += divnum(ans);
				temp->type = REAL_NUMBER;
			}
			//输入的是整数
			else if(flag)
			{
				temp->integer = ans;
				temp->type = INTEGER;
			}
		}
		break;
	}
	if(flag)return p;
	else
	{
		printf("\t您的输入有误！请重新输入：");
		return readin(temp);
	}

}

int main()
{
	LQueue *Q;
	Q = (LQueue *)malloc(sizeof(LQueue));
	Q->front = NULL;
	Q->rear = NULL;
	Q->length = 0;
	char ch;
	int flag = 0;
	while((ch = init()) && ch != 'q')
	{
		if(!flag && ch != 'a')
		{
			printf("\t请先初始化队列！\n");
			printf("\t按Enter键继续...");
			getchar();
			system("cls");
			continue;
		}
		switch(ch){
			case 'a':{
				InitLQueue(Q);
				printf("\t初始化成功！\n");
				flag = 1;//打上标记
				break;
			}
			case 'b':{
				printf("\t字符请加'', 字符串请加\"\"\n");
				printf("\t请输入需要入队的元素:");
				Type *temp = (Type *)malloc(sizeof(Type));
				void *p = readin(temp);
				if(EnLQueue(Q,p))
					printf("\t入队成功！\n");
				else
					printf("\t队列已满！\n");
				break;
			}
			case 'c':{
				if(DeLQueue(Q))
					printf("\t出队成功！\n");
				else
					printf("\t队列为空,请先添加元素！\n");
				break;
			}
			case 'd':{
				printf("\t队列长度为：%d!\n",LengthLQueue(Q));
				break;
			}
			case 'e':{
				if(IsEmptyLQueue(Q))
					printf("\t队列为空！\n");
				else
					printf("\t队列不为空！\n");
				break;
			}
			case 'f':{

				Type *temp = (Type *)malloc(sizeof(Type));
				if(GetHeadLQueue(Q,temp))
					LPrint(temp);
				else
					printf("\t队列为空！\n");
				break;
			}
			case 'g':{
				ClearLQueue(Q);
				printf("\t队列已清空！\n");
				break;
			}
			case 'h':{
				DestoryLQueue(Q);
				printf("\t队列已成功销毁！\n");
				//需重新初始化
				flag = 0;
				break;
			}
			case 'i':{
				printf("\t字符请加'', 字符串请加\"\", 停止时请输入0\n");

				do{
					printf("\t请输入:");
					//Type temp;//错误，执行完switch会被回收
					Type *temp = (Type *)malloc(sizeof(Type));
					void *p = readin(temp);
					if(temp->type == INTEGER && temp->integer == 0)
						break;
					else
					{
						if(EnLQueue(Q,p))
							printf("\t入队成功！\n");
						else
						{
							printf("\t队列已满！\n");
							break;
						}

					}
				}while(1);
				break;
			}
			case 'j':{
                                if(TraverseLQueue(Q,LPrint));
				else printf("\t队列为空！\n");
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

