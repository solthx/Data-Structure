/*
	给一个矩阵 ，输出满足下列条件和的最大值:
		若取了(x,y)，那么(x+1,y) (x-1,y) (x,y+1) (x,y-1)都不能取 
	
	分析:
		第一次自己想的方法是 先把矩阵存入num中，
		计算满足在当前行不相邻的条件下的最大和，每次更新num[i]
		然后每行的最后一个元素就是当前行的最大不相邻元素和
		然后在计算每行最后一个元素组成的最大不相邻元素和 
		 最后num[Y][X]就是总的最大和
		 自己写的白痴代码在 吃土豆(白痴解法).cpp里 
		 
		 然后网上大牛的解法：
		 	有了一个计算最大不相邻元素和的状态转移方程
			 f[i][j] = max(f[i][j-2],f[i][j-3]);  
			f[i][j]存的是在第i行的前j-2个元素的最大不相邻和；
			但我们要的是前j个最大和啊！ 
			因此只要多计算两次就能解决问题了 
			下面是看完大神思路后写的代码 
			
*/ 

# include <stdio.h>
# include <string.h>
# define max(a,b) a>b?a:b
 
int num[509][509];

int main(void)
{
	int X,Y,i,j,len,k;
	while (~scanf("%d %d",&Y,&X)){
	memset(num,0,sizeof(num));
	for ( i=1; i<=Y; ++i ){
		for ( j=1; j<=X; ++j )
			scanf("%d",&num[i][j]);
	}
	int Col,n=X; 
	for ( i=1; i<=Y+2; ++i )
	{
		for ( j=3; j<=X+2; ++j )
			num[i][j] += max(num[i][j-2],num[i][j-3]);	
	}
	for ( i=3; i<=Y+2; ++i )
	{
		num[i][X+2] += max( num[i-2][X+2],num[i-3][X+2] );
	}
	printf("%d\n",num[Y+2][X+2]); 	
}
	return 0;
} 
