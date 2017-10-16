 # include <string.h>
# include <stdio.h>

int dp[501]; //每一列的最大和（两两之间不相邻） 
int num[501][501];
int visited[501]; 

int main(void)
{
	int X,Y,i,j,len,k;
	while (~scanf("%d %d",&Y,&X)){
		memset(num,0,sizeof(num));
		for ( i=1; i<=Y; ++i ){
			for ( j=1; j<=X; ++j )
				scanf("%d",&num[i][j]);
		}
		int Col,n=X; 
		for ( i=1; i<=Y; ++i )
		{
			visited[1] = 1;
			for ( j=2; j<=X; ++j )
			{
				visited[j]=0;
		 		if ( num[i][j-2] + num[i][j] >num[i][j-1]  )   //如果第j个元素加上前j-2个元素和大于前j-1个元素和 
		 		{
		 			if ( visited[j-1] )
		 			{
						num[i][j] += num[i][j-2];
			//			printf("1 %d\n",num[i][j]);
					}
					else{
						num[i][j] += num[i][j-1];
			//			printf("2 %d\n",num[i][j]);
					}
					visited[j] = 1;	
				}
				else
				{
					if ( !visited[j-1] )
					{
						num[i][j] += num[i][j-1];
						visited[j] = 1;
			//			printf("3 %d\n",num[i][j]);
					}
					else
						num[i][j] = num[i][j-1]; 
				}
			}	
		} 
		visited[1]=1;
		for ( i=2; i<=Y; ++i )
		{
			visited[i] = 0;
			if ( num[i-2][n]+num[i][n]>num[i-1][n] )
			{
	 			if ( visited[i-1] )
	 			{
					num[i][n] += num[i-2][n];
				}
				else{
					num[i][n] += num[i-1][n];
				}
				visited[i] = 1;	
			}
			else
			{
				if ( !visited[i-1] )
				{
					num[i][n] += num[i-1][n];
					visited[i] = 1;
				}
				else
					num[i][n] = num[i-1][n]; 
			}
			
		}
		printf("%d\n",num[Y][X]); 	
	
	}
	return 0;
}         
