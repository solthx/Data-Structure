# include <iostream>
# include <string.h>
# include <iomanip>
# include <queue>
# define Num 10005
# define Inf 0x3f3f3f3f
using namespace std;

int g[Num][Num],n,m;
bool visit[Num];

double BFS( int x ){
    for ( int i=1; i<=n; ++i ) visit[i] = false;
    queue<int> q;
    int cnt=0,cur,last=-1,last_=x;
    int depth = 7;
    visit[x] = true;
    q.push(x);
    while( !q.empty() ){
        cur = q.front();
        q.pop();
        for ( int i=1; i<=n; ++i ){
            if ( !visit[i] && g[cur][i]<Inf ){
                visit[i] = true;
                last = i;
                q.push(i);
            }
        }
        cnt++;
        if ( cur == last_ ){
            last_ = last;
            if ( --depth==0 ) break;
        }
    }
    return 100.0*cnt/n;
}

int main(void){
    int v,u;
    cin>>n>>m;
    for ( int i=1; i<=n; ++i )
      for ( int j=1; j<=n; ++j )
        g[i][j] = Inf;
    for ( int i=0; i<m; ++i ){
        cin>>v>>u;
        g[v][u] = 1;
        g[u][v] = 1;
    }
    
    for ( int i=1; i<=n; ++i )
        cout<<i<<": "<<setprecision(2)<<fixed<<BFS(i)<<"\%"<<endl;
    return 0;
}