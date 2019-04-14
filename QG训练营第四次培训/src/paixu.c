#include "da.h"
#include <string.h>
#include <stdlib.h>
/**
 *  @name        : void insertSort(int *a,int n);
 *  @description : 插入排序
 *  @param       : 数组指针 a, 数组长度 n
 */
void insertSort(int *a,int n)
{
	for(int i = 1;i<n;i++)
	{
		int temp = a[i];
		for(int j = i-1;j>=0;j--)
		{
			if(temp < a[j])//后移
			{
				a[j+1] = a[j];
				a[j] = temp;
			}
			else
			{
				//a[j+1] = temp;
				break;
			}
		}
	}
}

/**
 *  @name        : void MergeArray(int *a,int begin,int mid,int end,int *temp);
 *  @description : 归并排序（合并数组）
 *  @param       : 数组指针a，数组起点begin，数组中点mid，数组终点end，承载数组指针temp
 */
void MergeArray(int *a,int begin,int mid,int end,int *temp)
{
	temp = (int *)malloc((end - begin + 1)*sizeof(int));
	int left = begin, right = mid+1,index = 0;
	while(left <= mid && right <= end)
	{
		if(a[left] <= a[right])
			temp[index++] = a[left++];
		else
			temp[index++] = a[right++];
		if(left > mid)//左边已经排完
		{
			while(right <= end)
				temp[index++] = a[right++];
		}
		else if(right > end)//右边已经排完
		{
			while(left <= mid)
				temp[index++] = a[left++];
		}
	}
	for(int i = 0;i<index;i++)a[begin+i] = temp[i];
	free(temp);
}

/**
 *  @name        : void MergeSort(int *a,int begin,int end,int *temp);
 *  @description : 归并排序
 *  @param       : 数组指针a，数组起点begin，数组终点end，承载数组指针temp
 */
void MergeSort(int *a,int begin,int end,int *temp)//二分区间
{
	if(begin < end)
	{
		int mid = (begin + end)/2;
		MergeSort(a,begin,mid,temp);
		MergeSort(a,mid+1,end,temp);
		MergeArray(a,begin,mid,end,temp);
	}
}

/**
 *  @name        : void QuickSort(int *a, int begin, int end);
 *  @description : 快速排序（递归版）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
void QuickSort_Recursion(int *a, int begin, int end)
{
	if(begin < end)
	{
		int m = Partition(a,begin,end);
		//分区
		//递归将左区间排序
		QuickSort_Recursion(a,begin,m-1);
		//递归将右区间排序
		QuickSort_Recursion(a,m+1,end);
	}
}
/**
 *  @name        : void QuickSort(int *a,int size)
 *  @description : 快速排序（非递归版）
 *  @param       : 数组指针a，数组长度size
 */
void QuickSort(int *a,int size)
{
	int begin = 0;
	int end = size-1;
	int *b = (int *)malloc((size + 1)*sizeof(int));
	b[1] = begin;
	b[2] = end;
	b[0] = 2;
	while(b[0])
	{
		int right = b[b[0]--];
		int left = b[b[0]--];
		int index = Partition(a,left,right);
		if((index - 1) > left)
		{
			b[++b[0]] = left;
			b[++b[0]] = index - 1;
		}
		if((index - 1) < right)
		{
			b[++b[0]] = index +1;
			b[++b[0]] = right;
		}
	}
}
/**
 *  @name        : void QuickSort(int *a, int begin, int end)
 *  @description : 快速排序（枢轴存放）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
int Partition(int *a, int begin, int end)
{
	/*
		枢纽一开始是拿出来放到第一个位置，(swap)
		然后从第一个位置后开始，加入分区(s1:比枢纽值小 s2:比枢纽值大)
		如果比枢纽值大，往后走
		如果比枢纽值小，和当前的分界（++m）交换
		这时的分界指向的是比枢纽值大的值，也是s2分区的左闭区间
		交换之后m就是s2区的左开区间
	*/
	int p = a[begin];//枢纽，选定值
	int m = begin;//s1 s2的分界点，也是排序后枢纽的位置
	for(int i = begin + 1;i <= end; i++)//探索未知的区域
	{
		if(a[i] < p)
		{
			m++;
			int temp;
			temp = a[i];
			a[i] = a[m];
			a[m] = temp;
		}
	}
	int temp = a[m];
	a[m] = a[begin];
	a[begin] = temp;
	return m;

}

