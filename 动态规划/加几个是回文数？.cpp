/*
����
��ν�����ַ���������һ���ַ����������Ҷ��ʹ��ҵ��������ȫһ���ģ�����"aba"����Ȼ�����Ǹ�������ⲻ���ټ򵥵��ж�һ���ַ����ǲ��ǻ����ַ���������Ҫ���㣬����һ���ַ�������������λ������ַ�����������Ӽ����ַ�������ʹ����ַ�����Ϊ�����ַ�����
����
��һ�и�������N��0<N<100��
��������N�У�ÿ��һ���ַ�����ÿ���ַ������Ȳ�����1000.
���
ÿ�����������ӵ������ַ���

*/ 

# include <stdio.h>
# include <string.h>
# define min(a,b) a<b?a:b
int f[1001][1001];
char ch[1001];

int main(void)
{
	int N,start,j,end;
	scanf("%d",&N);
	while ( N-- )
	{
		scanf("%s",ch);
		int i,j,len = strlen(ch);
		for ( i=0; i<=len; ++i )
			for ( j=0; j<=len; ++j )
				f[i][j] = 0;
		for ( i=2; i<=len; ++i )
		{
			for ( start=0; start<len-i+1; ++start )
			{
				end = start+i-1;
				if ( ch[end]==ch[start] )
				{
					f[start][end] = f[start+1][end-1];
				}
				else
				{
					f[start][end] = min(f[start][end-1]+1,f[start+1][end]+1);
				}
			}
			
		}
		printf("%d\n",f[0][len-1]);
	}
	return 0;	
} 
