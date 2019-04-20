#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "LinkBiTree.h"
int main()
{
	while(1)
	{
		printf("\t注意：由于数据类型限制，只支持0~9，不支持负数，按q可退出\n");
		printf("\t请输入表达式：");
		char s[205];
		fgets(s,201,stdin);
		s[strlen(s)-1] = '\0';
		if(s[0] == '\n')continue;
		if(s[0] == 'q' || s[0] == '\0')break;

		char *t = PreProcess(s);
		if(t == NULL)
		{
			printf("\t格式错误！\n");
			printf("\t按任意键返回...");
			getch();
			fflush(stdin);
			system("cls");
			continue;
		}
		BiTree T = NULL;
		if(!InitBiTree(&T))
		{
			printf("\t内存分配失败！");
		}
		if(CreateBiTree(T,t))
			printf("\t二叉树建立成功！\n");
		printf("\t中缀表达式：");
		InOrderTraverse(T,Print);
		printf("\n");
		printf("\t前缀表达式：");
		PreOrderTraverse(T,Print);
		printf("\n");
		printf("\t后缀表达式：");
		PostOrderTraverse(T,Print);
		printf("\n");
		int ans = Value(T);
		if(ans == -2000001000)printf("\t除0！\n");
		else printf("\tvalue:%d\n",ans);
		printf("\t按任意键返回...");
		getch();
		fflush(stdin);
		system("cls");


	}
    return 0;
}
