#include <stdio.h>

int main()
{
	FILE *ptr;
	ptr=fopen("items.txt","w");
	if(ptr==NULL)
	{
		printf("File not created");
		return 1;
	}
	int itemNum,quantity,stock;
	char name[10];
	float price,total=0;
	fprintf(ptr,"%-4d %-20s %9.2f %5d\n",1,"Rice",250.00,40);
	fprintf(ptr,"%-4d %-20s %9.2f %5d\n",2,"Sugar",160.00,25);
	fprintf(ptr,"%-4d %-20s %9.2f %5d\n",3,"Milk",220.00,30);
	fprintf(ptr,"%-4d %-20s %9.2f %5d\n",4,"Oil",560.00,12);
	fprintf(ptr,"%-4d %-20s %9.2f %5d\n",5,"Tea",450.00,18);
	
	fclose(ptr);
	ptr=fopen("items.txt","rb+");
	if(ptr==NULL)
	{
		printf("File not created");
		return 1;
	}
	while(1)
	{
		printf("\nEnter Item number: ");
		scanf("%d",&itemNum);
		if(itemNum==0)
		{
			break;
		}
		printf("Enter Quantity: ");
		scanf("%d",&quantity);
		
		fseek(ptr,(itemNum-1)*42,SEEK_SET);
		fscanf(ptr,"%d %s %f %d",&itemNum,name,&price,&stock);
		
		if(quantity<=stock)
		{
			printf("%s %dx%.2f=%.2f",name,quantity,price,quantity*price);
			total+=quantity*price;
			stock-=quantity;
			
			fseek(ptr,(itemNum-1)*42,SEEK_SET);
			fprintf(ptr,"%-4d %-20s %9.2f %5d",itemNum,name,price,stock);
		}
		else
		{
			printf("Only %d %s in stock\n",itemNum,name);
		}
	}
	
	printf("Total bill:%.2f\n",total);
	fclose(ptr);
}
