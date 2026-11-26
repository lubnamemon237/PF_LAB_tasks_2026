
#include <stdio.h>

int main()
{
    FILE *fp;

    fp=fopen("temp.txt","w");

    if(fp==NULL)
    {
        printf("File not created");
        return 1;
    }

    char name[15],hottest[15];
    float temp,max;
    int num;

    for(int i=1;i<=5;i++)
    {
        printf("Enter city name: ");
        scanf("%14s",name);

        printf("Enter temp: ");
        scanf("%f",&temp);

        fprintf(fp,"%-10s %5.1f\n",name,temp);
    }

    fclose(fp);

    fp=fopen("temp.txt","rb+");

    if(fp==NULL)
    {
        printf("File not opened");
        return 1;
    }

    printf("Enter city num: ");
    scanf("%d",&num);

    if(num<1 || num>5)
    {
        printf("Invalid city number.\n");
        fclose(fp);
        return 1;
    }

    fseek(fp,(num-1)*17,SEEK_SET);
    fscanf(fp,"%10s %f",name,&temp);

    printf("%s %.1f\n",name,temp);

    printf("Enter correct city num: ");
    scanf("%d",&num);

    if(num<1 || num>5)
    {
        printf("Invalid city number.\n");
        fclose(fp);
        return 1;
    }

    printf("Enter correct temp: ");
    scanf("%f",&temp);

    fseek(fp,(num-1)*17,SEEK_SET);

    fscanf(fp,"%10s",name);

    fseek(fp,(num-1)*17,SEEK_SET);

    fprintf(fp,"%-10s %5.1f\n",name,temp);

    printf("%s updated to %.1f\n",name,temp);

    rewind(fp);

    fscanf(fp,"%10s %f",hottest,&max);

    for(int i=1;i<5;i++)
    {
        fscanf(fp,"%10s %f",name,&temp);

        if(temp>max)
        {
            max=temp;

            int j=0;

            while(name[j]!='\0')
            {
                hottest[j]=name[j];
                j++;
            }

            hottest[j]='\0';
        }
    }

    printf("Hottest city: %s %.2f\n",hottest,max);

    fclose(fp);

    return 0;
}

