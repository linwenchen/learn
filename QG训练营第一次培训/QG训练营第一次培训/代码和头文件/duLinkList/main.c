#include "../head/duLinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#define INF 10000000000
int readint()
{
	char ch;
	int flag = 0;//+-符号 
	long long sum = 0;
	int test = 0;
	while((ch = getchar()) && ch!='\n')
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
		printf("错误！\n请输入正确的值:");
		return readint();
	}
	if(flag)sum =-sum;
	return (int)(sum);
} 
int main()
{
	static int sum = 0;
	char ch;
	int flag = 0;//标记
	DuLinkedList L;
	DuLNode *temp;
	ElemType item;
	while((ch = init()) && ch != 'q'){
		if(flag == 0 && ch != 'a')
		{
			printf("链表还未新建！请先初始化！\n");
			continue;
			
		}
		if(sum == 0 && (ch == 'c' || ch == 'd' || ch == 'h' || ch == 'f' || ch == 'g'))
		{
			printf("还没有项目,请先插入项目\n");
			continue;
		}
		switch(ch){
			case 'a':{
				if(InitList_DuL(&L))
				{
					printf("初始化成功！\n");
					flag= 1;
				} 
				else printf("初始化失败！内存不足！\n");
				break;
			}
			case 'b':{
				DestroyList_DuL(&L); 
				printf("删表成功！\n");
				sum = 0;
				flag = 0;
				break;
			}
			case 'c':{
				int i;
				printf("请输入i：");
				i = readint();
				printf("请输入要插入的值：");
				item = readint(); 
				
				if(Insert(&L,sum,item,'l'))
				{
					printf("插入成功！\n");
					sum++; 
				} 
				else printf("插入失败！内存不足！\n");
				break;
			}
			
			case 'd':{
				int i;
				printf("请输入i：");
				i = readint();
				printf("请输入要插入的值：");
				item = readint(); 
				
				if(Insert(&L,sum,item,'r'))
				{
					printf("插入成功！\n");
					sum++; 
				} 
				else printf("插入失败！内存不足！\n");
				break;
			}
			case 'e':{
				printf("输入要插入的值：");
	 			item = readint();
	 			if(Insert(&L,sum,item,'r'))
	 			{
	 				printf("插入成功！\n");
	 				sum++;
				 }
	 			else printf("插入失败！内存不足！\n");

				break;
			}
			case 'f': {
				int unsed;
				printf("请输入要删除的项目值：");
				item = readint();
				if(FindItem(L,item)) 
				{
					DeleteList_DuL(FindItem(L,item), &unsed);
					printf("删除成功！\n");
					sum--;
				}
				else 
					printf("没有这个项目！\n");
				break;
			}
			case 'g':{
				TraverseList_DuL(L,out);
				break;
			}
			case 'h':{
				printf("请输入您要查找的项目：");
				item = readint(); 
				if(FindItem(L,item) != NULL)printf("存在\n");
				else printf("不存在！\n");
				break;
			}
				
		}
		printf("按任意键继续...\n");
		getchar();
		system("cls");
	}	
	DestroyList_DuL(&L);
	printf("谢谢您的使用！\n祝您生活愉快，谢谢！手动狗头(～￣▽￣)～\n");
	getchar();
	return 0;
}
