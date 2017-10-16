# include <iostream>
# include <vector>
# include <stack>
# include <cstdio>
using namespace std;

vector<int> pre_seq;    //前序遍历数组
vector<int> mid_seq;    //中序遍历数组
vector<int> ans;        //answer
int N;

struct ll{
    int val;        
    struct ll * left;
    struct ll * right;
};

//获得子树的root的index
int Getroot(int v,int start,int end){
    for ( int i=start; i<=end; ++i){
        if ( v==mid_seq[i] ){
            return i;
        }
    }
    return -1;
}


struct ll * Generate_tree(int pre_start,int mid_start,int mid_end){
    /*
        此函数是递归的创建子树
        pre_start : 前序遍历子树的起始点
        mid_start : 中序遍历子树的起始点
        mid_end   : 中序遍历子树的终点
    */
    
    //如果超过“最大树”的最大范围就return
    if (  mid_start<0 || mid_end>=mid_seq.size() || pre_start>=pre_seq.size() )
        return NULL;
    //初始化一个叶子节点
    struct ll * Node = new struct ll();
    Node->left = Node->right = NULL;
    Node->val = pre_seq[pre_start];
    //若是叶子节点则返回
    if (mid_start==mid_end ) return Node;
    //得到根节点在中序遍历数组中的位置
    int root_idx = Getroot(Node->val,mid_start,mid_end);
    //如果没在中序遍历数组中找到根节点的话，就说明当前节点不存在
    if (root_idx==-1 ) return NULL;
    //得到左子树节点数量，用来后面计算得到右子树的中序遍历起始点
    int left_nodes_number = (root_idx-mid_start)+1;
    //递归得到左右子树
    Node->left = Generate_tree(pre_start+1,mid_start,root_idx-1);
    Node->right = Generate_tree(pre_start+left_nodes_number,root_idx+1,mid_end);
    return Node;
}

//后序遍历
void Traverse(struct ll * node){
    if ( node!=NULL ){
        Traverse(node->left);
        Traverse(node->right);
        ans.push_back(node->val);
    }
    return;
}

int main(void){
    struct ll * root; 
    int idx;    //每个叶子节点的val
    string op="";  //operation
    stack<int> s;
    cin>>N;
    N *= 2;     //每一个push操作对应一个pop操作
    while( N-- ){
        cin>>op;
        if ( op[1]=='u' || op[1]=='U' ){
            cin>>idx;
            s.push(idx);
            pre_seq.push_back(idx);
        }else if ( !s.empty() && (op[1]=='o' || op[1]=='O' ) ){
            mid_seq.push_back(s.top());
            s.pop();
        }
    }
    root = Generate_tree(0,0,mid_seq.size()-1);
    Traverse(root);

    //print
    cout<<ans[0];
    for ( int i=1; i<ans.size(); ++i ){
        cout<<' '<<ans[i];
    }
    cout<<endl;
    return 0;
}