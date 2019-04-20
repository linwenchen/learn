#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "LinkBiTree.h"
int main()
{
	while(1)
	{
		printf("\tע�⣺���������������ƣ�ֻ֧��0~9����֧�ָ�������q���˳�\n");
		printf("\t��������ʽ��");
		char s[205];
		fgets(s,201,stdin);
		s[strlen(s)-1] = '\0';
		if(s[0] == '\n')continue;
		if(s[0] == 'q' || s[0] == '\0')break;

		char *t = PreProcess(s);
		if(t == NULL)
		{
			printf("\t��ʽ����\n");
			printf("\t�����������...");
			getch();
			fflush(stdin);
			system("cls");
			continue;
		}
		BiTree T = NULL;
		if(!InitBiTree(&T))
		{
			printf("\t�ڴ����ʧ�ܣ�");
		}
		if(CreateBiTree(T,t))
			printf("\t�����������ɹ���\n");
		printf("\t��׺���ʽ��");
		InOrderTraverse(T,Print);
		printf("\n");
		printf("\tǰ׺���ʽ��");
		PreOrderTraverse(T,Print);
		printf("\n");
		printf("\t��׺���ʽ��");
		PostOrderTraverse(T,Print);
		printf("\n");
		int ans = Value(T);
		if(ans == -2000001000)printf("\t��0��\n");
		else printf("\tvalue:%d\n",ans);
		printf("\t�����������...");
		getch();
		fflush(stdin);
		system("cls");


	}
    return 0;
}
