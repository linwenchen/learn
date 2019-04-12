#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "Books_Management_System.h"
void MenuAdmin(BookList *L)    //管理员菜单
{
	do
	{
		system("cls");  //清屏
		HideCursor();  //隐藏光标
		color(9);    //设置一个好看的颜色
		char t;
		toxy(50,5);//将光标移动到（50，5）坐标处
		printf(" 图书馆管理员系统");
		toxy(48,8);
		printf("|     1.图书入库      |");
		toxy(48,10);
		printf("|     2.图书出库      |");
		toxy(48,12);
		printf("|     3.图书查询      |");
		toxy(48,14);
		printf("|     4.图书总览      |");
		toxy(48,16);
		printf("|     5.修改密码      |");
		toxy(48,18);
		printf("|     6.退出系统      |");
		t=getch();    //不回显函数
		switch(t)
		{
			case '1':
				{
					if(putbook(L))
						printf("入库成功！");
					else
						printf("入库失败！");
					break;
				}
			case '2':
				{
					system("cls");
					HideCursor();
					color(9);
					toxy(48,5);
					printf("请输入书号(不多于9位整数)：");
					uint bnumber = readint();
					Book *e = FindBook(*L,bnumber);
					if(e == NULL)
					{
						system("cls");
						HideCursor();
						color(9);
						toxy(48,5);
						printf("图书馆暂未拥有该书籍！");
					}
					else
					{
						DeleteBook(L, bnumber);
						system("cls");
						HideCursor();
						color(9);
						toxy(48,5);
						printf("图书已成功删除！");


					}
					toxy(48,7);
					printf("自动返回中...");
					delay();
					fflush(stdin);
					break;
				}
			case '3':
				{
					system("cls");
					HideCursor();
					color(9);
					toxy(48,5);
					printf("请输入书号(不多于9位整数)：");
					uint bnumber = readint();
					Book *e = FindBook(*L,bnumber);
					if(e)Printone(e);
					else
					{
						system("cls");
						HideCursor();
						color(9);
						toxy(48,5);
						printf("图书馆暂未拥有该书籍！");
					}

					printf("\n\t\t按任意键返回...\n");
					getch();
					fflush(stdin);
					break;
				}
			case '4':
				{
					system("cls");
					HideCursor();
					color(9);
					if(*L == NULL)
					{
						toxy(48,5);
						printf("暂时还没有图书！");
					}
					else Printall(*L);
					printf("\n\t\t按任意键返回...\n");
					getch();
					fflush(stdin);
					break;
				}
			case '5':
				{
					system("cls");
					ChangePassword();
					break;
				}
			case '6':return;
			default :break;
		}
	}while(1);
}
Status putbook(BookList *L)
{
	fflush(stdin);
	system("cls");
	HideCursor();
	color(9);
	toxy(20,5);
	printf("请输入您要添加的书号(不多于9位整数：");
	uint temp = readint();
	Book *e;
	e = FindBook(*L, temp);
	if(e != NULL)
	{
		toxy(20,7);
		printf("\t书库中已存在：");
		toxy(20,9);
		printf("\t____________________________________________________________");
		toxy(20,10);
		printf("\t|    书号    |          书名          |        作者        |");
		toxy(20,11);
		printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		toxy(20,12);
		printf("\t____________________________________________________________\n");
		toxy(20,13);
		printf("\t|%-12d|%-24s|%-20s|\n",e->bnumber,e->bname,e->bauthor);
		toxy(20,14);
		printf("\t------------------------------------------------------------\n");
		toxy(20,15);
		printf("\t请输入您要添加的数量(不多于9位整数)：");
		uint sum = readint();
		e->sum += sum;
		e->left += sum;
		toxy(20,16);
		printf("\t添加成功！");
		delay();
		fflush(stdin);
		return success;
	}
	else
	{
		e = (Book *)malloc(sizeof(Book));
		e->bnumber = temp;
		toxy(20,6);
		printf("请输入书名：");
		scanf("%s",e->bname);
		fflush(stdin);
		toxy(20,7);
		printf("请输入作者名字：");
		scanf("%s",e->bauthor);
		fflush(stdin);
		toxy(20,8);
		printf("请输入书的数量(不多于9位整数)：");
		temp = readint();
		e->sum = temp;
		AddBook(L,*e);
		toxy(20,9);
		printf("添加成功！");
		delay();
		fflush(stdin);
		return success;
	}
	return success;
}
void MenuMember(BookList *L, uint ID)//学生菜单
{
	do
	{
		system("cls");
		HideCursor();
		color(9);
		char t;
		toxy(51,5);
		printf(" 图书馆学生系统");
		toxy(48,8);
		printf("|     1.图书查询      |");
		toxy(48,10);
		printf("|     2.图书总览      |");
		toxy(48,12);
		printf("|     3.借阅图书      |");
		toxy(48,14);
		printf("|     4.预订图书      |");
		toxy(48,16);
		printf("|     5.归还图书      |");
		toxy(48,18);
		printf("|     6.退出系统      |");
		t=getch();
		switch(t)
		{
			case '1':
				{
					system("cls");
					HideCursor();
					color(9);
					toxy(48,5);
					printf("请输入书号(不多于9位整数)：");
					uint bnumber = readint();
					Book *e = FindBook(*L,bnumber);
					if(e)Printone(e);
					else
					{
						system("cls");
						HideCursor();
						color(9);
						toxy(48,5);
						printf("图书馆暂未拥有该书籍！");
					}

					printf("\n\t\t按任意键返回...\n");
					getch();
					fflush(stdin);
					break;
				}
			case '2':
				{
					system("cls");
					HideCursor();
					color(9);
					if(*L == NULL)
					{
						toxy(48,5);
						printf("暂时还没有图书！");
					}
					else Printall(*L);
					printf("\n\t\t按任意键返回...\n");
					getch();
					fflush(stdin);
					break;
				}
			case '3':
				{
					system("cls");
					HideCursor();
					color(9);
					toxy(48,5);
					printf("请输入书号(不多于9位整数)：");
					uint bnumber = readint();
					Book *e = FindBook(*L,bnumber);
					if(e == NULL)
					{
						toxy(48,7);
						printf("图书馆暂未拥有该书籍！");

					}
					else if(e->left > 0)
					{
						toxy(48,7);
						if(BorrowBook(e, ID))
							printf("借阅成功！");
						else
							printf("借阅失败！");
					}
					else if(e->left <= 0)
					{
						toxy(48,7);
						printf("该书已无库存,是否先预定？(y/n)");
						char ch;
						while((ch = getch()) && ch != 'n')
							if(ch == 'y')
							{
								ReserveBook(e, ID);
								toxy(48,9);
								printf("预定成功，有书时我们会帮你第一时间借阅！");
								break;
							}
					}
					toxy(48,11);
					printf("自动返回中...");
					delay();
					fflush(stdin);
					break;

				}
			case '4':
				{
					system("cls");
					HideCursor();
					color(9);
					toxy(48,5);
					printf("请输入书号(不多于9位整数)：");
					uint bnumber = readint();
					Book *e = FindBook(*L, bnumber);
					if(e == NULL)
					{
						toxy(48,7);
						printf("图书馆暂未拥有该书籍！");
					}
					else if(e->left > 0)
					{
						toxy(48,7);
						printf("该书尚有库存，是否直接借阅？(y/n)");
						char ch;
						while((ch = getch()) && ch != 'n')
							if(ch == 'y')
							{
								BorrowBook(e, ID);
								toxy(48,8);
								printf("借阅成功！");
								break;
							}
					}
					else if(e->left <= 0)
					{
						toxy(48,7);
						if(ReserveBook(e, ID))
							printf("预定成功，有书时我们会帮你第一时间借阅！");
						else
							printf("预定失败！");
					}
					toxy(48,10);
					printf("自动返回中...");
					delay();
					fflush(stdin);
					break;

				}
			case '5':
				{
					system("cls");
					HideCursor();
					color(9);
					toxy(48,5);
					printf("请输入书号(不多于9位整数)：");
					uint bnumber = readint();
					Book *e = FindBook(*L,bnumber);
					toxy(48,7);
					if(e == NULL)
					{
						printf("图书馆暂未拥有该书籍！");
					}
					else
					{
						int x = ReturnBook(e, ID);
						 if(x)
							printf("归还成功！");
						else
							printf("你没有借这本书！");
					}
					printf("自动返回中...");
					delay();
					fflush(stdin);
					break;
				}
			case '6':return;
			default :break;
		}
	}while(1);
}

