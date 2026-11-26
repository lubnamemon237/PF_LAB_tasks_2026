
#include <stdio.h>

int main()
{
    FILE *ptr;

    ptr=fopen("expenses.txt","ab");

    if(ptr==NULL)
    {
        printf("File not opened");
        return 1;
    }

    char category[13];
    float amount;

    printf("Enter category: ");
    scanf("%12s",category);

    printf("Enter amount: ");
    scanf("%f",&amount);

    fprintf(ptr,"%-12s %9.2f",category,amount);
    fputc('\n',ptr);

    fclose(ptr);

    ptr=fopen("expenses.txt","rb+");

    if(ptr==NULL)
    {
        printf("File not opened");
        return 1;
    }

    fseek(ptr,-2*23,SEEK_END);

    char ch[13];
    float rate;

    printf("\nLatest two expenses:\n");

    for(int i=1;i<=2;i++)
    {
        fscanf(ptr,"%12s %f",ch,&rate);
        printf("%s %.2f\n",ch,rate);
    }

    int entry;
    float correctAmount;

    printf("\nEnter entry number to fix: ");
    scanf("%d",&entry);

    printf("Enter correct amount: ");
    scanf("%f",&correctAmount);

    if(entry<1)
    {
        printf("Invalid entry number");
        fclose(ptr);
        return 1;
    }

    fseek(ptr,(entry-1)*23,SEEK_SET);

    char oldCategory[13];
    float oldAmount;

    if(fscanf(ptr,"%12s %f",oldCategory,&oldAmount)!=2)
    {
        printf("Invalid entry");
        fclose(ptr);
        return 1;
    }

    fseek(ptr,(entry-1)*23,SEEK_SET);

    fprintf(ptr,"%-12s %9.2f",oldCategory,correctAmount);
    fputc('\n',ptr);

    rewind(ptr);

    float total=0;

    printf("\nAll Expenses:\n");

    while(fscanf(ptr,"%12s %f",ch,&rate)==2)
    {
        printf("%s %.2f\n",ch,rate);
        total=total+rate;
    }

    printf("\nTotal: %.2f\n",total);

    fclose(ptr);

    return 0;
}

