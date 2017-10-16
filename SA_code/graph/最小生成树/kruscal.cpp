# include <iostream>
# define Num 10000
# define Inf 0x3f3f3f3f
using namespace std;

typedef struct {
    int v;
    int u;
    int w;
    int next; 
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
    for ( int i=1; i<=m ; ++i ){
        cin>>v>>u>>w;
        Add(v,u,w);
        Add(u,v,w);
        visited[i]=false;
    }
}

int Find(int x){
    if ( set_[x]<0 ) return x;
    return set_[x] = Find(set_[x]);
}

bool Merge(int x,int y){
    int a = Find(x);
    int b = Find(y);
    if ( a==b ) return false;
    if ( a<b ){
        set_[a] += set_[b];
        set_[b] = a;
    }else{
        set_[b] += set_[a];
        set_[a] = b;    
    }
    return true;
}

int kruscal(){
    int ans=0;
    int t=0;
    while(1){
        int e=-1,min_=Inf;
        for ( int i=0; i<cnt; ++i ){
            if ( num[i].w<min_ && !visited[i] ){
                 
                 e = i;
                min_ = num[i].w;
            } 
        }  
        if ( e==-1 ) break;
        if (Merge(num[e].v,num[e].u)){
            ans += num[e].w;
            t++;
        }
        visited[e] = true;
        
    }
    if ( t<n-1  ) return -1;
    return ans;
}

int main(void){
    cin>>n>>m;
    for ( int i=1; i<=n; ++i ){
        head[i]=-1;
        set_[i]=-1;
    } 
    Init();
    cout<<kruscal()<<endl;
    return 0;
}