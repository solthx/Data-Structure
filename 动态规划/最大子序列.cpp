/*
	问题：
		描述
	咱们就不拐弯抹角了，如题，需要你做的就是写一个程序，得出最长公共子序列。
	tip：最长公共子序列也称作最长公共子串(不要求连续)，英文缩写为LCS（Longest Common Subsequence）。其定义是，一个序列 S ，如果分别是两个或多个已知序列的子序列，且是所有符合此条件序列中最长的，则 S 称为已知序列的最长公共子序列。
	输入
	第一行给出一个整数N(0<N<100)表示待测数据组数
	接下来每组数据两行，分别为待测的两组字符串。每个字符串长度不大于1000.
	输出
	每组测试数据输出一个整数，表示最长公共子序列长度。每组结果占一行。 
*/ 

# include <stdio.h>
# include <string.h>
# define max(a,b) a>b?a:b
int f[1001][1001]; //f[i][j]保存 a中前i个元素组成的序列 和 b中前j个元素组成的序列 的最长子序列 
int K[1001][1001]; //标记数组
char a[1001],b[1001];  
void Display(int i,int j,int len)  //逆序输出最长元素 
{
	if ( !i || !j )  return;  // 因为f从1开始，当到0时说明已经扫完 
	if ( K[i][j]==1 )  //若是1，则说明z[i]=a[i]=b[i] 直接输出当前字符 
	{ 
		printf("%c ",a[i-1]); /*f中是从1开始记录的，而字符串是从0开始的，所以输出时要减一*/
		len--;
		Display(i-1,j-1,len);
	}
	else if ( K[i][j]==2 ) //若是2，则说明a的第i个字符一定不存在于当前子序列  所以进行i-1，然后继续进行查找 
		Display(i-1,j,len);
	else 
	{
		if ( K[i][j]==3 )
			Display(i,j-1,len);
		else
			Display(i-1,j,len);
	}
}

int main(void)
{
	int T;
	scanf("%d",&T);
	while ( T-- ){
		scanf("%s %s",a,b);
		int i,j,m,n;
		memset(f,0,sizeof(f)); 
		for ( i=0; i<strlen(a); ++i )
		{
			for ( j=0; j<strlen(b); ++j )
			{
				if ( a[i]==b[j] )  //若a中第i个元素与b中第j个元素相同  那么此元素一定在子序列中 直接在f[i][j]的基础上加一 
				{
					f[i+1][j+1] = f[i][j]+1;
					K[i+1][j+1] = 1;
				}
				else if ( a[i]!=b[j] )  //若不相同，则需要判断是哪种情况  
				{
					f[i+1][j+1] = max( f[i][j+1],f[i+1][j] ); 
					if ( f[i][j+1]>f[i+1][j] )  //若f[i][j+1]比较大 说明a中第i+1个元素一定不在子序列中 换句话说就是目前为止的子序列们存在于a字符串的前i个或b字符串里的前j+1个    
						K[i+1][j+1] = 2;
					else  
						K[i+1][j+1] = 3;
				}
			}
		}
		// 输出f矩阵 
		for ( i=1; i<=strlen(a); ++i )
		{						
			for ( j=1; j<=strlen(b); ++j )
				printf("%d ",f[i][j]);
			printf("\n");
		}
		
		//输出最大子序列的长度 
		int len =  f[strlen(a)][strlen(b)];
		printf("%d\n",len);
		
		//最大子序列的逆序输出  
		Display(strlen(a),strlen(b),len);
	}
	return 0;
 } 
