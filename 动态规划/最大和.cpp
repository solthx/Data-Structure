/*
	题目大意:
		给一个矩阵，求出他的最大子矩阵
	分析:
		最大子串的变形
		假如最大子矩阵在第i行到第j行
		那么和就是 第i和元素到第j行元素的和的最大子串和 
*/ 

# include <stdio.h>
# include <string.h>
# define max(a,b) a>b?a:b
int num[102][102];

int Cal(int a,int b,int n) 
{
	int i,j,k,sum;
	int MAX;
	MAX = sum = num[a][1] - num[b][1];
	for ( j=2; j<=n; ++j )
	{
		if ( sum<0 ) sum = num[a][j]-num[b][j];
		else 	sum += num[a][j]-num[b][j];
		if ( MAX<sum ) 	MAX = sum;
	}
	return MAX;
}

int main(void)
{
	int x,y,i,j,k,T,len;
	int first,last;
	scanf("%d",&T);
	while ( T-- )
	{
		memset(num,0,sizeof(num));
		scanf("%d %d",&y,&x);
		for ( i=1; i<=y; ++i )
			for ( j=1; j<=x; ++j ){
				scanf("%d",&num[i][j]);
				num[i][j] += num[i-1][j];
			}
		int MAX = -0x3f3f3f3f;
		for ( i=0; i<=y-1; ++i )  //剪掉i 
		{
			for ( j=i+1; j<=y; ++j )
			{
				MAX = max( MAX,Cal(j,i,x) );  //计算i+1行到第j行的最大子矩阵和 
			}
		}
		printf("%d\n",MAX);
	}
	return 0;
}
