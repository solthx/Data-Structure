# include <stdio.h>
# include <string.h>
# define min(a,b) a<b?a:b
int num[201];
int sum[201];
int f[201][201];

int main(void)
{
	int n,r,i,j,k,start,end;
	while ( ~scanf("%d",&n) )
	{
		memset(sum,0,sizeof(sum));
		for ( i=1; i<=n; ++i ){
			scanf("%d",num+i);
			sum[i] = sum[i-1]+num[i];
		}
		for ( r=2; r<=n; ++r )   //���䳤��   
		{
			for ( start=1; start<=n-r+1; ++start )  //��ʼλ�� 
			{
				end = start+r-1;   //����λ�� 
				f[start][end] = 0x3f3f3f3f;  //�ȳ�ʼ����������  ��Ϊ����Ҫȡ��Сֵ 
				for ( k=start; k<end; ++k )  //�ϵ�λ�� 
					f[start][end] = min(f[start][k]+f[k+1][end]+sum[end]-sum[start-1],f[start][end]);
			}	
		} 
		printf("%d\n",f[1][n]);
	}
	return 0;
} 
