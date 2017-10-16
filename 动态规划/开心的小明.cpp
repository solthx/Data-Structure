# include <stdio.h>
# include <string.h>
# define max(a,b) a>b?a:b 
int dp[30001],price[30001],v[30001];

int main(void)
{
	int N,n,i,j,k,V;
	scanf("%d",&N);
	while ( N-- )
	{
		memset(dp,0,sizeof(dp));
		scanf("%d %d",&V,&n);
		for ( i=1; i<=n; ++i )
			scanf("%d %d",&price[i],&v[i]);
		for ( i=1; i<=n; ++i )
		{
			for ( j=V; j>=price[i]; j-- )
				dp[j] = max( dp[j],dp[j-price[i]]+price[i]*v[i] );
		}
		printf("%d\n",dp[V]);
	}
	return 0;
} 
