# include <iostream>
# include <vector>
# define Num 10001
# define Inf 0x3f3f3f3f
using namespace std;

int g[Num][Num],n,m,start;
bool visited[Num];

vector<int> ans;

void DFS(int x){
    int flag=0;
    ans.push_back(x);
    visited[x] = true;
    for ( int i=1; i<=n; ++i ){
        if ( g[x][i]<Inf && !visited[i] ){
            DFS(i);
            flag=1;
        }
        if ( flag ) ans.push_back(x);
        flag=0;
    }
    //if ( flag ) ans.push_back(x);
}

int main(void){
    int v,u;
    cin>>n>>m>>start;
    for ( int i=1; i<=n; ++i )
        for ( int j=1; j<=n; ++j )
            g[i][j] = Inf;
    for ( int i=1; i<=m; ++i ){
        cin>>v>>u;
        g[v][u] = 1;
        g[u][v] = 1;
    }
    DFS(start);
    int flag=0;
    for ( int i=1; i<=n; ++i ){
        if ( !visited[i] ){
            flag=1; break;
        }
    }
    cout<<ans[0];
    for ( int i=1; i<ans.size(); ++i)
        cout<<" "<<ans[i];
    /*for ( int i=ans.size()-2; i>=0; --i )
        cout<<" "<<ans[i];*/
    if ( flag ) cout<<" "<<0;
    return 0;
}