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
#include <time.h>//����ʱ��
#include <stdio.h>//�ǵ�ɾ��
#include <stdlib.h>//�ǵ�ɾ��
#include <windows.h>

/**************************************************************
*	Macro Define Section
**************************************************************/
#define LENGTH 100			//�������Լ��������ֳ���
#define T 90				//�軹����(��)
#define T_sec (T * 24 *60 * 60)		//�軹����(��)
typedef unsigned int uint;
/**************************************************************
*	Struct Define Section
**************************************************************/

//�ѽ������
typedef struct BorrowReader{
	uint ID;	//ͼ��֤��
	time_t Time;	//����ʱ��
	time_t duetime; //����ʱ��
	int flag;	//�Ƿ�����
	struct BorrowReader *next;
}BorrowReader,*BReader;

//�Ŷ�Ԥ���Ķ���
typedef struct WaitingQueue{
	uint ID;	//�ȴ��ߵ�ͼ��֤��
	struct WaitingQueue *next;
}WaitingQueue,*WQueue;

//������������Book
typedef struct BOOK{
	uint bnumber;		//���
	char bname[LENGTH];	//����
	char bauthor[LENGTH];	//�������
	uint sum;		//�������
	uint left;		//���ʣ����

	BReader breader;	//����������
	WQueue wqueue;		//Ԥ��������

	struct BOOK *next;	//��һ����
}Book,*BookList;

typedef struct Admin{
	char password[LENGTH];
}Admin;
//��������
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

BookList InitSystem(void);//��ʼ������
void over(BookList L);//�˳�����
void AddBook(BookList *L,Book e);//����鼮
BookList FindBook(BookList L, uint bnumber);//Ѱ���鼮
Status DeleteBook(BookList *L,uint bnumber);//ɾ���鼮
void Printall(BookList L);//��ӡͼ����Ϣ
void Printone(Book *e);//��ӡһ��ͼ�����ϸ��Ϣ
Status BorrowBook(Book* e, uint ID);//����
Status ReturnBook(Book *e,uint ID);//����
Status ReserveBook(Book *e, uint ID);//Ԥ��

void AdminLogin(BookList *L);
void MemberLogin(BookList *L);
void MenuMember(BookList *L, uint ID);
void MenuAdmin(BookList *L) ;
void ChangePassword();

void toxy(int x, int y) ;
void color(short x);
void HideCursor();
uint readint();//��������
void delay();
Status putbook(BookList *L);
/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/

#endif // BOOKS_MANAGEMENT_SYSTEM_H_INCLUDED
