#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "Books_Management_System.h"

void AdminLogin(BookList *L)  //登录管理员账户
{
	system("cls");
	FILE *temp = fopen("admin.txt","r");
	rewind(temp);
	int ch = fgetc(temp);
	if(ch == EOF)//如果没有密码
	{

		fclose(temp);
		toxy(44,8);
		printf("这是您第一次登陆！请先设置您的密码!\n");
		toxy(44,10);
		printf("密码长度小于20,请使用数字和字母的组合\n");
		ChangePassword();
		MenuAdmin(L);
		return;
	}
	else fclose(temp);
	toxy(20,5);
	printf("请输入您的管理员密码：");
	temp = fopen("admin.txt","r");
	char s[LENGTH];
	char t[LENGTH];
	scanf("%s",s);
	fscanf(temp,"%s",t);
	fclose(temp);
	//进入管理员系统
	if(!strcmp(s,t))MenuAdmin(L);
	else
	{
		toxy(20,7);
		printf("密码错误！请注意大小写！");
		toxy(20,9);
		printf("按任意键返回...");
		getch();
	}
	fflush(stdin);

}

void MemberLogin(BookList *L) //登陆学生账户
{
	system("cls");
	FILE *temp = fopen("member.txt","a+");
	toxy(20,5);
	printf("请输入您的图书证号(不多于九位数)：");
	uint ID = readint();
	fprintf(temp,"%d\n",ID);
	MenuMember(L,ID);
	fclose(temp);
	fflush(stdin);
}

void ChangePassword()  //修改密码
{
	toxy(44,12);
	//以写入模式打开文件
	printf("password：");
	FILE *temp = fopen("admin.txt","w");
	char ch;
	//解决第一次在menu中调用会自动返回
	if((ch = getchar()) && ch != '\n')fputc(ch,temp);
	while((ch = getchar()) && ch != '\n')
	{
		if(ch >= '0' && ch <= '9')
			fputc(ch,temp);
		else if(ch >= 'a' && ch <= 'z')
			fputc(ch,temp);
		else if(ch >= 'A' && ch <= 'Z')
			fputc(ch,temp);
		else
		{
			//有输入错误,关闭文件
			fclose(temp);
			printf("您的输入有误！请重新输入！");
			printf("按任意键继续！");
			getch();
			//再调用函数
			ChangePassword();
			return;
		}
	}
	//密码保存成功
	fclose(temp);
}

void HideCursor()  //隐藏光标
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0};
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void color(short x)  //调颜色
{
	if(x>=0&&x<=15)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
	}
}

void toxy(int x, int y)  //将光标移动到X,Y坐标处
{
COORD pos = { x , y };
HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(Out, pos);
}

uint readint()//读入数字
{
	char ch;
	long long sum = 0;
	int test = 0;//检测是否读入了数字
	while((ch = getchar()) && ch!='\n')
	{
		//九位数
		if(ch<'0' || ch>'9' || sum > 1000000000)
		{
			while((ch = getchar())!='\n')continue;
			sum = 200000000000;
			break;
		}
		sum=sum*10+ch-'0';
		if(!test)test = 1;
	}

	if(sum == 200000000000 || test == 0)
	{
		system("cls");
		color(9);
		toxy(48,5);
		printf("错误！请输入数字:");
		return readint();
	}
	return (uint)(sum);
}

void delay()//延时函数
{
	Sleep(1000);
}
