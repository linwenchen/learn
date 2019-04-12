/***************************************************************************************
 *	File Name				:	Books_Management_System.h
 *	CopyRight				:	Wenchen Lin
 *	Create Data				:	2019.4.8
 *	Author/Corportation		:	Wenchen Lin
 *	Abstract Description	:	this will be used for manageing the books in the library
 *	SYSTEM					:   win10
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *
 *
 ***************************************************************************************/


/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef BOOKS_MANAGEMENT_SYSTEM_H_INCLUDED
#define BOOKS_MANAGEMENT_SYSTEM_H_INCLUDED

/**************************************************************
*	Include File Section
**************************************************************/
#include <time.h>//调用时间
#include <stdio.h>//记得删除
#include <stdlib.h>//记得删除
#include <windows.h>

/**************************************************************
*	Macro Define Section
**************************************************************/
#define LENGTH 100			//书名字以及作者名字长度
#define T 90				//借还期限(天)
#define T_sec (T * 24 *60 * 60)		//借还期限(秒)
typedef unsigned int uint;
/**************************************************************
*	Struct Define Section
**************************************************************/

//已借书队列
typedef struct BorrowReader{
	uint ID;	//图书证号
	time_t Time;	//借阅时间
	time_t duetime; //到期时间
	int flag;	//是否逾期
	struct BorrowReader *next;
}BorrowReader,*BReader;

//排队预定的队列
typedef struct WaitingQueue{
	uint ID;	//等待者的图书证号
	struct WaitingQueue *next;
}WaitingQueue,*WQueue;

//基本数据类型Book
typedef struct BOOK{
	uint bnumber;		//书号
	char bname[LENGTH];	//书名
	char bauthor[LENGTH];	//书的作者
	uint sum;		//书的总数
	uint left;		//书的剩余库存

	BReader breader;	//借书链队列
	WQueue wqueue;		//预订链队列

	struct BOOK *next;	//下一本书
}Book,*BookList;

typedef struct Admin{
	char password[LENGTH];
}Admin;
//返回类型
typedef enum Status
{
	error = 0,
	success = 1,
} Status;
/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name		:
 *	@description:
 *	@param		:
 *	@return		:
 *  @notice		:
 */

BookList InitSystem(void);//初始化程序
void over(BookList L);//退出程序
void AddBook(BookList *L,Book e);//添加书籍
BookList FindBook(BookList L, uint bnumber);//寻找书籍
Status DeleteBook(BookList *L,uint bnumber);//删除书籍
void Printall(BookList L);//打印图书信息
void Printone(Book *e);//打印一个图书的详细信息
Status BorrowBook(Book* e, uint ID);//借书
Status ReturnBook(Book *e,uint ID);//还书
Status ReserveBook(Book *e, uint ID);//预定

void AdminLogin(BookList *L);
void MemberLogin(BookList *L);
void MenuMember(BookList *L, uint ID);
void MenuAdmin(BookList *L) ;
void ChangePassword();

void toxy(int x, int y) ;
void color(short x);
void HideCursor();
uint readint();//读入数字
void delay();
Status putbook(BookList *L);
/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/

#endif // BOOKS_MANAGEMENT_SYSTEM_H_INCLUDED
