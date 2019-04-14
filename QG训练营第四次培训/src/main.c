#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "da.h"
int a[10005];
int b[50005];
int c[200005];
int d[105];

const long long r = 1201322;
int main()
{

	int begin,end;
	srand((int)time(0));
	int *temp;
	FILE *p1;
	FILE *p2;
	FILE *p3;
	long long ans = 0;
	do{
		system("cls");
		printf("\ttest sort:(enter q exit)\n\n");
		printf("\t1.insertSort\n\n");
		printf("\t2.MergeSort\n\n");
		printf("\t3.QuickSort_Recursion\n\n");
		printf("\t4.RadixCountSort\n\n");
		printf("\t5.CountSort\n\n");
		printf("\t6.QuickSort\n\n");
		printf("please enter your choose:");
		char ch;
		ch = getchar();
		switch(ch)
		{
			case '1':
			{
				//打开文件读入
				printf("\ninsertSort:\n");
				p1= fopen("text10000.txt","r");
				p2= fopen("text50000.txt","r");
				p3= fopen("text200000.txt","r");
				for(int i = 0;i<10000;i++)
					fscanf(p1,"%d",&a[i]);
				for(int i = 0;i<50000;i++)
					fscanf(p2,"%d",&b[i]);
				for(int i = 0;i<200000;i++)
					fscanf(p3,"%d",&c[i]);
				//测试
				begin = clock();
				insertSort(a,10000);
				end = clock();
				printf("10000:%dms\n",end-begin);
				begin = clock();
				insertSort(b,50000);
				end = clock();
				printf("50000:%dms\n",end-begin);
				begin = clock();
				insertSort(c,200000);
				end = clock();
				printf("200000:%dms\n",end-begin);
				//关闭文件
				fclose(p1);
				fclose(p2);
				fclose(p3);
				//测试小数据
				ans = 0;
				for(int i = 0;i<100000;i++)
				{
					for(int i = 0;i<100;i++)
						d[i] =(int)(r*rand()/(RAND_MAX+1.0));
					begin = clock();
					insertSort(d,100);
					end = clock();
					ans+=end-begin;
				}
				printf("\ninsertSort(100k*100):%I64dms\n",ans);
				break;
			}
			case '2':
			{
				//打开文件输入
				printf("\nMergeSort:\n");
				p1= fopen("text10000.txt","r");
				p2= fopen("text50000.txt","r");
				p3= fopen("text200000.txt","r");
				for(int i = 0;i<10000;i++)
					fscanf(p1,"%d",&a[i]);
				for(int i = 0;i<50000;i++)
					fscanf(p2,"%d",&b[i]);
				for(int i = 0;i<200000;i++)
					fscanf(p3,"%d",&c[i]);
				//测试
				begin = clock();
				temp = NULL;
				MergeSort(a,0,10000-1,temp);
				end = clock();
				printf("10000:%dms\n",end-begin);
				begin = clock();
				temp = NULL;
				MergeSort(b,0,50000-1,temp);
				end = clock();
				printf("50000:%dms\n",end-begin);
				begin = clock();
				temp = NULL;
				MergeSort(c,0,200000-1,temp);
				end = clock();
				printf("200000:%dms\n",end-begin);
				//关闭文件
				fclose(p1);
				fclose(p2);
				fclose(p3);
				//小数据测试
				ans = 0;
				for(int i = 0;i<100000;i++)
				{
					for(int i = 0;i<100;i++)
						d[i] =(int)(r*rand()/(RAND_MAX+1.0));
					begin = clock();
					temp = NULL;
					MergeSort(d,0,100-1,temp);
					end = clock();
					ans+=end-begin;
				}
				printf("\nMergeSort(100k*100):%I64dms\n",ans);
				break;
			}
			case '3':
			{
				//打开文件输入
				printf("\nQuickSort_Recursion:\n");
				p1= fopen("text10000.txt","r");
				p2= fopen("text50000.txt","r");
				p3= fopen("text200000.txt","r");
				for(int i = 0;i<10000;i++)
					fscanf(p1,"%d",&a[i]);
				for(int i = 0;i<50000;i++)
					fscanf(p2,"%d",&b[i]);
				for(int i = 0;i<200000;i++)
					fscanf(p3,"%d",&c[i]);
				//测试
				begin = clock();
				QuickSort_Recursion(a,0,10000-1);
				end = clock();
				printf("10000:%dms\n",end-begin);
				begin = clock();
				QuickSort_Recursion(b,0,50000-1);
				end = clock();
				printf("50000:%dms\n",end-begin);
				begin = clock();
				QuickSort_Recursion(c,0,200000-1);
				end = clock();
				printf("200000:%dms\n",end-begin);
				//关闭文件
				fclose(p1);
				fclose(p2);
				fclose(p3);
				//小数据测试
				ans = 0;
				for(int i = 0;i<100000;i++)
				{
					for(int i = 0;i<100;i++)
						d[i] =(int)(r*rand()/(RAND_MAX+1.0));
					begin = clock();
					QuickSort_Recursion(d,0,100-1);
					end = clock();
					ans+=end-begin;
				}
				printf("\nQuickSort_Recursion(100k*100):%I64dms\n",ans);
				break;
			}
			case '4':
			{
				//打开文件输入
				printf("\nRadixCountSort:\n");
				p1= fopen("text10000.txt","r");
				p2= fopen("text50000.txt","r");
				p3= fopen("text200000.txt","r");
				for(int i = 0;i<10000;i++)
					fscanf(p1,"%d",&a[i]);
				for(int i = 0;i<50000;i++)
					fscanf(p2,"%d",&b[i]);
				for(int i = 0;i<200000;i++)
					fscanf(p3,"%d",&c[i]);
				//测试
				begin = clock();
				RadixCountSort(a,10000);
				end = clock();
				printf("10000:%dms\n",end-begin);
				begin = clock();
				RadixCountSort(b,50000);
				end = clock();
				printf("50000:%dms\n",end-begin);
				begin = clock();
				RadixCountSort(c,200000);
				end = clock();
				printf("200000:%dms\n",end-begin);
				//关闭文件
				fclose(p1);
				fclose(p2);
				fclose(p3);
				//小数据测试
				ans = 0;
				for(int i = 0;i<100000;i++)
				{
					for(int i = 0;i<100;i++)
						d[i] =(int)(r*rand()/(RAND_MAX+1.0));
					begin = clock();
					RadixCountSort(d,100-1);
					end = clock();
					ans+=end-begin;
				}
				printf("\nRadixCountSort(100k*100):%I64dms\n",ans);
				break;
			}
			case '5':
			{
				//打开文件输入
				printf("\nCountSort(memory flow):\n");
				p1= fopen("text10000.txt","r");
				p2= fopen("text50000.txt","r");
				p3= fopen("text200000.txt","r");
				for(int i = 0;i<10000;i++)
					fscanf(p1,"%d",&a[i]);
				for(int i = 0;i<50000;i++)
					fscanf(p2,"%d",&b[i]);
				for(int i = 0;i<200000;i++)
					fscanf(p3,"%d",&c[i]);
				//测试
				int max;
				begin = clock();
				max = -1;
				for(int i = 0;i<10000;i++)
					if(a[i]>max)max = a[i];
				CountSort(a,10000,max);
				end = clock();
				printf("10000:%dms\n",end-begin);
				begin = clock();
				max = -1;
				for(int i = 0;i<50000;i++)
					if(a[i]>max)max = a[i];
				CountSort(a,50000,max);
				end = clock();
				printf("50000:%dms\n",end-begin);
				begin = clock();
				max = -1;
				for(int i = 0;i<200000;i++)
					if(a[i]>max)max = a[i];
				CountSort(a,200000,max);
				end = clock();
				printf("200000:%dms\n",end-begin);
				//关闭文件
				fclose(p1);
				fclose(p2);
				fclose(p3);
				//小数据测试
				ans = 0;
				for(int i = 0;i<100000;i++)
				{
					for(int i = 0;i<100;i++)
						d[i] =(int)(r*rand()/(RAND_MAX+1.0));

					begin = clock();
					max = -1;
					for(int i = 0;i<100;i++)
						if(a[i]>max)max = a[i];
					CountSort(a,100,max);
					end = clock();

					ans+=end-begin;
				}
				printf("\nRadixCountSort(100k*100):%I64dms\n",ans);
				break;
			}
			case '6':
			{
				//打开文件读入
				printf("\nQuickSort:\n");
				p1= fopen("text10000.txt","r");
				p2= fopen("text50000.txt","r");
				p3= fopen("text200000.txt","r");
				for(int i = 0;i<10000;i++)
					fscanf(p1,"%d",&a[i]);
				for(int i = 0;i<50000;i++)
					fscanf(p2,"%d",&b[i]);
				for(int i = 0;i<200000;i++)
					fscanf(p3,"%d",&c[i]);
				//测试
				begin = clock();
				QuickSort(a,10000);
				end = clock();
				printf("10000:%dms\n",end-begin);
				begin = clock();
				QuickSort(b,50000);;
				end = clock();
				printf("50000:%dms\n",end-begin);
				begin = clock();
				QuickSort(c,200000);;
				end = clock();
				printf("200000:%dms\n",end-begin);
				//关闭文件
				fclose(p1);
				fclose(p2);
				fclose(p3);
				//测试小数据
				ans = 0;
				for(int i = 0;i<100000;i++)
				{
					for(int i = 0;i<100;i++)
						d[i] =(int)(r*rand()/(RAND_MAX+1.0));
					begin = clock();
					QuickSort(d,100);
					end = clock();
					ans+=end-begin;
				}
				printf("\nQuickSort(100k*100):%I64dms\n",ans);
				break;
			}
			case 'q':return 0;
			default:printf("enter wrong!\n");
		}
		system("pause");
		fflush(stdin);
	}while(1);
    return 0;
}

