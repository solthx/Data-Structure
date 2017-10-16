# include <iostream>
# include <string.h>
# include <queue>
# define Num 10000
# define Inf 0x3f3f3f3f
using namespace std;

int g[Num][Num];
int dis[Num],path[Num];
int n,m;
queue<int> q;

void BFS(int x){
    dis[x] = 0;
    q.push(x);
    while( !q.empty() ){
        int z = q.front();
        q.pop();
        for ( int i=1; i<=n; ++i ){
            if ( dis[i]==-1 && g[z][i]!=Inf ){
                dis[i] = dis[z] + 1;
                path[i] = z;
                q.push(i);
            }
        }
    }
}

void Printpath(int x){
    if ( x==-1 ) return;
    Printpath(path[x]);
    cout<<x<<' ';    
}

int main(void){
    int u,v,w,N,M;
    cin>>n>>m;
    for ( int i=0; i<Num; i++ )
        for ( int j=0; j<Num; ++j)
            g[i][j] = Inf;
    for ( int i=0; i<m; ++i ){
        cin>>v>>u>>w;
        g[v][u] = w;
        g[u][v] = w;
    }
    
    memset(path,-1,sizeof(path));
    memset(dis,-1,sizeof(dis));
    BFS(1);
    
    int a;
    cin>>a;
    if ( a<=n ){
        cout<<"\n>>"<<dis[a];
    }
    cout<<endl<<"path:";

    Printpath(a);

    return 0;
}