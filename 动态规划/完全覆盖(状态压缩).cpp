#include<cstdio>  
#include<cstring>  
#include<iostream>  
using namespace std;  
long long dp[13][1<<12+1]; 
int m,n;

bool FirstJudge(long long p)
{
	int i,j,k;
	for ( i=0; i<m; )
	{
		if ( p & (1<<i) ) //����iλ��1 
		{
			if (i==m-1)  
				return false;
			if ( !(p&(1<<(i+1)) ))
				return false;
			else
				i+=2;
		}
		else
			i++;
	}
	return true;
}

bool Judge(int pre,int now)
{
	int i,j,k;
	for ( i=0; i<m; )
	{
		if ( now & (1<<i) ) //��now��iλ��1 
		{
			if ( pre & (1<<i) ) //��pre��iλҲ��1  ��ôֻ���Ժ��ŷ� 
			{
				if ( (i==m-1) || !(now & (1<<(i+1))) || !(pre & (1<<(i+1))) ) //�������һ�� ���� ��һ����0 ����pre�ĺ�һ����0(���������i+1���ӱ���2��)  �򲻷��� 
					return false;
				else
					i+=2; 
			}
			else //pre�ĵ�iλ��0 
				i++; 
		}
		else //now�ĵ�iλ��0 
		{
			if ( !(pre & (1<<i)) ) //��preҲ��0 �϶����� 
				return false;
			else
				i++; 
		}
	}
	return true;
}

int main(void)
{
	int i,j,k;
	while ( ~scanf("%d %d",&n,&m) )
	{
		if ( !m && !n ) break;		
		if ( m&1 && n&1 )
		{
			printf("0\n");
			continue;
		}
		if ( n<m ) {
			 n^=m;
			 m^=n;
			 n^=m;
		}
		memset(dp,0,sizeof(dp));
		long long allstatus = (1<<m)-1; //s 1!!!!!
		for ( i=0; i<=allstatus; ++i )
			if ( FirstJudge(i) )
				dp[1][i] = 1;
		for ( i=2; i<=n; i++ )
		{
			for ( j=0; j<=allstatus; ++j ) //������һ�� 
				for ( k=0; k<=allstatus; ++k ) //������ 
					if ( Judge(k,j) ){
						dp[i][j] += dp[i-1][k];
				}
		}
		printf("%lld\n",dp[n][allstatus]);
	}
	return 0;	
} 
