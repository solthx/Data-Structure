# include <iostream>
# include <cstdlib>
# include <time.h>
# include <algorithm>
# include <cstdio>
# define Num 10000
using namespace std;

int num[Num];

void Insertsort(int l,int r){
    for ( int i=l+1; i<=r; ++i ){
        int j=i-1;
        int s = num[i];
        while( j>=l && num[j]>s ){
            num[j+1] = num[j];
            j--;
        }
        num[j+1] = s;
    }
}

int get_p(int *num,int l,int r){
    int mid = (l+r)/2;
    if ( num[l]<num[mid] ) swap(num[l],num[mid]);
    if ( num[r]<num[mid] ) swap(num[r],num[mid]);
    if ( num[r]<num[l] ) swap(num[r],num[l]);
    return num[l];
}

void quicksort(int * num, int l,int r){
    if ( l<0 || r>=Num || l>=r ) return;
    if ( r-l<=15 ){
        Insertsort(l,r);
        return;
    }
    int p = get_p(num,l,r);
    int i=l,j=r,m=l;
    while( i<=j ){
        if ( num[i]<num[m] )
            swap(num[i++],num[m++]);
        else if ( num[i]>num[m] )
            swap(num[i],num[j--]);
        else i++;
    }
    /*while( i<=j ){
        while( i<j && num[j]>=p )
            j--;
        while( i<j && num[i]<=p )
            i++;
        if ( i<j ){
            swap(num[i],num[j]);
        }
    }
    num[l] = num[i];
    num[i] = p;
    quicksort(num,l,i-1);
    quicksort(num,i+1,r);*/
    quicksort(num,l,m-1);
    quicksort(num,j+1,r); 
} 

int cmp(const void *a, const void *b)
{
     return(*(int *)a-*(int *)b);
}

int main(void){
    srand(2);
    for (int i=0; i<Num; ++i )
        num[i] = (rand())%100+1;
    double s = clock();
    qsort(num,Num,sizeof(num[0]),cmp);
    double e = clock();
    printf("%lf\n",e-s);
    for (int i=0; i<Num; ++i )
        num[i] = (rand())%100+1;
    s = clock();
    quicksort(num,0,Num-1);
    e = clock();
    printf("%lf\n",e-s);
    return 0;
}