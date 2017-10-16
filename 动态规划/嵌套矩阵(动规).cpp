 # include <cstdio>
# include <iostream>
# include <string.h>
# include <algorithm>
# define max(a,b) a>b?a:b
using namespace std;
typedef struct{
	int x;
	int y;
}ll;
int f[3001];
ll num[3001];
bool OK( ll a,ll b )
{
	if ( a.x>b.x && a.y>b.y )
		return true;
	else
		return false;
}

int cmp(ll a,ll b)
{
	if ( a.x!=b.x )
		return a.x<b.x;
	else
		return a.y<b.y;
}

int main(void)
{
	int m,n,T,i,j;
	scanf("%d",&T);
	while ( T-- )
	{
		scanf("%d",&n);
		for ( i=0; i<n; ++i )
		{
			scanf("%d %d",&num[i].x,&num[i].y);
			if ( num[i].x<num[i].y )
			{
				m = num[i].x;
				num[i].x = num[i].y;
				num[i].y = m;
			}
		}
		sort(num,num+n,cmp);
	//	for ( i=0; i<n; ++i )
		//	printf("---%d %d\n",num[i].x,num[i].y);
		memset(f,0,sizeof(f));
		for ( i=1; i<n; ++i )
			for ( j=0; j<i; ++j )
			{
				if (/* num[i].x>num[j].x && num[i].y>num[j].y*/OK(num[i],num[j]) )  //第二个可以放到第一个上 
				{
					f[i] = max( f[i],f[j]+1 );
				}		
			}		
		printf("%d\n",*max_element(f,f+n)+1);
	}
	return 0;
}        
