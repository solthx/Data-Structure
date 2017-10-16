/*  2017年10月10日 22:40

    spfa的实现就是： 开一个队列，里面存节点，遍历节点的邻接点，如果邻接点i的visited是false并且dis
    可以被更新更小，那么就更新其dis并且把这个被更新dis的邻接点丢进队列里，当队列为空时跳出循环。
    最终的dis里就是最短距离的数组了
*/
# include <iostream>
# include <queue>
# define Num 100
# define Inf 0x3f3f3f3f
using namespace std;

typedef struct{
    int v,w,u,next;
}Edge;

int n,m;
int cnt=0;
int dis[Num+1],head[Num+1];
int set_[Num+1];
bool visited[Num+1];
Edge num[Num+1];


void Add(int v,int u,int w){
    num[cnt].v = v;
    num[cnt].w = w;  
    num[cnt].u = u;
    num[cnt].next = head[v];
    head[v] = cnt++;
}

void Init(){
    int v,w,u;
    cin>>n>>m;
    for ( int i=1; i<=n; ++i ){
        head[i]=-1;
        dis[i]=Inf;
    }    
    for ( int i=1; i<=m ; ++i ){
        cin>>v>>u>>w;
        Add(v,u,w);
        Add(u,v,w);
        visited[i]=false;
    }
}

int spfa(int x,int y){
    queue<int> q;
    dis[x]=0;
    q.push(x);
    visited[x] = true;
    while( !q.empty() ){
        int cur_v = q.front();
        q.pop();
        visited[cur_v] = false;
        int cur_e = head[cur_v];
        while( cur_e!=-1 ){
            if ( !visited[num[cur_e].u] && dis[num[cur_e].u]>dis[num[cur_e].v] + num[cur_e].w)
            {
                dis[num[cur_e].u]=dis[num[cur_e].v] + num[cur_e].w;
                q.push(num[cur_e].u);
                visited[num[cur_e].u]=true;
            }
            cur_e = num[cur_e].next;
        }
    }
    return dis[y];
}

int main(void){
    Init();
    cout<<spfa(1,5);
    return 0;
}




/* 邻接矩阵实现
int g[Num][Num];
int dis[Num];
bool visit[Num];
queue<int> q;
int N,E;

int spfa(int t){
    int cur,new_dis,x=1;
    for( int i=1; i<=N; ++i ){
        dis[i] = Inf;
    }
    dis[x]=0;
    q.push(x);
    visit[x] = true;
    while(!q.empty()){
        cur = q.front();
        q.pop();
        
        for( int i=1; i<=N; ++i ){
            if ( g[cur][i] < Inf && dis[i]>dis[cur]+g[cur][i]  ){
                dis[i]=dis[cur]+g[cur][i];
                if ( !visit[i] ){
                    q.push(i);
                    visit[i]=true;
                }
            }
        }
        visit[cur]=false;
    }
    return dis[t];
}

int main(void){
    cout<<"输入节点数和边数:"<<endl;
    cin>>N>>E;
    for ( int i=1; i<=N; ++i ){
        visit[i] = false;
        for ( int j=1; j<=N; ++j )
            g[i][j] = Inf;
    }
    for ( int i=0; i<E; i++ ){
        int n,v,w;
        cout<<"输入格式：节点1 节点2 权重\n";
        cin>>n>>v>>w;
        g[n][v] = w;
        g[v][n] = w;
    }

    cout<<spfa(5);
    return 0;
}*/