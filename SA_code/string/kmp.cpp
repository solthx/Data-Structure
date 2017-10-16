# include <iostream>
# include <cstdio>
# include <cstring>
using  namespace std;

int * get_next(char pat[], int length){
    /*
        构造next数组时，是在当前信息i和next[i]进行判断来决定
        出next[i+1]的值。

        由于每次更新都会更新出next[i+1]，而当前的next[i+1]在
        i移动一位后又会再次变成next[i]，所以我们可以在计算
        next[i+1]时，把它保存成t,并在下一次的时候直接使用

        t是记录了上一次的next[i+1]，也就是本次的next[i]
    */

    //因为是初始化，i=0，所以t=next[0]=-1
    int i=0, t=-1;
    int * next = new int[length+1];
    next[0] = -1;
    while( i<length ){
        if ( t<0 || pat[t]==pat[i] ){
            next[++i] = ++t;  //如果满足条件说明 next[i+1] = t(next[i]) + 1
        }else
            t = next[t];     //不满足条件的话 next[i] = next[next[i]];
    }
    return next;
}

//计算出text中有多少个pattern
int get_counter(char text[],int txt_size,int next[],char pat[],int pat_size){
    int i=0,j=0,counter=0;
    while( i<txt_size ){
        if ( j<0 || text[i]==pat[j] ){
            i++;
            j++;
        }else j = next[j];
        if ( j==pat_size-1 ){
            counter++;
            j = next[j];
        }
    }
    return counter;
}

int main(void){
    char text[1000001],pattern[10001];
    scanf("%s%s",pattern,text);
    int pat_size = strlen(pattern);
    int txt_size = strlen(text);
    int * next = get_next(pattern,pat_size) ;
    int counter = get_counter(text,txt_size,next,pattern,pat_size);
    printf("%d\n",counter);
    delete [] next;
    return 0;
}