#include <stdio.h>
#include <stdlib.h>
#include "SqStack.h"
#define INF 10000000000

int readint()
{
	char ch;
	int flag = 0;//+-����
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
		printf("\t����\n\t��������ȷ��ֵ:");
		return readint();
	}
	if(flag)sum =-sum;
	return (int)(sum);
}
int main()
{
	SqStack s;
	char ch;
	int flag = 0;//���
	while((ch = init()) && ch != 'q')
	{
		if(!flag && ch != 'a')
		{
			printf("\t���ȳ�ʼ��ջ��\n");
			printf("\t��Enter������...");
			getchar();
			system("cls");
			continue;
		}
		switch(ch){
			case 'a':{
				printf("\t��������Ҫ��ʼ��ջ�ĳ���:");
				int size = readint();
				if(initStack(&s,size))
				{
					printf("\t��ʼ���ɹ���\n");
					flag = 1;//���ϱ��
				}
				else
					printf("\t��ʼ��ʧ�ܣ��ڴ治�㣡\n");
				break;
			}
			case 'b':{
				printf("\t��������Ҫѹ��ջ��Ԫ��:");
				int data = readint();
				if(pushStack(&s,data))
					printf("\t��ջ�ɹ���\n");
				else
					printf("\tջ������\n");
				break;
			}
			case 'c':{
				int data;
				if(popStack(&s,&data))
					printf("\t��ջԪ��Ϊ��%d\n",data);
				else
					printf("\tջΪ��,�������Ԫ�أ�\n");
				break;
			}
			case 'd':{
				int length;
				if(stackLength(&s,&length))
					printf("\tջ����Ϊ��%d!\n",length);
				else
					printf("\tջδ��ʼ����\n");
				break;
			}
			case 'e':{
				if(isEmptyStack(&s))
					printf("\tջΪ�գ�\n");
				else
					printf("\tջ��Ϊ�գ�\n");
				break;
			}
			case 'f':{
				int e;
				if(getTopStack(&s,&e))
					printf("\tջ��Ԫ��Ϊ��%d\n",e);
				else
					printf("\tջΪ��,�������Ԫ�أ�\n");
				break;
			}
			case 'g':{
				if(clearStack(&s))
					printf("\tջ����գ�\n");
				else
					printf("\tջΪ�գ���������\n");
				break;
			}
			case 'h':{
				if(destroyStack(&s))
				{
					printf("\tջ�ѳɹ����٣�\n");
					//�����³�ʼ��
					flag = 0;
				}
				break;
			}
			case 'i':{
				printf("\t���ٶ���,ֹͣʱ������0\n");
				int temp;
				do{
					printf("\t������:");
					temp = readint();
					if(temp)
					{
						if(!pushStack(&s,temp))
						{
							printf("\tջ����!\n");
							break;
						}
					}
					else break;
				}while(1);
				break;
			}
		};
		printf("\t��Enter������...");
		getchar();
		system("cls");
	}
	printf("\tлл����ʹ�ã�\n\tף��������죬лл���ֶ���ͷ(��������)��\n");
	getchar();
	return 0;
}
