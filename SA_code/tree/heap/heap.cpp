# include <iostream>
# define Num 10000
# define Inf 0x3f3f3f3f
using namespace std;

int heap[Num][2];
int key[Num];
int cnt,N;

void Insert(int val){
    int x = ++cnt;
    if ( x>=Num ) return ;
    key[x] = val;
    int cur = x;
    int pre = cur/2;
    int tmp = key[x];
    while( key[pre]<tmp ){
        key[cur] = key[pre];
        cur = pre;
        pre /= 2;
    }
    key[cur] = tmp;
}

int pop_heap(){
    int x = cnt--;
    int ans = key[1];
    key[1] = key[cnt+1];
    //push_down
    int cur = 1,left,right;
    int tmp_key,tmp_idx;
    while( 1 ){
        left = 2*cur;
        right = left+1;
        //左孩子比自己大
        tmp_key = key[cur];
        tmp_idx = cur;
        if ( left<=cnt && key[left]>tmp_key ){
            tmp_key = key[left];
            tmp_idx = left;
        }
        if ( right<=cnt && key[right]>tmp_key ){
            tmp_key = key[right];
            tmp_idx = right;
        }
        if ( cur!=tmp_idx && key[cur]!=tmp_key ){
            int t = key[cur];
            key[cur] = tmp_key;
            cur = tmp_idx;
            key[cur] = t;
        }else break;
    }
    return ans;
}
 
int main(void){
    cin>>N;
    key[0] = Inf;
    for ( int i=0; i<N; ++i ){
        int t;
        cin>>t;
        Insert(t);
    }
    for ( int i=1; i<=N; ++i ){
        cout<<key[i]<<' ';
    }
    cout<<endl<<endl;
    while( cnt ){
        cout<<pop_heap()<<' ';
    }
    return 0;
}