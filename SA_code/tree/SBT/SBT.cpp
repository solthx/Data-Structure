# include <iostream>
# include <stack>
# define Num 100000
using namespace std;

typedef struct {
	int left;
	int right;
	int size;
	int value;
}Node;  

Node tree[Num];
int root,cnt;

/*
void traverse(int x ){
	if ( x ){
		traverse(tree[x].left);
		cout<<tree[x].value<<' ';
		traverse(tree[x].right);
	}
}*/

void traverse(int x){
	stack<int > s;
	int t;
	while( x || !s.empty() ){
		while( x ){
			s.push(x);
			x = tree[x].left;
		}
		x = s.top();
		s.pop();
		cout<<tree[x].value<<' ';
		x = tree[x].right;
	}
}

int Newnode(int e){
	int x=++cnt;
	tree[x].left = tree[x].right=0;
	tree[x].value = e;
	tree[x].size = 1;
	return x;
}

//用引用的原因是改变当前节点的idx 然后返回给上层（因为是递归）,这样就改变了上一层的左或右孩子
void RR(int &x){
	int y = tree[x].left;
	tree[x].left = tree[y].right;
	tree[y].right = x;
	tree[y].size = tree[x].size;
	tree[x].size = tree[tree[x].left].size + tree[tree[x].right].size + 1;
	x = y;
}

int Findmax(int x){
	while( tree[x].right!=0 )
		x = tree[x].right;
	return x;
} 

int Findmin(int x){
	while( tree[x].left!=0 )
		x = tree[x].left;
	return x;
} 

//输出第n小的
int Rank(int x,int n){
	int cur_rank = tree[x].size-tree[tree[x].right].size;
	//目标在右子树
	if ( cur_rank<n ){
		//如果已经最大了，确还要更大的则返回最大的。
		if ( tree[x].right!=0 )
			return Rank(tree[x].right,n-1-tree[tree[x].left].size);
		else return tree[x].value;
	}else if ( cur_rank==n ){ 
		return tree[x].value;	//正好n是当前的rank，直接返回当前节点。
	}else{	//和右边同理
		if ( tree[x].left!=0 )
			return Rank(tree[x].left,n);
		else return tree[x].value;
	}
}
//删除和bst类似，不过要注意删除成功才能给size减一
bool Delete(int &x , int e){
	if ( !x ) return false;
	if ( tree[x].value > e ){ 
		//删除成功才给size减一
		if (Delete(tree[x].left,e)){
			tree[x].size--;
			return true;
		}
		return false;
	}else if ( tree[x].value<e ){
		if ( Delete(tree[x].right,e) ){
			tree[x].size--;
			return true;
		}
		return false;
	}else{ //这里的删除跟bst里的一模一样
		if ( tree[x].left && tree[x].right ){
			int t = Findmax(tree[x].left);
			if (Delete(tree[x].left,t))
			{
				tree[x].value = t;
				return true;	
			} 
		}else{
			if ( tree[x].left!=0 ){
				x = tree[x].left;
				return true;
			}else{
				x = tree[x].right;
				return true;
			}
		}
	}
}

void LL(int &x){
	int y = tree[x].right;
	tree[x].right = tree[y].left;
	tree[y].left = x;
	tree[y].size = tree[x].size;
	tree[x].size = tree[tree[x].left].size + tree[tree[x].right].size + 1;
	x = y;
}

void Maintain(int & x, int kind){
	if ( kind ){	//新节点加在了右子树上，所以判断右子树的左右子树有没有比左子树大
		if ( tree[tree[x].left].size < tree[tree[tree[x].right].right].size ){
			LL(x);
		}else if ( tree[tree[x].left].size < tree[tree[tree[x].right].left].size ){
			RR(tree[x].right);
			LL(x);
		}
		else return;
	}else{	//跟上面情况相反
		if ( tree[tree[x].right].size < tree[tree[tree[x].left].left].size ){
			RR(x);
		}else if ( tree[tree[x].right].size < tree[tree[tree[x].left].right].size ){
			LL(tree[x].left);
			RR(x);
		}else return ;	//要注意相等时判断返回。。不然会死循环
	}
	Maintain(tree[x].left,0);
	Maintain(tree[x].right,1);
	Maintain(x,0);
	Maintain(x,1);
}

void Insert(int &x, int t){
	if ( !x ){
		x = Newnode(t);
		return ;
	}
	tree[x].size++;
	if ( tree[x].value >t )
		Insert(tree[x].left, t);
	else if ( tree[x].value <t )
		Insert(tree[x].right , t);
	else return ;
	Maintain(x,tree[x].value<t);
}

int main(void)
{
	tree[0].size=tree[0].left=tree[0].right=tree[0].size=0;
	int N,d;
	cout<<"输节点个数\n";
	cin>>N;
	cout<<"输入节点\n";
	for (int i=0; i<N; i++)
	{
		int t;
		cin>>t; 
		if ( !i ) root = Newnode(t);
		else Insert(root,t); 
	}
	traverse(root); 
	cout<<endl;
	//删除操作
	cout<<"输入要删除的数"<<endl;
	cin>>d;
	if (Delete(root,d))
		cout<<"删除成功"<<endl;
	else cout<<"删除失败"<<endl;
	traverse(root); 
	cout<<endl;
	
	//rank操作
	cout<<"输入要第几大的数：\n";
	cin>>d;
	cout<<Rank(root,d);
	return 0;
 } 
