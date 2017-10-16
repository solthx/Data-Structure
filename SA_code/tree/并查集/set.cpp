# include <iostream>
# define Num 10
using namespace std;

int mset[Num]; 

int Find(int x){
    if ( mset[x]<0 ) return x;
    return x = Find(mset[x]); 
}

void Union(int x,int y){
    int a = Find(x);
    int b = Find(y);
    if ( a==b ) return ;
    if ( mset[a]<mset[b] ){
        mset[a] += mset[b];
        mset[b] = a;
    }else{
        mset[b] += mset[a];
        mset[a] = b;
    }
}

int main(void){
    for ( int i=0; i<Num; ++i ) mset[i]=-1;
    int n,a,b;
    while(1){
        cout<<"输入你要合并的集合："<<endl;
        cin>>a>>b;
        Union(a,b);
        cout<<"输入你要查询的数:"<<endl;
        cin>>a;
        cout<<"答案是："<<Find(a)<<endl;
    }
    return 0;
}