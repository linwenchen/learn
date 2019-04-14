#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const long long r = 1201322;
int main()
{
	FILE *p = fopen("text10000.txt","w");
	srand((int)time(0));
	for(int i = 0;i<10000;i++)
	{
		int temp;
		temp =(int)(r*rand()/(RAND_MAX+1.0));
		fprintf(p,"%d ",temp);
	}
	fclose(p);

	p = fopen("text50000.txt","w");
	for(int i = 0;i<50000;i++)
	{
		int temp;
		temp =(int)(r*rand()/(RAND_MAX+1.0));
		fprintf(p,"%d ",temp);
	}
	fclose(p);

	p = fopen("text200000.txt","w");
	for(int i = 0;i<200000;i++)
	{
		int temp;
		temp =(int)(r*rand()/(RAND_MAX+1.0));
		fprintf(p,"%d ",temp);
	}
	fclose(p);
    return 0;
}
