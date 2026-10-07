#include <stdio.h>

int main()
{
	int cars[12],sum=0,overloaded=0,highest,lowest,difference;
	float avg;
	
	printf("enter number of cars waiting for 12 signals: ");
	
	for(int i=0;i<12;i++)
	{
		scanf("%d",&cars[i]);
		
		sum=sum+cars[i];
	}
	
	avg=(float)sum/12;
	highest=cars[0];
	lowest=cars[0];
	
	for(int i=0;i<12;i++)
	{
		if(cars[i]>avg)
		{
			overloaded++;
		}
		
		if(cars[i]>highest)
		{
			highest=cars[i];
		}
		if(cars[i]<lowest)
		{
			lowest=cars[i];
		}
	}
	difference=highest-lowest;
	printf("sum %d",sum);
	printf("avg %f",avg);
	printf("highest %d",highest);
	printf("lowest %d",lowest);
	printf("difference %d",difference);
	printf("overloaded %d",overloaded);
	
	
}
