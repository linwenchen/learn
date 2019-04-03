#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include "linkedList.h"
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
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	static sum = 0;
	char ch;
	int flag = 0;//标记 
	LinkedList L;
	LNode temp;
	ElemType item;
	while((ch = init()) && ch != 'q')
	{
		if(flag == 0 && ch != 'a')
		{
			printf("链表还未新建！请先初始化！\n");
			continue;
			
		}
		if(sum == 0 && (ch == 'd' || ch == 'e' || ch == 'f' || ch == 'g' || ch == 'h' || ch == 'i' || ch == 'j' || ch == 'k'))
		{
			printf("还没有项目,请先插入项目\n");
			continue;
		}
		
		switch(ch)
		{
			
			
			case 'a':{
				if(InitList(&L))
				{
					printf("初始化成功！\n");
					flag= 1;
					sum = 0;
				} 
				else printf("初始化失败！内存不足！\n");
				break;
			}
			case 'b':{
				DestroyList(&L); 
				printf("删表成功！\n");
				sum = 0;
				flag = 0;
				break;
			}
			case 'c':{
				printf("请输入您要插入的值：");
				item = readint();
				
				if(Insert(&L,sum,item))
				{
					printf("插入成功！\n");
					sum++; 
				} 
				else printf("插入失败！内存不足！\n");
				break;
			}
			case 'd': {
				
				printf("请输入要删除的项目：");
				item = readint();
				if(Delete(&L,item,sum)) 
				{
					printf("删除成功！\n");
					sum--;
				}
				else 
					printf("没有这个项目！\n");
				break;
			}
			case 'e':{
				TraverseList(L, out);
				break;
			}
			case 'f':{
				printf("请输入您要查找的项目：");
				item = readint(); 
				if(SearchList(L,item))printf("存在\n");
				else printf("不存在！\n");
				break;
			}
			case 'g':{
				if(ReverseList(&L))printf("翻转成功！\n");
				else printf("翻转失败！\n");
				break;
			}
			case 'h':{
				if(IsLoopList(L))printf("有环\n");
				else printf("无环\n");
				break;
			}
			case 'i':{
				L = ReverseEvenList(&L);
				printf("已翻转！\n");
				break;
			}
			case 'j':{
				temp = *(FindMidNode(&L));
				printf("%d\n",temp.data);
				break;
			}
			case 'k':{
				int i;
				printf("请输入i的值：");
				i = readint();
				printf("请输入要插入的值：");
				item = readint(); 
				if(i>sum || i<=0)
				{
					printf("结点不存在！\n");
					break;
				}
				LNode *temp = (LNode *)malloc(sizeof(LNode)); 
				if(temp)
				{
					temp->data = item;
					InsertList(LNodeI(&L,i), temp);
					printf("插入成功!\n");
					sum++;
					
				}
				else printf("插入失败！内存不足！\n");
				break;
			}
				
		}
		printf("按Enter键继续...\n");
		getchar();
		system("cls");
	}
	DestroyList(&L);
	printf("谢谢您的使用！\n祝您生活愉快，谢谢！手动狗头(～￣▽￣)～\n");
	getchar();
	return 0;
}
