# include <iostream>
# include <cstdlib>
# include <cstring>
# define MaxSize 1000
using namespace std;

//edge node
typedef struct Enode {
    int vertex;  
    int adjvex; //ver->adj 
    int weight;	 
    struct Enode * next;
}Enode,*LEnode;

//邻接表中每个节点链表的头节点 
typedef struct {
    //ElementType VertexInfo 
	Enode * firstarc;
}A_elem;

//邻接表 
typedef struct {
    A_elem AdjList[MaxSize];
    int arcnum,vexnum;
}AGraph,*ALGraph;

//图的初始化
 
void Init(ALGraph & AG,int m,int n){
	//m为边数，n为节点数 
    AG->arcnum = m;
    AG->vexnum = n;    
    for ( int i=1; i<=AG->vexnum; i++ )
        AG->AdjList[i].firstarc = NULL;
}

// 向图中插入一条边
// v指向u，权重为w 
void Insert(ALGraph & G ,int v,int u,int w ){
    LEnode node = new Enode;
    node->vertex = v;
    node->adjvex = u;
    node->weight = w;
    node->next = G->AdjList[v].firstarc;
    G->AdjList[v].firstarc = node;
}

// 删除图中的一条边
// v指向u 
void Delete(ALGraph & G,int v,int u){
    LEnode p;  
    p = G->AdjList[v].firstarc;
    if ( p && p->adjvex==u ){
        //节点v的firstarc指向节点u，单独删 
		G->AdjList[v].firstarc = p->next;
        delete p;
    }else{
        // firstarc不指向u 
        // 找u 
        LEnode pre = p;
        while( p && p->adjvex!=u ){
            pre = p;
            p = p->next;
        }
        if ( p ){
            //找到节点u 
		    pre->next = p->next;
            delete p;
        }else{
            //没找到节点u
        }
    }
}




// DFS遍历图 
void DFS(ALGraph A,int v,int & sum,bool visited[]){
    //visit(v)
    visited[v] = true;
    for( LEnode p=A->AdjList[v].firstarc; p; p=p->next )
        if ( !visited[p->adjvex] ){
            visited[p->adjvex] = true;
            sum+=p->weight;
            DFS(A,p->adjvex,sum,visited);  
        }
}

//破圈法 
bool find_loop(ALGraph & A,int v,int tag,LEnode path[],int top,bool collected[],bool first,int pre){
     // v为当前节点
	 // tag为目标节点
	 // path保存路径，是个栈，元素为边结点
	 // top是path的栈顶
	 // collected[i] 表示节点i是否被访问过 
	 // first 表示是否是第一次进入本次函数
	 // pre记录上一个节点号  
	 
	 //首次进入本函数，v是起始点，不用标记访问，因为如果存在环，最后还要在访问一次当前节点 
	 if ( !first )
        collected[v] = true;
    
    // 在不是首次访问的情况下，当前节点与目标节点一致
	// 找出最大权重边，并删除之 
    if ( !first && tag==v ){
        LEnode tmp = path[0];
        int max_w = path[0]->weight;
        //找最大边 
		for ( int i=0; i<top; i++  )
            if ( max_w<path[i]->weight ){
                tmp = path[i];
                max_w = path[i]->weight;
            }
        //删除 
        Delete(A,tmp->vertex,tmp->adjvex);
        Delete(A,tmp->adjvex,tmp->vertex);
        return true;
    }
    
    // 遍历邻接点，用DFS的方式寻找环 
    bool res=false;
    for( LEnode p = A->AdjList[v].firstarc; p ; p = p->next ){
    	// 无向图在遍历时，要注意排除掉上一个节点，否则会死循环（因为是无向图...） 
		if ( pre==p->adjvex ) continue;
        
		if ( !collected[p->adjvex]  ){
			path[top++] = p;
            res = find_loop(A,p->adjvex,tag,path,top,collected,false,v);
            if ( res ) return true; //若找到，直接返回，不必继续 
            top--; //回溯 
        }
    }
    return false;
}

//破圈法生成最小生成树 
void Min_GTree(ALGraph & G){
    bool exist_loop=true; 
    LEnode path[1000];
	int top=0;
    bool collected[1000];
    //init
    for ( int i=1; i<=G->vexnum; ++i ) collected[i] = false;
    
    for( int v=1; v<=G->vexnum; ++v ){
        exist_loop = true;
        while( exist_loop ){
        	// find_loop : 若存在包含节点v的环，则删掉最大边，并返回true
			//             若不存在，则返回 false 
            exist_loop = find_loop(G,v,v,path,top,collected,true,-1);
        }
    }
}

int main(void)
{
	/*
		输入： 
			每个测试用例的第1行给出边数 m、节点数n
			之后m行给出 (v,u,w) v->u w为权重
			m为0时退出
		输出：
			连通则输出最小生成树的总权重
			不连通则输出"?" 
	*/ 
    int m,n,v,u,w;
    int sum=0; //总权重 
    
    bool visited[MaxSize];
    while( cin>>m>>n && m ){
        ALGraph AG = new AGraph ;
        for( int i=0; i<=n; i++ ) visited[i] = false;

        Init(AG,m,n);
        for( int i=0; i<m; ++i ){
            cin>>v>>u>>w;
            Insert(AG,v,u,w);
            Insert(AG,u,v,w);
        }    
        Min_GTree(AG);
        DFS(AG,1,sum,visited);
        for ( int i=1; i<=AG->vexnum; ++i )
            if ( !visited[i] ){
                sum=-1;
                break;
            }
            
        if ( sum>0 ) cout<<sum<<endl;
        else cout<<'?'<<endl;
        delete AG;
    }
    return 0;
}
