#include <stdio.h>

void grow(int heights[],int n)
{
	if(n==0)
	{
		return;
	}
	heights[n-1]=heights[n-1]+(int)(heights[n-1]*0.10);
	grow(heights,n-1);
}

int tallest(int heights[],int n)
{
	if(n==1){
		return 0;
	}
	int pos=tallest(heights,n-1);
	
	if(heights[n-1]>heights[pos])
	{
		return n-1;
	}
	else
	{
		return pos;
	}
}
int search(int heights[], int n, int target)
{
	if(n==0)
	{
		return -1;
	}
	if(heights[n-1]==target)
	{
		return n-1;
	}
	else
	{
		return search(heights,n-1,target);
	}
	
}
int main()
{
	int ids[6]={101,102,103,104,105,106};
	int heights[6]={45,120,78,200,95,150};
	
	grow(heights,6);
	printf("New heights: ");
	
	for(int i=0;i<6;i++)
	{
		printf("%d ",heights[i]);
	}
	int pos=tallest(heights,6);
	printf("\nTallest tower %d(%dm)\n",ids[pos],heights[pos]);
	
	int target;
	printf("Height to search: ");
	scanf("%d",&target);
	
	pos=search(heights,6,target);
	if(pos==-1)
	{
		printf("Tower with height %d not found\n",target);
	}
	else
	{
		printf("Tower %d is %dm",ids[pos],heights[pos]);
	}
}
