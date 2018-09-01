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

//�ڽӱ���ÿ���ڵ������ͷ�ڵ� 
typedef struct {
    //ElementType VertexInfo 
	Enode * firstarc;
}A_elem;

//�ڽӱ� 
typedef struct {
    A_elem AdjList[MaxSize];
    int arcnum,vexnum;
}AGraph,*ALGraph;

//ͼ�ĳ�ʼ��
 
void Init(ALGraph & AG,int m,int n){
	//mΪ������nΪ�ڵ��� 
    AG->arcnum = m;
    AG->vexnum = n;    
    for ( int i=1; i<=AG->vexnum; i++ )
        AG->AdjList[i].firstarc = NULL;
}

// ��ͼ�в���һ����
// vָ��u��Ȩ��Ϊw 
void Insert(ALGraph & G ,int v,int u,int w ){
    LEnode node = new Enode;
    node->vertex = v;
    node->adjvex = u;
    node->weight = w;
    node->next = G->AdjList[v].firstarc;
    G->AdjList[v].firstarc = node;
}

// ɾ��ͼ�е�һ����
// vָ��u 
void Delete(ALGraph & G,int v,int u){
    LEnode p;  
    p = G->AdjList[v].firstarc;
    if ( p && p->adjvex==u ){
        //�ڵ�v��firstarcָ��ڵ�u������ɾ 
		G->AdjList[v].firstarc = p->next;
        delete p;
    }else{
        // firstarc��ָ��u 
        // ��u 
        LEnode pre = p;
        while( p && p->adjvex!=u ){
            pre = p;
            p = p->next;
        }
        if ( p ){
            //�ҵ��ڵ�u 
		    pre->next = p->next;
            delete p;
        }else{
            //û�ҵ��ڵ�u
        }
    }
}




// DFS����ͼ 
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

//��Ȧ�� 
bool find_loop(ALGraph & A,int v,int tag,LEnode path[],int top,bool collected[],bool first,int pre){
     // vΪ��ǰ�ڵ�
	 // tagΪĿ��ڵ�
	 // path����·�����Ǹ�ջ��Ԫ��Ϊ�߽��
	 // top��path��ջ��
	 // collected[i] ��ʾ�ڵ�i�Ƿ񱻷��ʹ� 
	 // first ��ʾ�Ƿ��ǵ�һ�ν��뱾�κ���
	 // pre��¼��һ���ڵ��  
	 
	 //�״ν��뱾������v����ʼ�㣬���ñ�Ƿ��ʣ���Ϊ������ڻ������Ҫ�ڷ���һ�ε�ǰ�ڵ� 
	 if ( !first )
        collected[v] = true;
    
    // �ڲ����״η��ʵ�����£���ǰ�ڵ���Ŀ��ڵ�һ��
	// �ҳ����Ȩ�رߣ���ɾ��֮ 
    if ( !first && tag==v ){
        LEnode tmp = path[0];
        int max_w = path[0]->weight;
        //������ 
		for ( int i=0; i<top; i++  )
            if ( max_w<path[i]->weight ){
                tmp = path[i];
                max_w = path[i]->weight;
            }
        //ɾ�� 
        Delete(A,tmp->vertex,tmp->adjvex);
        Delete(A,tmp->adjvex,tmp->vertex);
        return true;
    }
    
    // �����ڽӵ㣬��DFS�ķ�ʽѰ�һ� 
    bool res=false;
    for( LEnode p = A->AdjList[v].firstarc; p ; p = p->next ){
    	// ����ͼ�ڱ���ʱ��Ҫע���ų�����һ���ڵ㣬�������ѭ������Ϊ������ͼ...�� 
		if ( pre==p->adjvex ) continue;
        
		if ( !collected[p->adjvex]  ){
			path[top++] = p;
            res = find_loop(A,p->adjvex,tag,path,top,collected,false,v);
            if ( res ) return true; //���ҵ���ֱ�ӷ��أ����ؼ��� 
            top--; //���� 
        }
    }
    return false;
}

//��Ȧ��������С������ 
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
        	// find_loop : �����ڰ����ڵ�v�Ļ�����ɾ�����ߣ�������true
			//             �������ڣ��򷵻� false 
            exist_loop = find_loop(G,v,v,path,top,collected,true,-1);
        }
    }
}

int main(void)
{
	/*
		���룺 
			ÿ�����������ĵ�1�и������� m���ڵ���n
			֮��m�и��� (v,u,w) v->u wΪȨ��
			mΪ0ʱ�˳�
		�����
			��ͨ�������С����������Ȩ��
			����ͨ�����"?" 
	*/ 
    int m,n,v,u,w;
    int sum=0; //��Ȩ�� 
    
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
