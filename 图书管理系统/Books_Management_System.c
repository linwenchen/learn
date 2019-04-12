#include <stdio.h>
#include <time.h>
#include <conio.h>
#include "Books_Management_System.h"

BookList InitSystem(void)//初始化程序
{
	//打开文件(读入模式)
	FILE *fpbook = fopen("book","ab+");
	FILE *fpbreader = fopen("borrow_reader","ab+");
	FILE *fpwqueue = fopen("waitingqueue","ab+");
	//判断文件是否正常打开
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
	//检查文件是否为空
	char ch = getc(fpbook);
	if(feof(fpbook))
	{
		fclose(fpbook);
		fclose(fpbreader);
		fclose(fpwqueue);
		return NULL;
	}
	else ungetc(ch,fpbook);//退回流中
	//要返回的头指针和当前指针
	BookList head = NULL,current,p;
	//三种类型的字节长度
	int len_book = sizeof(Book);
	int len_borrowreader = sizeof(BorrowReader);
	int len_waitqueue = sizeof(WaitingQueue);
	//读入文件
	//while(!feof(fpbook))//判断文件位置标志是否移动到文件末尾
	while((ch = fgetc(fpbook)) && (feof(fpbook) == 0))
	{
		ungetc(ch,fpbook);
		p=(BookList)malloc(len_book);//向内存申请一段空间
		fread(p,len_book,1,fpbook);//将fpbook所指向的文件中的内容赋给p
		if(head == NULL)
		{
			current = head = p;
			if(current->breader != NULL)
			{
				BReader p1 = NULL;//当前结点的前一个结点
				do
				{
					BReader temp=(BReader)malloc(len_borrowreader);//向内存申请一段空间
					fread(temp,len_borrowreader,1,fpbreader);//将fpbreader所指向的文件中的内容赋给temp
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
				WQueue p1 = NULL;//当前结点的前一个结点
				do
				{
					WQueue temp=(WQueue)malloc(len_waitqueue);//向内存申请一段空间
					fread(temp,len_borrowreader,1,fpwqueue);//将fpwqueue所指向的文件中的内容赋给temp
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
		else//创建链表
		{
			current->next = p;
			current = p;
			if(current->breader != NULL)
			{
				BReader p1 = NULL;//当前结点的前一个结点
				do
				{
					BReader temp=(BReader)malloc(len_borrowreader);//向内存申请一段空间
					fread(temp,len_borrowreader,1,fpbreader);//将fpbreader所指向的文件中的内容赋给temp
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
				WQueue p1 = NULL;//当前结点的前一个结点
				do
				{
					WQueue temp=(WQueue)malloc(len_waitqueue);//向内存申请一段空间
					fread(temp,len_borrowreader,1,fpwqueue);//将fpwqueue所指向的文件中的内容赋给temp
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
	//关闭文件
	fclose(fpbook);
	fclose(fpbreader);
	fclose(fpwqueue);
	return head;

}
void over(BookList L)//退出程序
{
	//打开文件
	FILE *fpbook = fopen("book","wb");
	FILE *fpbreader = fopen("borrow_reader","wb");
	FILE *fpwqueue = fopen("waitingqueue","wb");
	//判断文件是否正常打开
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
	//当前指针
	BookList current;
	//三种类型的字节长度
	int len_book = sizeof(Book);
	int len_borrowreader = sizeof(BorrowReader);
	int len_waitqueue = sizeof(WaitingQueue);
	//写入文件
	while(L)//链结点不为空
	{
		//当前结点
		current = L;
		//写入文件
		fwrite(current,len_book,1,fpbook);
		while(current->breader != NULL)
		{
			//往borrow_reader文件写入
			fwrite(current->breader,len_borrowreader,1,fpbreader);
			//下一个
			current->breader = current->breader->next;
		}
		while(current->wqueue != NULL)
		{
			//往waitingqueue文件写入
			fwrite(current->wqueue ,len_waitqueue,1,fpwqueue);
			//下一个
			current->wqueue  = current->wqueue ->next;

		}
		L = L->next;
	}
	//关闭文件
	fclose(fpbook);
	fclose(fpbreader);
	fclose(fpwqueue);

}
void AddBook(BookList *L,Book e)//添加书籍
{
	//L->head
	//如果头指针为空
	if(*L == NULL)
	{
		(*L) = (BookList)malloc(sizeof(Book));
		//开始时借阅、预约和下一本书都为空
		e.breader = NULL;
		e.wqueue = NULL;
		e.next = NULL;
		//书的库存和现存量相同
		e.left = e.sum;
		*(*L) = e;
		return;

	}
	BookList temp = *L;
	while(temp->next != NULL)temp = temp->next;
	temp->next = (BookList)malloc(sizeof(Book));
	//开始时借阅、预约和下一本书都为空
	e.breader = NULL;
	e.wqueue = NULL;
	e.next = NULL;
	//书的库存和现存量相同
	e.left = e.sum;
	*(temp->next) = e;

}
BookList FindBook(BookList L, uint bnumber)//寻找书籍
{
	while(L)
	{
		if(L->bnumber == bnumber)return L;
		L = L->next;
	}
	return NULL;
}
Status DeleteBook(BookList *L,uint bnumber)//删除书籍
{
	Book *pre = *L;
	Book *current = *L;
	while(current)
	{
		if(current->bnumber == bnumber)
		{
			//如果要删除的是第一个结点
			if(pre == current)
			{
				//改变头指针的值
				*L = current->next;
				free(current);
			}
			else
			{
				//将要删除结点的前后结点连接
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
	//没有找到这本书
	return error;

}
void Printall(BookList L)//打印图书信息
{
	toxy(0,3);
	printf("\t_____________________________________________________________________________________________");
	toxy(0,4);
	printf("\t|    书号    |          书名          |        作者        |   库存   |  已借阅  |  总库存  |\n");
	toxy(0,5);
	printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\t_____________________________________________________________________________________________\n");
	while(L)
	{
		//书号 书名 作者
		printf("\t|%-12d|%-24s|%-20s",L->bnumber,L->bname,L->bauthor);
		//剩余 借阅 总量
		printf("|%-10d|%-10d|%-10d|\n",L->left,L->sum-L->left,L->sum);
		//下一本书
		L = L->next;
	}
	printf("\t---------------------------------------------------------------------------------------------\n");
}
void Printone(Book *e)//打印一个图书的详细信息
{

	toxy(0,3);
	printf("\t_____________________________________________________________________________________________");
	toxy(0,4);
	printf("\t|    书号    |          书名          |        作者        |   库存   |  已借阅  |  总库存  |\n");
	toxy(0,5);
	printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\t_____________________________________________________________________________________________\n");
	//书号 书名 作者
	printf("\t|%-12d|%-24s|%-20s",e->bnumber,e->bname,e->bauthor);
	//剩余 借阅 总量
	printf("|%-10d|%-10d|%-10d|\n",e->left,e->sum-e->left,e->sum);
	printf("\t---------------------------------------------------------------------------------------------\n\n");
	printf("\t_____________________________________________________________________________________________\n");
	printf("\t|    借阅者ID  |        借阅时间        |        到期时间         |  是否逾期 |\n");
	printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\t_____________________________________________________________________________________________\n");
	BReader temp = e->breader;
	while(temp)
	{
		printf("\t|%-14u",temp->ID);
		//将日历时间转化为本地时间
		struct tm *timeinfo;
		//借阅时间
		timeinfo =  localtime(&(temp->Time));
		printf("| %02d:%02d:%02d  %d/%02d/%02d   |", \
			timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, timeinfo->tm_year+1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
		//到期时间
		timeinfo =  localtime(&(temp->duetime));
		printf(" %02d:%02d:%02d   %d/%02d/%02d   |", \
			timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, timeinfo->tm_year+1900, timeinfo->tm_mon + 1, timeinfo->tm_mday);
		//已经逾时
		if(temp->flag)
		{
			printf(" 是        |\n");
		}
		else
		{
			//和现在时间比较
			time_t CurrentTime;
			time(&CurrentTime);
			//difftime(time_t t1, time_t t2)返回(t1-t2)的秒差
			if(difftime(CurrentTime,temp->duetime) > 0)
			{
				temp->flag = 1;
				printf(" 是        |\n");
			}
			else
			{
				printf(" 否        |\n");
			}

		}
		temp = temp->next;
	}
	printf("\t---------------------------------------------------------------------------------------------\n");

}

Status BorrowBook(Book* e, uint ID)//借书
{
	//库存为0
	if(e->left <= 0)return error;
	else
	{
		e->left--;
		BorrowReader *temp;
		temp = (BReader)malloc(sizeof(BorrowReader));
		//借阅时间和到期时间
		time_t t;
		//借书时间
		time(&t);
		temp->Time = t;
		//借书开始到到期的时间
		temp->duetime = t + T_sec;
		//初始化其他成员
		temp->flag = 0;
		temp->ID = ID;
		temp->next = NULL;
		//借书人数为0
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
Status ReturnBook(Book *e,uint ID)//还书
{
	if(e == NULL)return error;
	BorrowReader *pre = e->breader;
	BorrowReader *current = e->breader;
	while(current)
	{
		if(current->ID == ID)
		{
			//如果要删除的是第一个结点
			if(pre == current)
			{
				//改变头指针的值
				e->breader = e->breader->next;
				free(current);
			}
			else
			{
				//将要删除结点的前后结点连接
				pre->next = current->next;
				free(current);
			}
			e->left += 1;//还书，库存加1
			if(e->wqueue)//如果有预定的，直接借书
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
	//没有找到这个人
	return error;
}
Status ReserveBook(Book *e, uint ID)//预定
{
	if(e == NULL)return error;
	WaitingQueue *temp;
	temp = (WQueue)malloc(sizeof(WaitingQueue));
	temp->ID = ID;
	temp->next = NULL;
	//更改成员的值
	if(e->wqueue == NULL)e->wqueue = temp;
	else
	{
		WaitingQueue *pre = e->wqueue;
		while(pre->next != NULL)pre = pre->next;
		pre->next = temp;
	}
	return success;
}
