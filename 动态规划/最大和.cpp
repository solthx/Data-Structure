/*
	��Ŀ����:
		��һ�����������������Ӿ���
	����:
		����Ӵ��ı���
		��������Ӿ����ڵ�i�е���j��
		��ô�;��� ��i��Ԫ�ص���j��Ԫ�صĺ͵�����Ӵ��� 
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
		for ( i=0; i<=y-1; ++i )  //����i 
		{
			for ( j=i+1; j<=y; ++j )
			{
				MAX = max( MAX,Cal(j,i,x) );  //����i+1�е���j�е�����Ӿ���� 
			}
		}
		printf("%d\n",MAX);
	}
	return 0;
}
