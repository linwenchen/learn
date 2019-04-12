#include <stdio.h>
#include <time.h>
#include <conio.h>
#include "Books_Management_System.h"

BookList InitSystem(void)//��ʼ������
{
	//���ļ�(����ģʽ)
	FILE *fpbook = fopen("book","ab+");
	FILE *fpbreader = fopen("borrow_reader","ab+");
	FILE *fpwqueue = fopen("waitingqueue","ab+");
	//�ж��ļ��Ƿ�������
	if(fpbook == NULL)
	{
		printf("Can't open \"book\"\n");
		getchar();
		exit(1);
	}
	else if(fpbreader == NULL)
	{
		printf("Can't open \"borrow_reader\"\n");
		getchar();
		exit(1);
	}
	else if(fpwqueue == NULL)
	{
		printf("Can't open \"waitingqueue\"\n");
		getchar();
		exit(1);
	}
	//����ļ��Ƿ�Ϊ��
	char ch = getc(fpbook);
	if(feof(fpbook))
	{
		fclose(fpbook);
		fclose(fpbreader);
		fclose(fpwqueue);
		return NULL;
	}
	else ungetc(ch,fpbook);//�˻�����
	//Ҫ���ص�ͷָ��͵�ǰָ��
	BookList head = NULL,current,p;
	//�������͵��ֽڳ���
	int len_book = sizeof(Book);
	int len_borrowreader = sizeof(BorrowReader);
	int len_waitqueue = sizeof(WaitingQueue);
	//�����ļ�
	//while(!feof(fpbook))//�ж��ļ�λ�ñ�־�Ƿ��ƶ����ļ�ĩβ
	while((ch = fgetc(fpbook)) && (feof(fpbook) == 0))
	{
		ungetc(ch,fpbook);
		p=(BookList)malloc(len_book);//���ڴ�����һ�οռ�
		fread(p,len_book,1,fpbook);//��fpbook��ָ����ļ��е����ݸ���p
		if(head == NULL)
		{
			current = head = p;
			if(current->breader != NULL)
			{
				BReader p1 = NULL;//��ǰ����ǰһ�����
				do
				{
					BReader temp=(BReader)malloc(len_borrowreader);//���ڴ�����һ�οռ�
					fread(temp,len_borrowreader,1,fpbreader);//��fpbreader��ָ����ļ��е����ݸ���temp
					if(p1 == NULL)
					{
						current->breader = p1 = temp;
					}
					else
					{
						p1->next = temp;
						p1 = temp;
					}
				}while(p1->next != NULL);
			}
			if(current->wqueue != NULL)
			{
				WQueue p1 = NULL;//��ǰ����ǰһ�����
				do
				{
					WQueue temp=(WQueue)malloc(len_waitqueue);//���ڴ�����һ�οռ�
					fread(temp,len_borrowreader,1,fpwqueue);//��fpwqueue��ָ����ļ��е����ݸ���temp
					if(p1 == NULL)
					{
						current->wqueue = p1 = temp;
					}
					else
					{
						p1->next = temp;
						p1 = temp;
					}
				}while(p1->next != NULL);
			}

		}
		else//��������
		{
			current->next = p;
			current = p;
			if(current->breader != NULL)
			{
				BReader p1 = NULL;//��ǰ����ǰһ�����
				do
				{
					BReader temp=(BReader)malloc(len_borrowreader);//���ڴ�����һ�οռ�
					fread(temp,len_borrowreader,1,fpbreader);//��fpbreader��ָ����ļ��е����ݸ���temp
					if(p1 == NULL)
					{
						current->breader = p1 = temp;
					}
					else
					{
						p1->next = temp;
						p1 = temp;
					}
				}while(p1->next != NULL);
			}
			if(current->wqueue != NULL)
			{
				WQueue p1 = NULL;//��ǰ����ǰһ�����
				do
				{
					WQueue temp=(WQueue)malloc(len_waitqueue);//���ڴ�����һ�οռ�
					fread(temp,len_borrowreader,1,fpwqueue);//��fpwqueue��ָ����ļ��е����ݸ���temp
					if(p1 == NULL)
					{
						current->wqueue = p1 = temp;
					}
					else
					{
						p1->next = temp;
						p1 = temp;
					}
				}while(p1->next != NULL);
			}
		}
	}
	//�ر��ļ�
	fclose(fpbook);
	fclose(fpbreader);
	fclose(fpwqueue);
	return head;

}
void over(BookList L)//�˳�����
{
	//���ļ�
	FILE *fpbook = fopen("book","wb");
	FILE *fpbreader = fopen("borrow_reader","wb");
	FILE *fpwqueue = fopen("waitingqueue","wb");
	//�ж��ļ��Ƿ�������
	if(fpbook == NULL)
	{
		printf("Can't open \"book\"\n");
		getchar();
		exit(1);
	}
	else if(fpbreader == NULL)
	{
		printf("Can't open \"borrow_reader\"\n");
		getchar();
		exit(1);
	}
	else if(fpwqueue == NULL)
	{
		printf("Can't open \"waitingqueue\"\n");
		getchar();
		exit(1);
	}
	//��ǰָ��
	BookList current;
	//�������͵��ֽڳ���
	int len_book = sizeof(Book);
	int len_borrowreader = sizeof(BorrowReader);
	int len_waitqueue = sizeof(WaitingQueue);
	//д���ļ�
	while(L)//����㲻Ϊ��
	{
		//��ǰ���
		current = L;
		//д���ļ�
		fwrite(current,len_book,1,fpbook);
		while(current->breader != NULL)
		{
			//��borrow_reader�ļ�д��
			fwrite(current->breader,len_borrowreader,1,fpbreader);
			//��һ��
			current->breader = current->breader->next;
		}
		while(current->wqueue != NULL)
		{
			//��waitingqueue�ļ�д��
			fwrite(current->wqueue ,len_waitqueue,1,fpwqueue);
			//��һ��
			current->wqueue  = current->wqueue ->next;

		}
		L = L->next;
	}
	//�ر��ļ�
	fclose(fpbook);
	fclose(fpbreader);
	fclose(fpwqueue);

}
void AddBook(BookList *L,Book e)//����鼮
{
	//L->head
	//���ͷָ��Ϊ��
	if(*L == NULL)
	{
		(*L) = (BookList)malloc(sizeof(Book));
		//��ʼʱ���ġ�ԤԼ����һ���鶼Ϊ��
		e.breader = NULL;
		e.wqueue = NULL;
		e.next = NULL;
		//��Ŀ����ִ�����ͬ
		e.left = e.sum;
		*(*L) = e;
		return;

	}
	BookList temp = *L;
	while(temp->next != NULL)temp = temp->next;
	temp->next = (BookList)malloc(sizeof(Book));
	//��ʼʱ���ġ�ԤԼ����һ���鶼Ϊ��
	e.breader = NULL;
	e.wqueue = NULL;
	e.next = NULL;
	//��Ŀ����ִ�����ͬ
	e.left = e.sum;
	*(temp->next) = e;

}
BookList FindBook(BookList L, uint bnumber)//Ѱ���鼮
{
	while(L)
	{
		if(L->bnumber == bnumber)return L;
		L = L->next;
	}
	return NULL;
}
Status DeleteBook(BookList *L,uint bnumber)//ɾ���鼮
{
	Book *pre = *L;
	Book *current = *L;
	while(current)
	{
		if(current->bnumber == bnumber)
		{
			//���Ҫɾ�����ǵ�һ�����
			if(pre == current)
			{
				//�ı�ͷָ���ֵ
				*L = current->next;
				free(current);
			}
			else
			{
				//��Ҫɾ������ǰ��������
				pre->next = current->next;
				free(current);
			}
			return success;
		}
		if(pre == current)
		{
			current = current->next;
			continue;
		}
		current = current->next;
		pre = pre->next;
	}
	//û���ҵ��Ȿ��
	return error;

}
void Printall(BookList L)//��ӡͼ����Ϣ
{
	toxy(0,3);
	printf("\t_____________________________________________________________________________________________");
	toxy(0,4);
	printf("\t|    ���    |          ����          |        ����        |   ���   |  �ѽ���  |  �ܿ��  |\n");
	toxy(0,5);
	printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\t_____________________________________________________________________________________________\n");
	while(L)
	{
		//��� ���� ����
		printf("\t|%-12d|%-24s|%-20s",L->bnumber,L->bname,L->bauthor);
		//ʣ�� ���� ����
		printf("|%-10d|%-10d|%-10d|\n",L->left,L->sum-L->left,L->sum);
		//��һ����
		L = L->next;
	}
	printf("\t---------------------------------------------------------------------------------------------\n");
}
void Printone(Book *e)//��ӡһ��ͼ�����ϸ��Ϣ
{

	toxy(0,3);
	printf("\t_____________________________________________________________________________________________");
	toxy(0,4);
	printf("\t|    ���    |          ����          |        ����        |   ���   |  �ѽ���  |  �ܿ��  |\n");
	toxy(0,5);
	printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\t_____________________________________________________________________________________________\n");
	//��� ���� ����
	printf("\t|%-12d|%-24s|%-20s",e->bnumber,e->bname,e->bauthor);
	//ʣ�� ���� ����
	printf("|%-10d|%-10d|%-10d|\n",e->left,e->sum-e->left,e->sum);
	printf("\t---------------------------------------------------------------------------------------------\n\n");
	printf("\t_____________________________________________________________________________________________\n");
	printf("\t|    ������ID  |        ����ʱ��        |        ����ʱ��         |  �Ƿ����� |\n");
	printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\t_____________________________________________________________________________________________\n");
	BReader temp = e->breader;
	while(temp)
	{
		printf("\t|%-14u",temp->ID);
		//������ʱ��ת��Ϊ����ʱ��
		struct tm *timeinfo;
		//����ʱ��
		timeinfo =  localtime(&(temp->Time));
		printf("| %02d:%02d:%02d  %d/%02d/%02d   |", \
			timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, timeinfo->tm_year+1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
		//����ʱ��
		timeinfo =  localtime(&(temp->duetime));
		printf(" %02d:%02d:%02d   %d/%02d/%02d   |", \
			timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, timeinfo->tm_year+1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
		//�Ѿ���ʱ
		if(temp->flag)
		{
			printf(" ��        |\n");
		}
		else
		{
			//������ʱ��Ƚ�
			time_t CurrentTime;
			time(&CurrentTime);
			//difftime(time_t t1, time_t t2)����(t1-t2)�����
			if(difftime(CurrentTime,temp->duetime) > 0)
			{
				temp->flag = 1;
				printf(" ��        |\n");
			}
			else
			{
				printf(" ��        |\n");
			}

		}
		temp = temp->next;
	}
	printf("\t---------------------------------------------------------------------------------------------\n");

}

Status BorrowBook(Book* e, uint ID)//����
{
	//���Ϊ0
	if(e->left <= 0)return error;
	else
	{
		e->left--;
		BorrowReader *temp;
		temp = (BReader)malloc(sizeof(BorrowReader));
		//����ʱ��͵���ʱ��
		time_t t;
		//����ʱ��
		time(&t);
		temp->Time = t;
		//���鿪ʼ�����ڵ�ʱ��
		temp->duetime = t + T_sec;
		//��ʼ��������Ա
		temp->flag = 0;
		temp->ID = ID;
		temp->next = NULL;
		//��������Ϊ0
		if(e->breader == NULL)
			e->breader = temp;
		else
		{
			BorrowReader *pre = e->breader;
			while(pre->next != NULL)
				pre = pre->next;
			pre->next = temp;

		}
	}
	return success;
}
Status ReturnBook(Book *e,uint ID)//����
{
	if(e == NULL)return error;
	BorrowReader *pre = e->breader;
	BorrowReader *current = e->breader;
	while(current)
	{
		if(current->ID == ID)
		{
			//���Ҫɾ�����ǵ�һ�����
			if(pre == current)
			{
				//�ı�ͷָ���ֵ
				e->breader = e->breader->next;
				free(current);
			}
			else
			{
				//��Ҫɾ������ǰ��������
				pre->next = current->next;
				free(current);
			}
			e->left += 1;//���飬����1
			if(e->wqueue)//�����Ԥ���ģ�ֱ�ӽ���
			{
				BorrowBook(e,e->wqueue->ID);
				e->wqueue = e->wqueue->next;
			}
			return success;
		}
		if(pre == current)
		{
			current = current->next;
			continue;
		}
		current = current->next;
		pre = pre->next;
	}
	//û���ҵ������
	return error;
}
Status ReserveBook(Book *e, uint ID)//Ԥ��
{
	if(e == NULL)return error;
	WaitingQueue *temp;
	temp = (WQueue)malloc(sizeof(WaitingQueue));
	temp->ID = ID;
	temp->next = NULL;
	//���ĳ�Ա��ֵ
	if(e->wqueue == NULL)e->wqueue = temp;
	else
	{
		WaitingQueue *pre = e->wqueue;
		while(pre->next != NULL)pre = pre->next;
		pre->next = temp;
	}
	return success;
}
