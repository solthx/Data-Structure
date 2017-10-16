# include <iostream>
# include <queue>
# define Num 100
# define Inf 0x3f3f3f3f
using namespace std;

int g[Num][Num];
bool visit[Num];
queue<int> q;
int N,E;

void BFS(int x){
    int cur=x;
    visit[x] = true;
    q.push(x);
    while( !q.empty() ){
        cur = q.front();
        cout<<cur<<' ';
        q.pop();
        for ( int i=1; i<=N; ++i ){
            if ( i!=cur && g[cur][i]<Inf && !visit[i] ){
                visit[i]=true;
                q.push(i);
            }
        }
    }
}

void DFS(int x){
    int cur = x;
    cout<<cur<<' ';
    visit[cur] = true;
    for ( int i=1; i<=N; ++i ){
        if ( cur!=i && !visit[i] && g[cur][i]<Inf ){
            visit[i] = true;
            DFS(i);
        }
    }
}

int main(void){
    cout<<"输入节点数和边数:"<<endl;
    cin>>N>>E;
    for ( int i=0; i<=N; ++i ){
        visit[i] = false;
        for ( int j=0; j<=N; ++j )
            g[i][j] = Inf;
    }
    for ( int i=0; i<E; i++ ){
        int n,v,w;
        cout<<"输入格式：节点1 节点2 权重\n";
        cin>>n>>v>>w;
        g[n][v] = w;
        g[v][n] = w;
    }
    cout<<"BFS:\n";
    BFS(3);
    for ( int i=0; i<=N; ++i ) visit[i] = false;
    cout<<"\nDFS:\n";
    DFS(3);
    return 0;
}