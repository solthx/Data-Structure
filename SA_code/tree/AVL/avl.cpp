# include <iostream>
# include <algorithm>
# include <vector>
# include <stack>
using namespace std;

struct avl{
    avl(int a){
        val = a;
        height = 0;
        left = NULL;
        right = NULL;
    }
    int val;
    int height;
    struct avl * left;
    struct avl * right;
};

int Getheight(struct avl * T){
    if ( T!=NULL ) 
        return T->height;
    return -1;
}

struct avl * RR(struct avl * T){
    struct avl * right_child;
    right_child = T->right;
    
    T->right = right_child->left;
    right_child->left = T;
    T->height = max(Getheight(T->left),Getheight(T->right)) + 1;
    right_child->height = max(Getheight(right_child->right),Getheight(T)) + 1;
    return right_child;
}

struct avl * LL(struct avl * T){
    struct avl * left_child;
    left_child = T->left;
    T->left = left_child->right;
    left_child->right = T;
    T->height = max(Getheight(T->left),Getheight(T->right)) + 1;
    left_child->height = max(Getheight(left_child->left),Getheight(T)) + 1;
    return left_child;
}

struct avl * RL(struct avl * T){
    T->right = LL(T->right);
    return RR(T);
}

struct avl * LR(struct avl * T){
    T->left = RR(T->left);
    return LL(T);
}

struct avl * Insert(struct avl * T, int e){
    if ( T==NULL ){
        struct avl * Node = new struct avl(e);
        //cout<<"OK"<<endl;
        return Node;
    }else{
        if ( e>T->val ){
            //插进右子树
            T->right = Insert(T->right,e);
            //不平衡了
            if ( Getheight(T->left) - Getheight(T->right) == -2 ){
                if ( e>T->right->val ){
                    
                    T = RR(T);
                }else if ( e<T->right->val ){
                    T = RL(T);
                }
            }
        }else if (e<T->val){
            T->left = Insert(T->left,e);
            if ( Getheight(T->left) - Getheight(T->right) == 2 ){
                if (e < T->left->val ){
                    T = LL(T);
                }else if ( e>T->left->val ){
                    T = LR(T);
                }
            }
        }
    }
    T->height = max(Getheight(T->left),Getheight(T->right))+1;
    return T;
}


void Traverse(struct avl * T){
    if ( T!=NULL ){
        Traverse(T->left);
        Traverse(T->right);
        cout<<T->val<<' ';
    }
}

//前序
void pre_order_traverse(struct avl * T){
    struct avl * cur = T;
    stack<struct avl *> s;    
    while( cur!=NULL || !s.empty() ){
        while( cur!=NULL ){
            cout<<cur->val<<' ';
            s.push(cur);
            cur = cur->left;
        }
        if ( !s.empty() ){
            cur = (s.top())->right;
            s.pop();
        }
    }
}

//中序
void mid_order_traverse(struct avl * T){
    struct avl * cur = T;
    stack<struct avl * > s;
    while( cur!=NULL || !s.empty() ){
        while( cur!=NULL ){
            s.push(cur);
            cur = cur->left;
        }
        cur = s.top();
        s.pop();
        cout<<cur->val<<' ';
        cur = cur->right;
    }
}

typedef struct tt{
    struct avl * node;
    bool First_visit;
}record;

//后序
void last_order_traverse(struct avl * T){
    stack<record*> s;
    while( T!=NULL || !s.empty() ){
        while( T!=NULL ){
            record * new_record = new record();
            new_record->First_visit = true;  //记录是否是第一次访问该节点
            new_record->node = T;            //记录该node
            s.push(new_record);
            T = T->left;
        }
        if ( !s.empty() ){
            record *tmp = s.top();
            s.pop();
            if ( tmp->First_visit ){    //如果是第一次访问，说明右子树还没被访问
                tmp->First_visit = false;   
                s.push(tmp);            //因为还要先访问右子树，所以再把该节点给push回去
                T = (tmp->node->right)?tmp->node->right:T;  //如果右子树是空的就没必要再赋值了
            }else{//如果已经访问过右子树了，就直接visit把
                cout<<tmp->node->val<<' ';
                T = NULL;   //下一次不需要再去找最左叶子，所以就把T弄空，这样下次就跳过循环直接得到pop
            }
        }
    }
} 

int main(void)
{
    struct avl * head=NULL;
    int N,tmp;
    cin>>N;
    for ( int i=0; i<N; ++i ){
        cin>>tmp;
        head = Insert(head,tmp);
    }
    //Traverse(head);
    //last_order_traverse(head);
    cout<<head->val<<endl;
    return 0;
}