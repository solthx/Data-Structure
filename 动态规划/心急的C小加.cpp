
/*
	题目大意: 给出一对数 x y，求单调递增(即下一组x和y均大于上一组)的序列个数
	分析:
		动态规划解法:
		 先给结构体进行排序 主要以x的大小做升序排列，若相等则按y的大小排
		 此时结构体里的x已经是满足递增
		 k[i]保存到第i组数据为止的最大递增子列数  
		 结果超时 
		 
		 这题用贪心做很简单  - -！ 
*/


# include <cstdio>
# include <string.h>
# include <iostream>
# include <string.h>
# include <algorithm>
using namespace std;

typedef struct {
	int x,y;
}ll;

ll num[5100];
int n,k[5100];

void solve_dp()
{
	int i,j;
	for ( i=0; i<n; ++i ) //扫描每一组数据 
	{
		for ( j=0; j<i; ++j )  
			if ( num[i].y<num[j].y && k[i]<k[j]+1/*第j组的数据比第i组大 所以要开个新的子序列 子序列个数在此基础上加一*/ )  //因为第i组的x必定大于j组的x 所以比较y 若第i组的y小 说明递增秩序被破坏 检查是否要更新最大子序列个数 
			{		
				k[i] = k[j]+1;
			}
	}
	printf("%d\n",*max_element(k,k+n)); //输出所有子序列个数中最多的那个 
}

int cmp(ll a,ll b)
{
	if ( a.x!=b.x )
		return a.x<b.x;
	else
		return a.y<b.y;
}

int main(void)
{
	int N,i,j,v,w,sum,temp;
	scanf("%d",&N);
	while ( N-- )
	{
		sum=0;
		scanf("%d",&n);
	//	for ( i=0; i<=n; ++i ) k[i] = 1;
		for ( i=0; i<n; ++i )
		{
			scanf("%d %d",&num[i].x,&num[i].y); 
		}
		sort(num,num+n,cmp); 
	
	//	solve_dp();  动规解法
	
		/*贪心解法*/ 
		for ( i=0; i<n; ++i )
		{
			if ( num[i].y )
			{
				sum++;
				temp = num[i].y;
				num[i].y = 0;
				for ( j=i+1; j<n; ++j )
				{
					if ( num[j].y>=temp )
					{
						temp = num[j].y;
						num[j].y = 0;
					}
				}
			}
		}
		printf("%d\n",sum);
	}
	return 0;	
} 
