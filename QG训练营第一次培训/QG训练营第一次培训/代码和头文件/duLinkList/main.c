#include "../head/duLinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#define INF 10000000000
int readint()
{
	char ch;
	int flag = 0;//+-���� 
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
		printf("����\n��������ȷ��ֵ:");
		return readint();
	}
	if(flag)sum =-sum;
	return (int)(sum);
} 
int main()
{
	static int sum = 0;
	char ch;
	int flag = 0;//���
	DuLinkedList L;
	DuLNode *temp;
	ElemType item;
	while((ch = init()) && ch != 'q'){
		if(flag == 0 && ch != 'a')
		{
			printf("����δ�½������ȳ�ʼ����\n");
			continue;
			
		}
		if(sum == 0 && (ch == 'c' || ch == 'd' || ch == 'h' || ch == 'f' || ch == 'g'))
		{
			printf("��û����Ŀ,���Ȳ�����Ŀ\n");
			continue;
		}
		switch(ch){
			case 'a':{
				if(InitList_DuL(&L))
				{
					printf("��ʼ���ɹ���\n");
					flag= 1;
				} 
				else printf("��ʼ��ʧ�ܣ��ڴ治�㣡\n");
				break;
			}
			case 'b':{
				DestroyList_DuL(&L); 
				printf("ɾ��ɹ���\n");
				sum = 0;
				flag = 0;
				break;
			}
			case 'c':{
				int i;
				printf("������i��");
				i = readint();
				printf("������Ҫ�����ֵ��");
				item = readint(); 
				
				if(Insert(&L,sum,item,'l'))
				{
					printf("����ɹ���\n");
					sum++; 
				} 
				else printf("����ʧ�ܣ��ڴ治�㣡\n");
				break;
			}
			
			case 'd':{
				int i;
				printf("������i��");
				i = readint();
				printf("������Ҫ�����ֵ��");
				item = readint(); 
				
				if(Insert(&L,sum,item,'r'))
				{
					printf("����ɹ���\n");
					sum++; 
				} 
				else printf("����ʧ�ܣ��ڴ治�㣡\n");
				break;
			}
			case 'e':{
				printf("����Ҫ�����ֵ��");
	 			item = readint();
	 			if(Insert(&L,sum,item,'r'))
	 			{
	 				printf("����ɹ���\n");
	 				sum++;
				 }
	 			else printf("����ʧ�ܣ��ڴ治�㣡\n");

				break;
			}
			case 'f': {
				int unsed;
				printf("������Ҫɾ������Ŀֵ��");
				item = readint();
				if(FindItem(L,item)) 
				{
					DeleteList_DuL(FindItem(L,item), &unsed);
					printf("ɾ���ɹ���\n");
					sum--;
				}
				else 
					printf("û�������Ŀ��\n");
				break;
			}
			case 'g':{
				TraverseList_DuL(L,out);
				break;
			}
			case 'h':{
				printf("��������Ҫ���ҵ���Ŀ��");
				item = readint(); 
				if(FindItem(L,item) != NULL)printf("����\n");
				else printf("�����ڣ�\n");
				break;
			}
				
		}
		printf("�����������...\n");
		getchar();
		system("cls");
	}	
	DestroyList_DuL(&L);
	printf("лл����ʹ�ã�\nף��������죬лл���ֶ���ͷ(��������)��\n");
	getchar();
	return 0;
}
