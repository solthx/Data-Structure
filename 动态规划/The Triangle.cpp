# include <cstdio>
# include <algorithm>
# include <iostream>
using namespace std;
int num[101][101];

int main(void)
{
	int i,j,n;
	scanf("%d",&n);
	for ( i=1; i<=n; ++i )
		for ( j=1; j<=i; ++j ){
			scanf("%d",&num[i][j]);
			num[i][j] += max( num[i-1][j],num[i-1][j-1] );
		}
	printf("%d\n",*max_element(num[n],num[n]+n));				
	return 0;
} 
