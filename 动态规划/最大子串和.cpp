# include <stdio.h>
int main(void)
{
	int MAX,m,T,n,N,sum,c,i,end;
	int start,temp; 
	scanf("%d",&N);
	for( m=1; m<=N; ++m )
	{
		scanf("%d",&n);
		scanf("%d",&c);
		MAX = sum = c;
		start = temp=end = 1;
		for ( i=2; i<=n; ++i )
		{
			scanf("%d",&c);
			if ( sum<0 )
			{ 
				sum = c; //sum<0 ��sum+c<c ֱ�Ӱ�С��0������ 
				temp = i;  // ��Ϊǰ���sum�������� ���Խ������п��ܴӱ��ڵ㿪ʼ���Ӵ��ͻ���Ϯ MAX  �����ȼ�¼һ�� 
			}
			else sum += c;		//��sum>=0 �� sum+c >=c ��sum����c 
 			if ( MAX<sum ) 
			{
				MAX =sum;   //�����ֵ 
		 		start = temp; //��Ϯ�ɹ� ���³�ʼλ��
				end = i; 
			}
		}
		printf("Case %d:\n%d %d %d\n",m,MAX,start,end);
	//	printf("��%dth��%dth���Ӵ������\n",start,end); 
	}
	return 0;
 } 

