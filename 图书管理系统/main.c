#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Books_Management_System.h"
#include <windows.h>
#include <conio.h>

int main()
{
	BookList head = InitSystem();
	do
	{
		system("cls");  //����
		HideCursor();  //���ع��
		color(9);    //����һ���ÿ�����ɫ
		char t;
		toxy(54,5);//������ƶ�����50��5�����괦
		printf(" ��½����");
		toxy(48,8);
		printf("|     1.����Աϵͳ    |");
		toxy(48,10);
		printf("|     2.ѧ��ϵͳ      |");
		toxy(48,12);
		printf("|     3.�˳����      |");
		t=getch();    //�����Ժ���
		switch(t)
		{
			case '1':{AdminLogin(&head);break;}
			case '2':{MemberLogin(&head);break;}
			case '3':
				{
					over(head);
					return 0;
				}
			default :break;
		}
	}while(1);
	return 0;
}
