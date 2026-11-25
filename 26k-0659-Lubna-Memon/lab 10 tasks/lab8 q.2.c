#include <stdio.h>

int main()
{
	int K[2][2];
	int M[2][2];
	int E[2][2];
	char msg[5];
	int i,j,k;
	int mainSum,otherSum;
	
	printf("Enter key Matrix(2x2):\n");
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		scanf("%d",&K[i][j]);
	}
	printf("Enter letters: ");
	scanf("%4s",msg);
	
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			M[i][j]=msg[i*2+j]-'A'+1;
		}
	}
	
	printf("Message matrix:\n");
	
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("%d ",M[i][j]);
		}
		printf("\n");
	}
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			E[i][j]=0;
			for(k=0;k<2;k++)
			{
				E[i][j]+=K[i][k]*M[k][j];
			}
		}
	}
	printf("\nEnter secret matix:\n");
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("%d ",E[i][j]);
		}
		printf("\n");
	}
	printf("Transpose of secret matrix:\n");
	for(i=0;i<2;i++)
	{
		for(j=0;j<2;j++)
		{
			printf("%d ",E[j][i]);
		}
		printf("\n");
	}
	mainSum=E[0][0]+E[1][1];
	otherSum=E[0][1]+E[1][0];
	
	if(mainSum>otherSum)
	{
		printf("\nSafe\n");
	}
	else
	{
		printf("Unsafe\n");
	}
	if(K[0][0]==1 && K[0][1]==0 && K[1][0]==0 && K[1][1])
	{
		printf("Warning:Key is too weak");
	}
	else
	{
		printf("Key is Strong");
	}
}
