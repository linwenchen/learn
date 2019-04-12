#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include "Books_Management_System.h"

void AdminLogin(BookList *L)  //��¼����Ա�˻�
{
	system("cls");
	FILE *temp = fopen("admin.txt","r");
	rewind(temp);
	int ch = fgetc(temp);
	if(ch == EOF)//���û������
	{

		fclose(temp);
		toxy(44,8);
		printf("��������һ�ε�½������������������!\n");
		toxy(44,10);
		printf("���볤��С��20,��ʹ�����ֺ���ĸ�����\n");
		ChangePassword();
		MenuAdmin(L);
		return;
	}
	else fclose(temp);
	toxy(20,5);
	printf("���������Ĺ���Ա���룺");
	temp = fopen("admin.txt","r");
	char s[LENGTH];
	char t[LENGTH];
	scanf("%s",s);
	fscanf(temp,"%s",t);
	fclose(temp);
	//�������Աϵͳ
	if(!strcmp(s,t))MenuAdmin(L);
	else
	{
		toxy(20,7);
		printf("���������ע���Сд��");
		toxy(20,9);
		printf("�����������...");
		getch();
	}
	fflush(stdin);

}

void MemberLogin(BookList *L) //��½ѧ���˻�
{
	system("cls");
	FILE *temp = fopen("member.txt","a+");
	toxy(20,5);
	printf("����������ͼ��֤��(�����ھ�λ��)��");
	uint ID = readint();
	fprintf(temp,"%d\n",ID);
	MenuMember(L,ID);
	fclose(temp);
	fflush(stdin);
}

void ChangePassword()  //�޸�����
{
	toxy(44,12);
	//��д��ģʽ���ļ�
	printf("password��");
	FILE *temp = fopen("admin.txt","w");
	char ch;
	//�����һ����menu�е��û��Զ�����
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
			//���������,�ر��ļ�
			fclose(temp);
			printf("���������������������룡");
			printf("�������������");
			getch();
			//�ٵ��ú���
			ChangePassword();
			return;
		}
	}
	//���뱣��ɹ�
	fclose(temp);
}

void HideCursor()  //���ع��
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0};
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void color(short x)  //����ɫ
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

void toxy(int x, int y)  //������ƶ���X,Y���괦
{
COORD pos = { x , y };
HANDLE Out = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleCursorPosition(Out, pos);
}

uint readint()//��������
{
	char ch;
	long long sum = 0;
	int test = 0;//����Ƿ����������
	while((ch = getchar()) && ch!='\n')
	{
		//��λ��
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
		printf("��������������:");
		return readint();
	}
	return (uint)(sum);
}

void delay()//��ʱ����
{
	Sleep(1000);
}
