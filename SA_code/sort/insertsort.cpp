# include <iostream>
# include <cstdlib>
# include <time.h>
# include <algorithm>
# include <cmath>
# define Num 100000000
using namespace std;

int num[Num];
int Sedgewick[]={0,
    1,5,19,41,109,209,505,929,
    2161,3905,8929,16001,36289,64769,146305,260609,
    587521,1045505,2354689,4188161,9427969,16764929,37730305,67084289,
    150958081,268386305,603906049,1073643521};

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


void shellsort(){
    int d,j,i,tmp,s,D;
    for ( s=28; Sedgewick[s]>=Num ; --s );
    for ( D=Sedgewick[s]; D>0; D = Sedgewick[--s] ){
        for ( i=D; i<Num; i++ ){
            j = i-D;
            tmp = num[i];
            while( j>=0 && num[j]>tmp ){
                num[j+D] = num[j];
                j -= D;
            }
            num[j+D] = tmp;
        }
    }
}

int main(void){
    srand(1);
    for (int i=0; i<Num; ++i )
        num[i] = rand()%100000000+1;
    //Insertsort(0,Num-1);
    //Init();
    double start = clock();
    shellsort();
    double end = clock();
    cout<<((double)end-(double)start)<<endl;
    return 0;
}