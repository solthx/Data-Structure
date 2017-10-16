# include <iostream>
# include <queue>
# include <algorithm>
# define Num 10001
# define Inf 0x3f3f3f3f
using namespace std;

int g[Num][Num],dis[Num],price[Num][Num],path[Num],p[Num];
bool collected[Num];
int n,m;

void heap_dijkstra(int x){
    int new_dis;
    //Init
    for ( int i=0; i<n; ++i ){
        collected[i] = false;
        path[i] = -1;
        if ( i==x ){ 
            dis[i]=0;
            p[i]=0;
        }
        else if ( g[x][i]<Inf ){
            dis[i] = g[x][i];
            p[i] = price[x][i];
        }else{
            dis[i] = Inf;
            p[i] = Inf;
        }    
    }
    collected[x] = true;
    //dijkstra
    int min_,e;
    while(1){
        min_=Inf,e=-1;
        for ( int i=0; i<n; ++i ){
            if ( !collected[i] && dis[i]<min_ ){
                min_ = dis[i];
                e = i;
            }
        }
        if ( e==-1 ) break;
        collected[e] = true;
        for ( int i=0; i<n; ++i ){
            if ( !collected[i] && g[e][i]<Inf ){
                new_dis = g[e][i] + dis[e];
                if ( dis[i]>new_dis ){
                    //path[i] = e;
                    dis[i] = new_dis;
                    p[i] = p[e] + price[e][i];
                }else if ( dis[i]==new_dis ){
                    int new_price = p[e]+price[e][i];
                    if ( p[i]>new_price ){
                        //path[i] = e;
                        p[i] = new_price;
                    }
                }
            }
        }
    }

}


int main(void){
    int v,w,u,pp,i,j;
    int start,end;
    cin>>n>>m>>start>>end;
    for ( i=0; i<n; ++i )
        for ( j=0; j<n; ++j )
        {    
            g[i][j] = Inf;
            price[i][j] = Inf;
        }
    for ( i=0; i<m; ++i ){
        cin>>v>>u>>w>>pp;
        g[v][u] = w;
        g[u][v] = w;
        price[u][v] = pp;
        price[v][u] = pp;
    }
    heap_dijkstra(start);
    //cout<<"~~";
    cout<<dis[end]<<' '<<p[end]<<endl;
    return 0;
}