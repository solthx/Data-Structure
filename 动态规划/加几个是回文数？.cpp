/*
描述
所谓回文字符串，就是一个字符串，从左到右读和从右到左读是完全一样的，比如"aba"。当然，我们给你的问题不会再简单到判断一个字符串是不是回文字符串。现在要求你，给你一个字符串，可在任意位置添加字符，最少再添加几个字符，可以使这个字符串成为回文字符串。
输入
第一行给出整数N（0<N<100）
接下来的N行，每行一个字符串，每个字符串长度不超过1000.
输出
每行输出所需添加的最少字符数

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
