# include <iostream>
# include <string.h>
# include <algorithm>
# include <queue>
# define Num 1000
# define Inf 0x3f3f3f3f
using namespace std;

int g[Num][Num],dis[Num],n,m,path[Num];
bool collected[Num];

void Init_dis(int x){
    for ( int i=1; i<=n; ++i )
        dis[i] = (g[x][i]<Inf)?g[x][i]:Inf;
    dis[x]=0;
}


/*Dijkstra算法：

假设：起始点是V，“已经是最短路径的集合”中的节点是S，“未收录集合中到V的距离最短的”节点是K

1、为什么能断言之后的节点在更新周围权重的时候，不会影响到“已经是最短路径的集合”中
的节点呢？
答：为了避免这个问题，所以才是以dis[i](起始点到第i个节点的距离)递增的顺序来将每一
个节点收录到这个“最短路径集合”中。 

首先我们要知道，在“最短路径”集合中的节点S是不可能被当前节点K影响到的，因为：
    如果影响到了的话，就说明V->K->S < V->S， 由于大前提是权重都是正的，所以
这也就说明了V->K<V->S，然而这与“以dis递增（非递减）顺序来收录”的假设条件不符。

所以，这也是Dijkstra算法不能解决负权边问题的原因，如果K->S是负的，
那么尽管V->K>V->S这个条件满足，但仍然有可能会V->K->S<V->S，这样就会
影响到“最短路径集合”中的节点，造成混乱。

*/

void Dijkstra(int x){
    Init_dis(x);
    memset(path,-1,sizeof(path));
    int e,min_=Inf,i;
    while( 1 ){
        min_ = Inf;
        e = -1;
        for ( i=1; i<=n; ++i )
            if ( dis[i]<min_ && !collected[i] ){
                e = i;
                min_ = dis[i];
            }
        collected[e] = true;
        if ( e==-1 ) break;
        for ( i=1; i<=n; ++i ){
            if ( !collected[i] && g[e][i]<Inf ){
                int new_dis = dis[e]+g[e][i];
                if ( dis[i]>new_dis ){
                    dis[i] = new_dis;
                    path[i] = e;
                }
            }
        }
    }
}

typedef pair<int,int> p;

struct cmp{
    bool operator()(p a,p b){
        return a.second>b.second;
    } 
};

priority_queue<p ,vector<p>, cmp > heap;
void Init_dis_heap(int x){
    for ( int i=1; i<=n; ++i )
    {
        if ( g[x][i]<Inf ){
            heap.push(make_pair(i,g[x][i]));
            dis[i] = g[x][i];
        }else{
            dis[i] = Inf;
        }
    }
    dis[x]=0;
}

void heap_Dijkstra(int x){
    Init_dis_heap(x);
    for ( int i=1; i<=n; ++i ){
        if ( g[x][i]<Inf ) heap.push(make_pair(i,g[x][i]));
    }
    //heap.push(make_pair(x,0));
    memset(path,-1,sizeof(path));
    p tmp;
    while( !heap.empty() ){
        tmp = heap.top();
        heap.pop();
        if ( collected[tmp.first] ) continue;
        tmp.second = true;
        for ( int i=1; i<=n; ++i ){
            if ( !collected[i] && g[tmp.first][i]<Inf ){
                int new_dis = dis[tmp.first] + g[tmp.first][i];
                if ( dis[i]>new_dis ){
                    heap.push(make_pair(i,new_dis));
                    dis[i] = new_dis;
                    path[i] = tmp.first;
                }
            }
        }
    }
}

void Print_path(int x){
    if ( x==-1 ) return ;
    Print_path(path[x]);
    cout<<x<<' ';
}

int main(void){
    int v,w,u;
    memset(collected,false,sizeof(collected));
    memset(g,Inf,sizeof(g));
    cout<<"输入节点数和边数：\n";
    cin>>n>>m;
    cout<<"输入节点：\n";
    for ( int i=0; i<m; ++i ){
        cin>>v>>u>>w;
        g[v][u] = w;
        g[u][v] = w;
    }
    cout<<"输入起始点：\n";
    cin>>v;
    //Dijkstra(v);
    heap_Dijkstra(v);
    cout<<"输入终点：\n";
    cin>>u;
    cout<<"最短距离："<<dis[u]<<endl;
    cout<<"\n最短路径:";
    cout<<v<<' ';
    Print_path(u);
    cout<<endl;
    return 0;
}