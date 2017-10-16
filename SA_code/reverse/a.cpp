# include <iostream>
# include <cstdio>
using namespace std;

struct ll {
    int val;
    int next;
};

struct ll arr[100000];
int start_idx,K,N;

int Reverse(int start_idx){
    if ( start_idx==-1 ) return -1; 
    int i=0;  
    int tmp;    
    int pre;    //记录前一个变量的值
    int cur=start_idx; //记录当前变量的值
    int next_tmp;   //暂时保存下一节点的index

    //先看足不足K个
    while( (i++)<K ){
        pre = cur;
        cur = arr[pre].next;
        //不足K个就返回
        if ( cur==-1 && i!=K ) return start_idx;
    }
    //得到后面一个子链表（K个节点）的首节点index
    pre = Reverse(cur);
    //翻转当前长度为K的链表
    i=0;
    cur = start_idx;
    while( (i++)<K-1 ){
        next_tmp = arr[cur].next;
        arr[cur].next = pre;
        pre = cur;
        cur = next_tmp;
    }
    arr[cur].next = pre;
    //返回当前长度为K的链表的首节点index
    return cur;
}

int main(void){
    cin>>start_idx>>N>>K;
    int address;
    while( N-- ){
        cin>>address;
        cin>>arr[address].val>>arr[address].next;
    }
    int head=start_idx;
    if ( K!=1 )
        head = Reverse(start_idx);
    int cur = head;
    while( arr[cur].next!=-1 ){
        printf("%05d %d %05d\n",cur,arr[cur].val,arr[cur].next);
        cur = arr[cur].next;
    }
    printf("%05d %d %d\n",cur,arr[cur].val,arr[cur].next);
    return 0;
}