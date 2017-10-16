# include <stdio.h>
# include <cstring>
# define max(a,b) (a)>(b)?(a):b
using namespace std;
int main(void){
    int num[1000];
    memset(num,0,sizeof(num));
    for ( int i=0; i<100; ++i )
        printf("%d\n",num[i]);
}
