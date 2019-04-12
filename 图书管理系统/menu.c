#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "Books_Management_System.h"
void MenuAdmin(BookList *L)    //����Ա�˵�
{
	do
	{
		system("cls");  //����
		HideCursor();  //���ع��
		color(9);    //����һ���ÿ�����ɫ
		char t;
		toxy(50,5);//������ƶ�����50��5�����괦
		printf(" ͼ��ݹ���Աϵͳ");
		toxy(48,8);
		printf("|     1.ͼ�����      |");
		toxy(48,10);
		printf("|     2.ͼ�����      |");
		toxy(48,12);
		printf("|     3.ͼ���ѯ      |");
		toxy(48,14);
		printf("|     4.ͼ������      |");
		toxy(48,16);
		printf("|     5.�޸�����      |");
		toxy(48,18);
		printf("|     6.�˳�ϵͳ      |");
		t=getch();    //�����Ժ���
		switch(t)
		{
			case '1':
				{
					if(putbook(L))
						printf("���ɹ���");
					else
						printf("���ʧ�ܣ�");
					break;
				}
			case '2':
				{
					system("cls");
					HideCursor();
					color(9);
					toxy(48,5);
					printf("���������(������9λ����)��");
					uint bnumber = readint();
					Book *e = FindBook(*L,bnumber);
					if(e == NULL)
					{
						system("cls");
						HideCursor();
						color(9);
						toxy(48,5);
						printf("ͼ�����δӵ�и��鼮��");
					}
					else
					{
						DeleteBook(L, bnumber);
						system("cls");
						HideCursor();
						color(9);
						toxy(48,5);
						printf("ͼ���ѳɹ�ɾ����");


					}
					toxy(48,7);
					printf("�Զ�������...");
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
					printf("���������(������9λ����)��");
					uint bnumber = readint();
					Book *e = FindBook(*L,bnumber);
					if(e)Printone(e);
					else
					{
						system("cls");
						HideCursor();
						color(9);
						toxy(48,5);
						printf("ͼ�����δӵ�и��鼮��");
					}

					printf("\n\t\t�����������...\n");
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
						printf("��ʱ��û��ͼ�飡");
					}
					else Printall(*L);
					printf("\n\t\t�����������...\n");
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
	printf("��������Ҫ��ӵ����(������9λ������");
	uint temp = readint();
	Book *e;
	e = FindBook(*L, temp);
	if(e != NULL)
	{
		toxy(20,7);
		printf("\t������Ѵ��ڣ�");
		toxy(20,9);
		printf("\t____________________________________________________________");
		toxy(20,10);
		printf("\t|    ���    |          ����          |        ����        |");
		toxy(20,11);
		printf("\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		toxy(20,12);
		printf("\t____________________________________________________________\n");
		toxy(20,13);
		printf("\t|%-12d|%-24s|%-20s|\n",e->bnumber,e->bname,e->bauthor);
		toxy(20,14);
		printf("\t------------------------------------------------------------\n");
		toxy(20,15);
		printf("\t��������Ҫ��ӵ�����(������9λ����)��");
		uint sum = readint();
		e->sum += sum;
		e->left += sum;
		toxy(20,16);
		printf("\t��ӳɹ���");
		delay();
		fflush(stdin);
		return success;
	}
	else
	{
		e = (Book *)malloc(sizeof(Book));
		e->bnumber = temp;
		toxy(20,6);
		printf("������������");
		scanf("%s",e->bname);
		fflush(stdin);
		toxy(20,7);
		printf("�������������֣�");
		scanf("%s",e->bauthor);
		fflush(stdin);
		toxy(20,8);
		printf("�������������(������9λ����)��");
		temp = readint();
		e->sum = temp;
		AddBook(L,*e);
		toxy(20,9);
		printf("��ӳɹ���");
		delay();
		fflush(stdin);
		return success;
	}
	return success;
}
void MenuMember(BookList *L, uint ID)//ѧ���˵�
{
	do
	{
		system("cls");
		HideCursor();
		color(9);
		char t;
		toxy(51,5);
		printf(" ͼ���ѧ��ϵͳ");
		toxy(48,8);
		printf("|     1.ͼ���ѯ      |");
		toxy(48,10);
		printf("|     2.ͼ������      |");
		toxy(48,12);
		printf("|     3.����ͼ��      |");
		toxy(48,14);
		printf("|     4.Ԥ��ͼ��      |");
		toxy(48,16);
		printf("|     5.�黹ͼ��      |");
		toxy(48,18);
		printf("|     6.�˳�ϵͳ      |");
		t=getch();
		switch(t)
		{
			case '1':
				{
					system("cls");
					HideCursor();
					color(9);
					toxy(48,5);
					printf("���������(������9λ����)��");
					uint bnumber = readint();
					Book *e = FindBook(*L,bnumber);
					if(e)Printone(e);
					else
					{
						system("cls");
						HideCursor();
						color(9);
						toxy(48,5);
						printf("ͼ�����δӵ�и��鼮��");
					}

					printf("\n\t\t�����������...\n");
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
						printf("��ʱ��û��ͼ�飡");
					}
					else Printall(*L);
					printf("\n\t\t�����������...\n");
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
					printf("���������(������9λ����)��");
					uint bnumber = readint();
					Book *e = FindBook(*L,bnumber);
					if(e == NULL)
					{
						toxy(48,7);
						printf("ͼ�����δӵ�и��鼮��");

					}
					else if(e->left > 0)
					{
						toxy(48,7);
						if(BorrowBook(e, ID))
							printf("���ĳɹ���");
						else
							printf("����ʧ�ܣ�");
					}
					else if(e->left <= 0)
					{
						toxy(48,7);
						printf("�������޿��,�Ƿ���Ԥ����(y/n)");
						char ch;
						while((ch = getch()) && ch != 'n')
							if(ch == 'y')
							{
								ReserveBook(e, ID);
								toxy(48,9);
								printf("Ԥ���ɹ�������ʱ���ǻ�����һʱ����ģ�");
								break;
							}
					}
					toxy(48,11);
					printf("�Զ�������...");
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
					printf("���������(������9λ����)��");
					uint bnumber = readint();
					Book *e = FindBook(*L, bnumber);
					if(e == NULL)
					{
						toxy(48,7);
						printf("ͼ�����δӵ�и��鼮��");
					}
					else if(e->left > 0)
					{
						toxy(48,7);
						printf("�������п�棬�Ƿ�ֱ�ӽ��ģ�(y/n)");
						char ch;
						while((ch = getch()) && ch != 'n')
							if(ch == 'y')
							{
								BorrowBook(e, ID);
								toxy(48,8);
								printf("���ĳɹ���");
								break;
							}
					}
					else if(e->left <= 0)
					{
						toxy(48,7);
						if(ReserveBook(e, ID))
							printf("Ԥ���ɹ�������ʱ���ǻ�����һʱ����ģ�");
						else
							printf("Ԥ��ʧ�ܣ�");
					}
					toxy(48,10);
					printf("�Զ�������...");
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
					printf("���������(������9λ����)��");
					uint bnumber = readint();
					Book *e = FindBook(*L,bnumber);
					toxy(48,7);
					if(e == NULL)
					{
						printf("ͼ�����δӵ�и��鼮��");
					}
					else
					{
						int x = ReturnBook(e, ID);
						 if(x)
							printf("�黹�ɹ���");
						else
							printf("��û�н��Ȿ�飡");
					}
					printf("�Զ�������...");
					delay();
					fflush(stdin);
					break;
				}
			case '6':return;
			default :break;
		}
	}while(1);
}

