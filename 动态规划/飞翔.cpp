# include <cstdio>
# include <string.h>
# include <iostream>
# include <algorithm>
# define G 1.414213
using namespace std;
typedef struct {
	int x,y;
}ll;

ll a[1001];
int v[1001];

void Cal(int X,int Y,int n)
{
	int i,j,k;
//	memset(v,1,sizeof(v));
	v[0] = 1;
	for ( i=1; i<=n; ++i )
	{
		v[i] = 1;
		for ( j=1; j<i; ++j )
		{
			if ( a[i].x>a[j].x && a[i].y>a[j].y && v[i]<v[j]+1 )
				v[i] = v[j]+1;
		}
	}
	int len = *max_element(v+1,v+n+1);
	double ans = ((double)( X+Y )-len*(2-G))*100;
	printf("%.0lf\n",ans); 
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
	int n,X,Y,i,j;
	while ( ~scanf("%d %d %d",&X,&Y,&n) )
	{
		for ( i=1; i<=n; ++i )
			scanf("%d %d",&a[i].x,&a[i].y);
		sort(a+1,a+n+1,cmp);
		Cal(X,Y,n);
	}
	return 0;
}
