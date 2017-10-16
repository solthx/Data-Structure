# include <iostream>
# include <cstdlib>
# include <time.h>
# define Num 90
using namespace std;

int num[Num];

void mergesort(int * num,int *t,int l,int mid,int r){
    int i=l,k=0;
    int j=mid+1;
    while( i<=mid && j<=r ){
        if ( num[i]<num[j] ) t[k++] = num[i++];
        else t[k++] = num[j++];
    }
    while( i<=mid ) t[k++] = num[i++];
    while( j<=r ) t[k++] = num[j++];
    for ( int i=0; i<k; ++i ){
        num[l+i] = t[i];
    }
}
/* 递归版
void Msort(int * num, int * t, int l, int r){
    if ( l>=r ) return ;
    int mid = (l+r)/2;
    Msort(num,t,l,mid);
    Msort(num,t,mid+1,r);
    mergesort(num,t,l,mid,r);
}

void Mergesort(int * num,int l,int r){
    int * t = new int[Num];
    Msort(num,t,l,r);
    delete [] t;
}*/

void Msort(int * num,int * t,int k, int length){
    int i=0;
    while( i+2*k<length ){
        mergesort(num,t,i,i+k-1,i+2*k-1);
        i += 2*k;
    }
    cout<<k<<endl;
    if ( i+k<length ) //i+k-1<=length-1
        mergesort(num,t,i,i+k-1,length-1);
    //大于就不管它了
    
}

//非递归版
void Mergesort(int * num,int l,int r){
    int * t = new int[Num];
    int i=1;
    while( i<Num ){
        Msort(num,t,i,Num);
        i*=2;
    }
    delete [] t;
}

int main(void){
    srand(2);
    for (int i=0; i<Num; ++i )
        num[i] = (rand()*100)%100;
    Mergesort(num,0,Num-1);
    for (int i=0; i<Num; ++i )
        cout<<num[i]<<' ';
    cout<<endl;
    return 0;
}