#include <stdio.h>
#include <string.h>

int main()
{
    FILE *ptr;

    int room;

    ptr=fopen("hotel.txt","w");

    if(ptr==NULL)
    {
        printf("File not created");
        return 1;
    }

    for(room=101;room<=110;room++)
    {
        fprintf(ptr,"%3d %c %-20s %2d %8.2f\n",room,'F',"-",0,8000.00);
    }

    fclose(ptr);

    ptr=fopen("hotel.txt","rb+");

    if(ptr==NULL)
    {
        printf("File not opened");
        return 1;
    }

    int choice;

    printf("\n1. Check-in");
    printf("\n2. Search Guest");
    printf("\n3. Check-out");
    printf("\nEnter choice: ");
    scanf("%d",&choice);

    if(choice==1)
    {
        int num,nights;
        int roomNum,numOfnights;
        char name[21],guest[21],status;
        float rate;

        printf("Enter Room number: ");
        scanf("%d",&num);

        printf("Enter Guest name: ");
        scanf("%20s",name);

        printf("Enter number of nights: ");
        scanf("%d",&nights);

        if(num<101 || num>110)
        {
            printf("Invalid room number");
        }
        else
        {
            fseek(ptr,(num-101)*39,SEEK_SET);

            fscanf(ptr,"%3d %c %20s %2d %f",&roomNum,&status,guest,&numOfnights,&rate);

            if(status=='F')
            {
                fseek(ptr,-39,SEEK_CUR);

                fprintf(ptr,"%3d %c %-20s %2d %8.2f\n",roomNum,'B',name,nights,rate);

                printf("Room booked successfully");
            }
            else
            {
                printf("Room already booked");
            }
        }
    }

    else if(choice==2)
    {
        char search[21],guest[21],status;
        int roomNum,nights;
        float rate;
        int found=0;

        printf("Enter guest name to search: ");
        scanf("%20s",search);

        rewind(ptr);

        while(fscanf(ptr,"%3d %c %20s %2d %f",&roomNum,&status,guest,&nights,&rate)==5)
        {
            if(status=='B' && strcmp(search,guest)==0)
            {
                printf("Guest found in room %d",roomNum);
                found=1;
                break;
            }
        }

        if(found==0)
        {
            printf("Guest not found");
        }
    }

    else if(choice==3)
    {
        int num,roomNum,nights;
        char guest[21],status;
        float rate,bill;

        printf("Enter room number: ");
        scanf("%d",&num);

        if(num<101 || num>110)
        {
            printf("Invalid room number");
        }
        else
        {
            fseek(ptr,(num-101)*39,SEEK_SET);

            fscanf(ptr,"%3d %c %20s %2d %f",&roomNum,&status,guest,&nights,&rate);

            if(status=='B')
            {
                bill=nights*rate;

                printf("Guest Name: %s\n",guest);
                printf("Room Number: %d\n",roomNum);
                printf("Total Bill: %.2f\n",bill);

                fseek(ptr,-39,SEEK_CUR);

                fprintf(ptr,"%3d %c %-20s %2d %8.2f\n",roomNum,'F',"-",0,rate);

                printf("Checkout successful");
            }
            else
            {
                printf("Room is already free");
            }
        }
    }

    else
    {
        printf("Invalid choice");
    }

    fclose(ptr);

    return 0;
}
