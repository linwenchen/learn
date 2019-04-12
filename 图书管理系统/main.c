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
		system("cls");  //清屏
		HideCursor();  //隐藏光标
		color(9);    //设置一个好看的颜色
		char t;
		toxy(54,5);//将光标移动到（50，5）坐标处
		printf(" 登陆界面");
		toxy(48,8);
		printf("|     1.管理员系统    |");
		toxy(48,10);
		printf("|     2.学生系统      |");
		toxy(48,12);
		printf("|     3.退出软件      |");
		t=getch();    //不回显函数
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
