# include <iostream>
# include <algorithm>
# include <vector>
# include <cmath>
# include <queue>
# define Num 100000
using namespace std;

int tree[Num][2];
int key[Num];
int root,cnt;
int b[Num],N;
vector<int> v;
int ans[Num];

//生成一棵树
//root=1
//根节点是i,左孩子是2*i,右孩子是2*i+1
int Generate(int x){
    if ( 2*x<=N )
        tree[x][0] = Generate(2*x);
    else tree[x][0] = 0;
    if ( 2*x+1<=N )
        tree[x][1] = Generate(2*x+1);
    else tree[x][1] = 0;
    return x;
}

//获得前序遍历的下标，将其存入b数组
void pre_tra(int x){
    if ( x ){
        pre_tra(tree[x][0]);
        b[cnt++] = x;
        pre_tra(tree[x][1]);
    }
}

int main(void){
    int t,n;
    cin>>N;
    n = N;
    while( n-- ){
        cin>>t;
        v.push_back(t);
    }
    //排序后，我们就得到了cbt的前序遍历
    sort(v.begin(),v.end());
    //生成一个左右孩子的idx分别为2*i,2*i+1的树
    root = Generate(1);
    //将这个树前序遍历一下，得到下标
    pre_tra(root);
    //我们得到了树的value的前序遍历v 和 树下标的前序遍历b
    //所以我们的结果就是ans[b[i]]=v[i]
    for ( int i=0; i<cnt; ++i ){
        ans[b[i]] = v[i];
    }
    //根是从1开始的
    cout<<ans[1];
    for ( int i=2; i<=N; ++i ){
        cout<<" "<<ans[i];
    }
    return 0;
}