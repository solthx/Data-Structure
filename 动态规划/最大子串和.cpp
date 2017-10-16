# include <stdio.h>
int main(void)
{
	int MAX,m,T,n,N,sum,c,i,end;
	int start,temp; 
	scanf("%d",&N);
	for( m=1; m<=N; ++m )
	{
		scanf("%d",&n);
		scanf("%d",&c);
		MAX = sum = c;
		start = temp=end = 1;
		for ( i=2; i<=n; ++i )
		{
			scanf("%d",&c);
			if ( sum<0 )
			{ 
				sum = c; //sum<0 则sum+c<c 直接把小于0的掐掉 
				temp = i;  // 因为前面的sum被掐掉了 所以接下来有可能从本节点开始的子串和会逆袭 MAX  所以先记录一下 
			}
			else sum += c;		//若sum>=0 则 sum+c >=c 给sum加上c 
 			if ( MAX<sum ) 
			{
				MAX =sum;   //找最大值 
		 		start = temp; //逆袭成功 更新初始位置
				end = i; 
			}
		}
		printf("Case %d:\n%d %d %d\n",m,MAX,start,end);
	//	printf("从%dth到%dth的子串和最大\n",start,end); 
	}
	return 0;
 } 

