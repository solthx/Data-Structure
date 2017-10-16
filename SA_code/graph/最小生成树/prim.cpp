# include <iostream>
# define Num 10000
# define Inf 0x3f3f3f3f
using namespace std;

int g[Num+1][Num+1],n,m;
int dis[Num+1];
bool visited[Num+1];

void Init(){
    for ( int i=1; i<=n; ++i ){
        dis[i] = Inf;
        visited[i] = false;
        for ( int j=1; j<=n; ++j ){
            g[i][j] = Inf;
        }
    } 
    int v,w,u;
    for ( int i=1; i<=m ; ++i ){
        cin>>v>>u>>w;
        g[v][u] = w;
        g[u][v] = w;
    }
}

int prim(int x){
    int load_=0;
    int e,min_,cnt=1;
    dis[x] = 0;
    visited[x] = true;
    for ( int i=1; i<=n; ++i )
        dis[i] = (g[x][i]<Inf)?g[x][i]:Inf;
    while( 1 ){
        e = -1;
        min_ = Inf;
        for ( int i=1; i<=n; ++i ){
            if ( dis[i]<min_ && !visited[i] ){
                min_ = dis[i];
                e = i;
            }
        }
        if ( e==-1 ) break;
        load_ += dis[e];
        cnt++;
        visited[e] = true;
        //warning！！因为是记录的点到树的距离，所以在树里的点到树的距离为0！！！
        dis[e]=0;
        for ( int i=1; i<=n; ++i ){
            if ( !visited[i] && g[e][i]<Inf ){
                int new_dis = dis[e] + g[e][i];
                dis[i] = (dis[i]>new_dis)?new_dis:dis[i];
            }
        }
    }
    if ( cnt<n ) return -1;
    return load_;
}

int main(void){
    cin>>n>>m;
    Init();
    cout<<prim(1)<<endl;
    return 0;
}