/**
 *  @name        : void CountSort(int *a, int size , int max)
 *  @description : 计数排序
 *  @param       : 数组指针a，数组长度size，数组最大值max
 */
void CountSort(int *a, int size , int max)//没有对负数情况处理！！！
{
	int *b = (int *)malloc((max+1)*sizeof(int));
	//预处理b数组
	for(int i = 0;i<=max;i++)b[i] = 0;
	for(int i = 0;i < size;i++)
		b[a[i]]++;
	int index = 0;
	for(int i = 0;i <= max;i++)
	{
		while(b[i]--)
			a[index++] = i;
	}

}

/**
 *  @name        : void RadixCountSort(int *a,int size)
 *  @description : 基数计数排序
 *  @param       : 数组指针a，数组长度size
 */

void RadixCountSort(int *a,int size)
{
	int *b[10];
	for(int i = 0;i<10;i++)//分配空间
	{
		b[i] = (int *)malloc((size + 1) * sizeof(int));
		b[i][0] = 0;
	}
	int max = -100000000;
	for(int i = 0;i<size;i++)
	{
		if(a[i] > max)max = a[i];
	}
	int num = 0;
	while(max)//计算最大数的位数
	{
		num++;
		max/=10;
	}
	for(int pos = 1; pos <= num;pos++)
	{
		for(int i = 0;i<size;i++)
		{
			int x;
			int d = 1;
			for(int i = 1;i<=pos;i++)d*=10;
			x = (a[i]/d)%10;
			b[x][(++b[x][0])] = a[i];
		}
		for(int i = 0,j = 0;i<10;i++)
		{
			for(int k = 1; k <= b[i][0];k++)
				a[j++] = b[i][k];
			b[i][0] = 0;
		}
	}


}
/**
 *  @name        : void ColorSort(int *a,int size)
 *  @description : 颜色排序
 *  @param       : 数组指针a（只含0，1，2元素），数组长度size
 */
void ColorSort(int *a,int size)
{
	int *begin = a;
	int *end = (a+size-1);
	int *p = a;
	while(p <= end)
	{
		if(*p == 0)
		{
			while(*begin == 0 && begin < p)begin++;
			int temp = *p;
			*p = *begin;
			*begin = temp;
			begin++;
		}
		else if(*p == 2)
		{
			while(*end == 2 && end > p)end--;
			int temp = *p;
			*p = *end;
			*end = temp;
			end--;
		}
		if(begin < p && (*p == 0 || *p == 2))
			continue;
		else
			p++;
	}
	 /*
		对数组进行扫描，
		计录1的个数和整个数组的和。
		扫描完后可以得出1的数目t，
		2的数目(sum-t)/2，
		最后可以得出0的数目，
		这样子根据0，1，2的数目再对数组进行设置值。

	int count = 0;
	int sum = 0;
	for(int i = 0;i<size;i++)
	{
		if(a[i] == 1)count++;
		sum+=a[i];
	}
	int t = (sum-count)/2;
	for(int i = 0;i<size;i++)
	{
		if(i<(size - count - t))a[i] = 0;
		else if(i < (size - t))a[i] = 1;
		else a[i] = 2;
	}
	*/
}


/**
 *  @name        : 自拟
 *  @description : 在一个无序序列中找到第K大/小的数
 *  @param       : 数组指针a，数组长度size，K的值
 */
int findk(int *a,int size,int k)
{
	int begin = 0;
	int end = size-1;
	while(begin < end)//二分算法
	{
		int m = Partition(a,begin,end);
		if(m == k-1)return a[m];
		else if(m > k)
			end = m-1;
		else
			begin = m+1;
	}
	return begin;
}
