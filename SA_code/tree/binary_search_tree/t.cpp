# include <iostream>
# include <vector>
using namespace std;

vector<int> arr1;
vector<int> arr2;

struct ll {
    int val;
    struct ll * left;
    struct ll * right;
};

struct ll * Findmax(struct ll * T){
    if ( T!=NULL ){
        while( T->right!=NULL ){
            T = T->right;
        }
    }
    return T;
}

struct ll * Delete( struct ll * T , int v ){
    if ( T==NULL ){
        cout<<"没找到。。。"<<v<<endl;
    }else {
        //非空
        //大了去右边删
        if ( v<T->val )
            T->left = Delete(T->left,v);
        else if ( v>T->val )
            T->right = Delete(T->right,v);
        else{
            //相等
            if ( T->left && T->right ){
                struct ll * tmp = Findmax(T->left);
                T->val = tmp->val;
                T->left = Delete(T->left,T->val);
            }else{
                struct ll * tmp = T;
                if ( T->left==NULL ){
                    T = T->right;
                }else if (T->right==NULL){
                    T = T->left;    
                }
                delete tmp;
            }
        }
    }
    return T;
}

struct ll * Insert( struct ll * T , int v){
    if ( T==NULL ){
        struct ll * Node = new struct ll();
        Node->left = Node->right = NULL;
        Node->val = v;
        return Node;
    }else{
        if ( v>T->val )
            T->right = Insert(T->right,v);
        else if ( v<T->val )
            T->left = Insert(T->left,v);
    }
    return T;
}


void traverse_(struct ll * T){
    if ( T!=NULL ){
        traverse_(T->left);
        traverse_(T->right);
        cout<<T->val<<' ';
    }
}


int main(void){
    int N,L;
    cin>>N;
    while( N ){
        //cout<<"start"<<endl;
        struct ll * T1 = NULL;
        for ( int i=0; i<N; ++i ){
            int v;
            cin>>v;
            T1 = Insert(T1,v);
        }
        int k;
        traverse_(T1);
        cout<<endl;
        cin>>k;
        Delete(T1,k);
        traverse_(T1);
        cout<<endl;
    }
    return 0;
}