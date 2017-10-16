/*
描述
大家对拦截导弹那个题目应该比较熟悉了，我再叙述一下题意：某国为了防御敌国的导弹袭击，新研制出来一种导弹拦截系统。但是这种导弹拦截系统有一个缺陷：它的第一发炮弹能够到达任意的高度，但是以后每一发炮弹都不能超过前一发的高度。突然有一天，雷达捕捉到敌国的导弹来袭。由于该系统存在缺陷，所以如果想把所有的导弹都拦截下来，就要多准备几套这样的导弹拦截系统。但是由于该系统成本太高，所以为了降低成本，请你计算一下最少需要多少套拦截系统。
输入
有多组测试数据。
每组数据先输入一个整数N（N≤3000），代表有N发导弹来袭。接下来有N个数，分别代表依次飞来的导弹的导弹的高度。当N=-1时表示输入结束。
输出
每组输出数据占一行，表示最少需要多少套拦截系统。

*/ 

# include <stdio.h>

int num[3001],a[3001]; // a[i]里存每一个子序列的末尾元素大小（即最小值） 

int min(int a,int b)
{
	return a<b?a:b;
}

int Find(int val,int * len)  //二分查找  返回a[i]中第一个大于等于val的位置 这也保证了每次更新最优情况 若没找到则返回len+1 
{
	int left = 1,right = *len,mid;
	mid = (left+right)/2;
	while ( left<=right )
	{
		if ( a[mid]==val ) return mid;
		else if ( a[mid]>val ) right = mid-1;
		else left = mid + 1;
		mid = (left+right)/2;
	}
	if  ( left==*len+1)  //若没找到 也就是说val比数组里每个元素都大  这个时候必须再发射一个炮弹 
	{
			(*len)++;  //炮弹数加一 
			return *len;  
	}
	return left;
}

int main(void)
{
	int n,i,len,pos;
	while ( ~scanf("%d",&n) )
	{
		if ( n==-1 ) break;
		a[0] = 1;
		len=1;
		for ( i=1; i<=n; ++i ){
			scanf("%d",num+i);
			a[i]=1;
		}
		a[1] = num[1];  //第一个值一定是num[1] 
		for ( i=2; i<=n; ++i )
		{
			pos = Find(num[i],&len); // 若找到则更新某个子序列的最小值 ( 这里的某个子序列一定是某个尾元素和num[i]最接近的子序列 原因参见本函数的功能 ) 
			a[pos]=num[i];   
		}	
		printf("%d\n",len);
	}
	return 0;	
} 
