
/*
	��Ŀ����: ����һ���� x y���󵥵�����(����һ��x��y��������һ��)�����и���
	����:
		��̬�滮�ⷨ:
		 �ȸ��ṹ��������� ��Ҫ��x�Ĵ�С���������У��������y�Ĵ�С��
		 ��ʱ�ṹ�����x�Ѿ����������
		 k[i]���浽��i������Ϊֹ��������������  
		 �����ʱ 
		 
		 ������̰�����ܼ�  - -�� 
*/


# include <cstdio>
# include <string.h>
# include <iostream>
# include <string.h>
# include <algorithm>
using namespace std;

typedef struct {
	int x,y;
}ll;

ll num[5100];
int n,k[5100];

void solve_dp()
{
	int i,j;
	for ( i=0; i<n; ++i ) //ɨ��ÿһ������ 
	{
		for ( j=0; j<i; ++j )  
			if ( num[i].y<num[j].y && k[i]<k[j]+1/*��j������ݱȵ�i��� ����Ҫ�����µ������� �����и����ڴ˻����ϼ�һ*/ )  //��Ϊ��i���x�ض�����j���x ���ԱȽ�y ����i���yС ˵�����������ƻ� ����Ƿ�Ҫ������������и��� 
			{		
				k[i] = k[j]+1;
			}
	}
	printf("%d\n",*max_element(k,k+n)); //������������и����������Ǹ� 
}

int cmp(ll a,ll b)
{
	if ( a.x!=b.x )
		return a.x<b.x;
	else
		return a.y<b.y;
}

int main(void)
{
	int N,i,j,v,w,sum,temp;
	scanf("%d",&N);
	while ( N-- )
	{
		sum=0;
		scanf("%d",&n);
	//	for ( i=0; i<=n; ++i ) k[i] = 1;
		for ( i=0; i<n; ++i )
		{
			scanf("%d %d",&num[i].x,&num[i].y); 
		}
		sort(num,num+n,cmp); 
	
	//	solve_dp();  ����ⷨ
	
		/*̰�Ľⷨ*/ 
		for ( i=0; i<n; ++i )
		{
			if ( num[i].y )
			{
				sum++;
				temp = num[i].y;
				num[i].y = 0;
				for ( j=i+1; j<n; ++j )
				{
					if ( num[j].y>=temp )
					{
						temp = num[j].y;
						num[j].y = 0;
					}
				}
			}
		}
		printf("%d\n",sum);
	}
	return 0;	
} 
