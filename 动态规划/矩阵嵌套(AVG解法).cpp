# include <cstdio>
# include <iostream>
# include <queue>
using namespace std;
# define INF 0x3f3f3f3f
typedef struct{
	int x;
	int y;
}ll;

int max(int a,int b)
{
	return a>b?a:b;
}

int num[1001][1001];
ll a[1001];
int book[1001];

bool OK( int i,int j )
{
	if ( (a[i].x>a[j].x && a[i].y>a[j].y) || (a[i].x>a[j].y && a[i].y>a[j].x) )
		return true;
	return false;
}

int Dijkstra(int n)
{
	queue<int> que;
	int Indegree[n+1],V,dis[n+1],i,j,v,w;
	for ( i=1; i<=n ;++i ){
		Indegree[i]=0;
		dis[i]=-INF;  
	} 
	for ( i=1; i<=n; ++i )
		for ( j=1; j<=n; ++j ) 
		if ( num[i][j]==1 ) Indegree[j]++;
	for ( i=1; i<=n; ++i )
		if ( !Indegree[i] ){
			que.push(i);
			dis[i] = 0;
		}
	int cur,MAX=0;
	while ( !que.empty() )
	{
		cur = que.front();
		que.pop();
		for ( i=1; i<=n; ++i )
		{
			if ( num[cur][i]<INF && num[cur][i]!=0 )
			{
				if ( !--Indegree[i]  )
					que.push(i);
			 	dis[i] = max( dis[i],dis[cur]+num[cur][i] );
				MAX = max(MAX,dis[i]);
			}
		}
	}
	return MAX+1;
}

int main(void)
{
	int N,n,i,j;
	scanf("%d",&N);
	while ( N-- )
	{
		scanf("%d",&n);
		for ( i=1; i<=n; ++i )
		{
			scanf("%d %d",&a[i].x,&a[i].y);
		}
		for ( i=1; i<=n; ++i )
		{
			for ( j=1; j<=n; ++j )
				if ( i==j ) num[i][j] = 0;
				else{
					if ( OK(j,i) ) num[i][j] = 1;  
					else num[i][j] = INF;
				}
		}
		int length = -1;
		length = Dijkstra(n);
		
		printf("%d\n",length);
	}
	return 0;
}
