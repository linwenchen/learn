#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LQueue.h"
char init()
{
	char ch,temp;
	printf(

			"\n\t|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\t\n"
			"\t|a:��ʼ������                                             |\t\n"
			"\t|b:���                                                   |\t\n"
			"\t|c:����                                                   |\t\n"
			"\t|d:�����г���                                           |\t\n"
			"\t|e:�ж϶����Ƿ�Ϊ��                                       |\t\n"
			"\t|f:��ӡ�Ӷ�Ԫ��                                           |\t\n"
			"\t|g:��ն���                                               |\t\n"
			"\t|h:���ٶ���                                               |\t\n"
			"\t|i:�������                                               |\t\n"
			"\t|j:��ӡ����                                               |\t\n"
			"\t|q:�˳�����                                               |\t\n"
			"\t|_________________________________________________________|\t\n\n"
			);
	printf("\t������������еĲ���(ֻ�е�һ����ĸ��Ч)��");
	scanf(" %c",&ch);
	while((temp = getchar())!='\n')continue;
	//������
	while(ch!='q' && (ch < 'a' || ch > 'j'))
	{
		printf("\t��������: '%c' ����!���������룺",ch);
		scanf(" %c",&ch);
		while((temp = getchar())!='\n')continue;
	}
	 return ch;
}

Type ORI = {.type = 0};
//��xת��ΪС��������ֵ
double divnum(int x)
{
	double ret = x;
	//��֤����
	while((ret+0.00001) >= 1)
		ret/=10;
	return ret;
}
//����ָ�����͵Ĳ�ȷ������ָ��
void* readin(Type *temp)
{
	*temp = ORI;
	void *p;
	p = temp;
	//����Ƿ�ɹ���ȡ����
	int flag = 0;

	//�����û�����
	char ch;
	char s[MAX_STRINGS_LENGTH];
	int len = 0;
	while((ch = getchar()) && ch != '\n')s[len++] = ch;
	s[len] = '\0';

	//�����û�����
	int i = 0;
	while(s[i]!='\0')
	{
		if(s[i] == ' ')continue;
		if(s[i] == '\'')//�ַ�����
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
					//�����������ַ�
					flag = 0;
					break;
				}
			}
		}
		else if(s[i] == '\"')//�ַ�������
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
		else if(s[i] >= '0' && s[i] <= '9')//��������
		{
			int ans = 0;
			int flag1 = 0;//���������
			while(s[i] != '\0')
			{
				if(s[i] == '.')
				{
					//����������С����
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
			//���������Ǹ�����
			if(flag1 && flag)
			{
				temp->real_number += divnum(ans);
				temp->type = REAL_NUMBER;
			}
			//�����������
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
		printf("\t���������������������룺");
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
			printf("\t���ȳ�ʼ�����У�\n");
			printf("\t��Enter������...");
			getchar();
			system("cls");
			continue;
		}
		switch(ch){
			case 'a':{
				InitLQueue(Q);
				printf("\t��ʼ���ɹ���\n");
				flag = 1;//���ϱ��
				break;
			}
			case 'b':{
				printf("\t�ַ����'', �ַ������\"\"\n");
				printf("\t��������Ҫ��ӵ�Ԫ��:");
				Type *temp = (Type *)malloc(sizeof(Type));
				void *p = readin(temp);
				if(EnLQueue(Q,p))
					printf("\t��ӳɹ���\n");
				else
					printf("\t����������\n");
				break;
			}
			case 'c':{
				if(DeLQueue(Q))
					printf("\t���ӳɹ���\n");
				else
					printf("\t����Ϊ��,�������Ԫ�أ�\n");
				break;
			}
			case 'd':{
				printf("\t���г���Ϊ��%d!\n",LengthLQueue(Q));
				break;
			}
			case 'e':{
				if(IsEmptyLQueue(Q))
					printf("\t����Ϊ�գ�\n");
				else
					printf("\t���в�Ϊ�գ�\n");
				break;
			}
			case 'f':{

				Type *temp = (Type *)malloc(sizeof(Type));
				if(GetHeadLQueue(Q,temp))
					LPrint(temp);
				else
					printf("\t����Ϊ�գ�\n");
				break;
			}
			case 'g':{
				ClearLQueue(Q);
				printf("\t��������գ�\n");
				break;
			}
			case 'h':{
				DestoryLQueue(Q);
				printf("\t�����ѳɹ����٣�\n");
				//�����³�ʼ��
				flag = 0;
				break;
			}
			case 'i':{
				printf("\t�ַ����'', �ַ������\"\", ֹͣʱ������0\n");

				do{
					printf("\t������:");
					//Type temp;//����ִ����switch�ᱻ����
					Type *temp = (Type *)malloc(sizeof(Type));
					void *p = readin(temp);
					if(temp->type == INTEGER && temp->integer == 0)
						break;
					else
					{
						if(EnLQueue(Q,p))
							printf("\t��ӳɹ���\n");
						else
						{
							printf("\t����������\n");
							break;
						}

					}
				}while(1);
				break;
			}
			case 'j':{
                                if(TraverseLQueue(Q,LPrint));
				else printf("\t����Ϊ�գ�\n");
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

