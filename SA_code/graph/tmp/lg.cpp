# include <iostream>
# include <string.h>
# define Num 1000
# include <queue>
using namespace std;

typedef struct ll{
    int v;
    int u;
    int w;
    int next;
}Edge;

Edge num[Num];
int head[Num],cnt,M;

bool visit[Num];

queue<int> q;
/*插头法
插进来的第i条边，以v[i]为起始点，u[i]为指向的点，w[i]为权重
为了把这条新边插到以v[i]为首的链表里，
先把新边的next更新成以v[i]为首的第一条边，
再改变以v[i]为节点的第一条边
*/

//num[cnt]是边，cnt是边的序号
void Add(int v,int u,int w){
    num[cnt].v = v;     //指出的节点
    num[cnt].w = w;     //边的权重
    num[cnt].u = u;     //被指向的节点
    num[cnt].next = head[v];    //下一条边的idx 
    head[v] = cnt++;    //更新头节点（也就是更新成本边的idx
}

void Visit(int l,int r){
    if ( l==r ) return ;
    int k;
    for ( int i=l; i<=r; ++i ){
        k = head[i];
        while( k!=-1 ){
            cout<<num[k].u<<' ';
            k = num[k].next;
        }
    }
}

void DFS(int x){
    cout<<x<<' ';
    visit[x] = true;
    int e = head[x];
    while( e!=-1 ){
        if ( !visit[num[e].u] ){
            DFS(num[e].u);
        }
        e = num[e].next;
    }
    
    //cout<<num[e].v<<' ';
    //Visit(0,x-1);
    //Visit(x,M-1);
}

void BFS(int x){
    q.push(x);
    visit[x] = true;
    int e=head[x];
    cout<<num[x].v<<' ';
    while( q.empty() ){
        while(e!=-1){
            if ( !visit[num[e].u] ){
                visit[num[e].u] = true;
                cout<<num[e].u<<' ';
                q.push(num[e].u);
            }
        }
    }
}

int main(void){
    int N,v,w,u;
    cin>>N>>M;
    memset(head,-1,sizeof(head));
    for ( int i=1; i<=M; ++i ){
        cin>>v>>u>>w;
        Add(v,u,w);
        Add(u,v,w);
    }

    cout<<"DFS:\n";
    DFS(2);
    memset(visit,false,sizeof(visit));
    cout<<"\nBFS:\n";
    BFS(1);
    return 0;
}

