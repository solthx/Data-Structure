# include <iostream>
# include <algorithm>
# define Num 10000
using namespace std;

int pre[Num];     //记录父节点
int ch[Num][2];   //树 ch[index][which] which=0 是左孩子，1是右孩子
int value[Num];   //记录value  
int root;       //记录树根
int cnt;        //记录节点的index

int get(int r){
    return ch[pre[r]][1]==r; //如果是左孩子，则返回1. 右孩子返回0
}

int NewNode(int father,int val){
    int x = ++cnt;
    value[x] = val;
    pre[x] = father;
    ch[x][0] = ch[x][1] = 0;
    return x;
}

void Rotate(int x){
    int y = pre[x];
    int which = get(x);
    ch[y][which] = ch[x][which^1]; 
    pre[ch[x][which^1]] = y;
    int z = pre[y];
    if ( z ){
        ch[z][get(y)] = x;
    }
    pre[x] = z;
    pre[y] = x;
    ch[x][which^1] = y;
}

int Splay(int x){
    for ( int father; father=pre[x]; Rotate(x) )
        if ( pre[father] )
            Rotate(get(x)==get(father)?father:x);
    return x; 
}

int Insert(int val){
    int r = root;
    while( ch[r][val>value[r]] ){
        if ( val==value[r] ){
            return Splay(r);
        }
        r = ch[r][val>value[r]];
    }
    if ( val==value[r] ){
        return Splay(r);
    }
    ch[r][val>value[r]] = NewNode(r,val);
    int t =  Splay(ch[r][val>value[r]]);
    return t;
}

void traverse(int r){
    if ( r ){
        cout<<value[r]<<' ';
        traverse(ch[r][0]);
        traverse(ch[r][1]);
    }
}

int Findmax(int x){
    if (x){
        while( ch[x][1] ){
            x = ch[x][1];
        }
        return Splay(x);
    }
    return root;
}

int Delete(int val){
    int r = root;
    //找到要删除的目标
    while( ch[r][val>value[r]] ){
        if ( value[r]==val ) break;
        r = ch[r][val>value[r]];
    }
    //没找到
    if ( value[r]!=val ) return root;
    //删除找到的目标，并合并左右子树
    root = Splay(r);
    //没有左子树
    if ( !ch[r][0] ) return ch[r][1];
    //有左子树
    int right_tree_root = ch[r][1];
    pre[ch[r][0]] = 0;
    //找到左子树的最大值（这样它就没有右孩子了
    int left_tree_root = Findmax(ch[r][0]);
    //换“父”换“孩子”
    ch[left_tree_root][1] = right_tree_root;
    pre[right_tree_root] = left_tree_root;
    return left_tree_root;  
}

int main(void){
    int n,node_val;
    pre[0]=0;
    cout<<"输入节点数："<<endl;
    cin>>n;
    cout<<"输入节点值："<<endl;
    for ( int i=0; i<n; ++i ){
        cin>>node_val;
        if ( i==0 ){
            root = NewNode(0,node_val);
        }
        else{
            root = Insert(node_val);
        }
    }
    traverse(root);
    cout<<"\n输入要删除的值:"<<endl;
    int t;
    cin>>t;
    root = Delete(t);
    cout<<endl;
    traverse(root);
    return 0;
}