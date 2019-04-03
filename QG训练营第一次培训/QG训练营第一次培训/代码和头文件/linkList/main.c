#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include "linkedList.h"
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
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main() {
	static sum = 0;
	char ch;
	int flag = 0;//��� 
	LinkedList L;
	LNode temp;
	ElemType item;
	while((ch = init()) && ch != 'q')
	{
		if(flag == 0 && ch != 'a')
		{
			printf("����δ�½������ȳ�ʼ����\n");
			continue;
			
		}
		if(sum == 0 && (ch == 'd' || ch == 'e' || ch == 'f' || ch == 'g' || ch == 'h' || ch == 'i' || ch == 'j' || ch == 'k'))
		{
			printf("��û����Ŀ,���Ȳ�����Ŀ\n");
			continue;
		}
		
		switch(ch)
		{
			
			
			case 'a':{
				if(InitList(&L))
				{
					printf("��ʼ���ɹ���\n");
					flag= 1;
					sum = 0;
				} 
				else printf("��ʼ��ʧ�ܣ��ڴ治�㣡\n");
				break;
			}
			case 'b':{
				DestroyList(&L); 
				printf("ɾ��ɹ���\n");
				sum = 0;
				flag = 0;
				break;
			}
			case 'c':{
				printf("��������Ҫ�����ֵ��");
				item = readint();
				
				if(Insert(&L,sum,item))
				{
					printf("����ɹ���\n");
					sum++; 
				} 
				else printf("����ʧ�ܣ��ڴ治�㣡\n");
				break;
			}
			case 'd': {
				
				printf("������Ҫɾ������Ŀ��");
				item = readint();
				if(Delete(&L,item,sum)) 
				{
					printf("ɾ���ɹ���\n");
					sum--;
				}
				else 
					printf("û�������Ŀ��\n");
				break;
			}
			case 'e':{
				TraverseList(L, out);
				break;
			}
			case 'f':{
				printf("��������Ҫ���ҵ���Ŀ��");
				item = readint(); 
				if(SearchList(L,item))printf("����\n");
				else printf("�����ڣ�\n");
				break;
			}
			case 'g':{
				if(ReverseList(&L))printf("��ת�ɹ���\n");
				else printf("��תʧ�ܣ�\n");
				break;
			}
			case 'h':{
				if(IsLoopList(L))printf("�л�\n");
				else printf("�޻�\n");
				break;
			}
			case 'i':{
				L = ReverseEvenList(&L);
				printf("�ѷ�ת��\n");
				break;
			}
			case 'j':{
				temp = *(FindMidNode(&L));
				printf("%d\n",temp.data);
				break;
			}
			case 'k':{
				int i;
				printf("������i��ֵ��");
				i = readint();
				printf("������Ҫ�����ֵ��");
				item = readint(); 
				if(i>sum || i<=0)
				{
					printf("��㲻���ڣ�\n");
					break;
				}
				LNode *temp = (LNode *)malloc(sizeof(LNode)); 
				if(temp)
				{
					temp->data = item;
					InsertList(LNodeI(&L,i), temp);
					printf("����ɹ�!\n");
					sum++;
					
				}
				else printf("����ʧ�ܣ��ڴ治�㣡\n");
				break;
			}
				
		}
		printf("��Enter������...\n");
		getchar();
		system("cls");
	}
	DestroyList(&L);
	printf("лл����ʹ�ã�\nף��������죬лл���ֶ���ͷ(��������)��\n");
	getchar();
	return 0;
}
