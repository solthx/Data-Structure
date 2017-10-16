# include <iostream>
# include <queue>
# define Num 10000
# define Inf 0x3f3f3f3f
using namespace std;

typedef struct {
    int degree;
    int earliest_time;
    int latest_time;
}Vertex;

Vertex vex[Num];

int d[Num];
int num[Num][Num];
int n,m;
bool visited[Num];

void Init(){
    int v,w,u;
    cin>>n>>m;
    for ( int i=1; i<=n; ++i ){
        vex[i].degree = 0;
        vex[i].earliest_time = 0;
        vex[i].latest_time = Inf;
        visited[i] = false;
        d[u]=0;
        for ( int j=1; j<=n; ++j ){
            num[i][j] = Inf;
        }
    }
    for ( int i=0; i<m; ++i ){
        cin>>v>>u>>w;
        num[v][u] = w;
        vex[u].degree++;
        d[u]++;
    }
}

int Forward(){
    queue<int> q;
    int cur,ans=0;
    for ( int i=1; i<=n; ++i ){
        if ( !vex[i].degree ){
            q.push(i);
            visited[i] = true;
        }
    }
    if ( q.empty() ) return 0;
    while( !q.empty() ){
        cur = q.front();
        ans = cur;
        q.pop();
        for ( int i=1; i<=n; ++i ){
            if ( num[cur][i]<Inf && !visited[i] ){
                if (vex[i].earliest_time<vex[cur].earliest_time+num[cur][i])
                    vex[i].earliest_time=vex[cur].earliest_time+num[cur][i];
                if (!(--vex[i].degree)){
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
    }
    return ans;
}

void Backward(int x){
    queue<int> q;
    int cur,last;
    if ( !x ){
        cout<<0<<endl;
        return ;
    }
    vex[x].latest_time = vex[x].earliest_time;
    q.push(x);
    while( !q.empty() ){
        cur = q.front();
        q.pop();
        for ( int i=1; i<=n; ++i ){
            if ( num[i][cur]<Inf ){
                if ( vex[i].latest_time>vex[cur].latest_time - num[i][cur] )
                    vex[i].latest_time = vex[cur].latest_time - num[i][cur];
                q.push(i);
            }
        }
        last = cur;
    }
    //Print path
    cout<<vex[x].earliest_time<<endl;
    /*q.push(last);
    visited[last] = false;
    while( !q.empty() ){
        cur = q.front();
        q.pop();
        for ( int i=n; i>=0; --i ){
            if ( num[cur][i]<Inf && visited[i] ){
                if ( vex[i].latest_time-vex[cur].earliest_time-num[cur][i]<=0 )
                    cout<<cur<<"->"<<i<<endl;
                if ( !(--d[i]) ){
                    q.push(i);
                    visited[i] = false;
                }
            }
        }
    }*/
    for ( int i=1; i<=n; ++i ){
        cout<<"i:"<<i<<",,,e:"<<vex[i].earliest_time<<",,latest:"<<vex[i].latest_time<<endl;
    }
}

int main(void){
    int last_vex;
    Init();
    last_vex = Forward();
    Backward(last_vex);
    return 0;
}