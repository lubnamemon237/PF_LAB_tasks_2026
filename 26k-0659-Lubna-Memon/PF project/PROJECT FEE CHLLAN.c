#include <stdio.h>
#include <string.h>
#include <ctype.h>
//"I use a macro name MAX to define maximum no of students that my system can store Its value is 100"

//I also have color macros such as RED GREEN RESET etc These are used to display colored text in the console.

#define MAX 100

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

struct Student
{
    char id[15];
    char name[50];
    char program[30];
    int semester;
    char challanNo[20];
    char password[20];
    float totalFee;
    float paidFee;
};

struct Student s[MAX];
int count = 0;

void loadRecords();
void saveRecords();
void clearInput();
int compareIgnoreCase(char a[], char b[]);
int findStudent(char id[]);

void adminLogin();
void studentLogin();
void addStudent();
void viewStudents();
void recordPayment();
void searchStudent();
void outstandingFees();
void viewChallan(int index);
void displayStudent(int index);

int main()
{
    int choice;

    loadRecords();

    do
    {
        printf(CYAN "\n====================================\n");
        printf("   STUDENT FEE & CHALLAN SYSTEM\n");
        printf("====================================\n" RESET);

        printf("\n              MAIN MENU\n");
        printf("\n1. Admin Login");
        printf("\n2. Student Login");
        printf("\n3. Exit");

        printf(YELLOW "\n\nEnter your choice: " RESET);
        scanf("%d", &choice);
        clearInput();

        switch(choice)
        {
            case 1:
                adminLogin();
                break;

            case 2:
                studentLogin();
                break;

            case 3:
                printf(GREEN "\nThank you for using the system!\n" RESET);
                break;

            default:
                printf(RED "\nInvalid choice!\n" RESET);
        }

    } while(choice != 3);

    return 0;
}

void clearInput()
{
    int ch;

    while((ch = getchar()) != '\n' && ch != EOF);
}

int compareIgnoreCase(char a[], char b[])
{
    int i = 0;

    while(a[i] != '\0' && b[i] != '\0')
    {
        if(tolower((unsigned char)a[i]) !=
           tolower((unsigned char)b[i]))
        {
            return 1;
        }

        i++;
    }

    if(a[i] == '\0' && b[i] == '\0')
    {
        return 0;
    }

    return 1;
}

int findStudent(char id[])
{
    int i;

    for(i = 0; i < count; i++)
    {
        if(compareIgnoreCase(s[i].id, id) == 0)
        {
            return i;
        }
    }

    return -1;
}

void saveRecords()
{
    FILE *fp;

    fp = fopen("students.dat", "wb");

    if(fp == NULL)
    {
        printf(RED "\nUnable to save records!\n" RESET);
        return;
    }

    fwrite(s, sizeof(struct Student), count, fp);

    fclose(fp);
}

void loadRecords()
{
    FILE *fp;

    fp = fopen("students.dat", "rb");

    if(fp == NULL)
    {
        count = 0;
        return;
    }

    count = 0;

    while(count < MAX &&
          fread(&s[count], sizeof(struct Student), 1, fp) == 1)
    {
        count++;
    }

    fclose(fp);
}

void adminLogin()
{
    char username[20];
    char password[20];
    int choice;

    printf(MAGENTA "\n========== ADMIN LOGIN ==========\n" RESET);

    printf("Enter Username: ");
    scanf("%19s", username);

    printf("Enter Password: ");
    scanf("%19s", password);
    clearInput();

    if(strcmp(username, "admin") == 0 &&
       strcmp(password, "1234") == 0)
    {
        printf(GREEN "\nAdmin Login Successful!\n" RESET);

        do
        {
            printf(BLUE "\n========== ADMIN DASHBOARD ==========\n" RESET);

            printf("\n1. Add Student");
            printf("\n2. View All Students");
            printf("\n3. Record Fee Payment");
            printf("\n4. Search Student");
            printf("\n5. View Outstanding Fees");
            printf("\n6. Logout");

            printf(YELLOW "\n\nEnter your choice: " RESET);
            scanf("%d", &choice);
            clearInput();

            switch(choice)
            {
                case 1:
                    addStudent();
                    break;

                case 2:
                    viewStudents();
                    break;

                case 3:
                    recordPayment();
                    break;

                case 4:
                    searchStudent();
                    break;

                case 5:
                    outstandingFees();
                    break;

                case 6:
                    printf(GREEN "\nAdmin Logged Out!\n" RESET);
                    break;

                default:
                    printf(RED "\nInvalid Choice!\n" RESET);
            }

        } while(choice != 6);
    }
    else
    {
        printf(RED "\nInvalid Admin Username or Password!\n" RESET);
    }
}

void addStudent()
{
    char id[15];

    if(count >= MAX)
    {
        printf(RED "\nStudent Record Limit Reached!\n" RESET);
        return;
    }

    printf(CYAN "\n========== ADD STUDENT ==========\n" RESET);

    printf("Enter Student ID (e.g. 26K-0659): ");
    scanf("%14s", id);
    clearInput();

    if(findStudent(id) != -1)
    {
        printf(RED "\nStudent ID Already Exists!\n" RESET);
        return;
    }

    strcpy(s[count].id, id);

    printf("Enter Student Name: ");
    fgets(s[count].name, sizeof(s[count].name), stdin);
    s[count].name[strcspn(s[count].name, "\n")] = '\0';

    printf("Enter Program: ");
    fgets(s[count].program, sizeof(s[count].program), stdin);
    s[count].program[strcspn(s[count].program, "\n")] = '\0';

    printf("Enter Semester: ");
    scanf("%d", &s[count].semester);

    printf("Enter Challan Number: ");
    scanf("%19s", s[count].challanNo);

    printf("Set Student Password: ");
    scanf("%19s", s[count].password);

    printf("Enter Total Fee: ");
    scanf("%f", &s[count].totalFee);

    printf("Enter Initial Paid Fee: ");
    scanf("%f", &s[count].paidFee);
    clearInput();

    if(s[count].totalFee <= 0 ||
       s[count].paidFee < 0 ||
       s[count].paidFee > s[count].totalFee)
    {
        printf(RED "\nInvalid Fee Amount!\n" RESET);
        return;
    }

    count++;

    saveRecords();

    printf(GREEN "\nStudent Added Successfully!\n" RESET);
}

void displayStudent(int index)
{
    float remaining;

    remaining = s[index].totalFee - s[index].paidFee;

    printf(CYAN "\n------------------------------------\n" RESET);

    printf("Student ID       : %s\n", s[index].id);
    printf("Student Name     : %s\n", s[index].name);
    printf("Program          : %s\n", s[index].program);
    printf("Semester         : %d\n", s[index].semester);
    printf("Challan Number   : %s\n", s[index].challanNo);

    printf("Total Fee        : %.2f\n", s[index].totalFee);
    printf("Paid Fee         : %.2f\n", s[index].paidFee);
    printf("Remaining Fee    : %.2f\n", remaining);

    if(remaining == 0)
    {
        printf(GREEN "Payment Status   : PAID\n" RESET);
    }
    else if(s[index].paidFee > 0)
    {
        printf(YELLOW "Payment Status   : PARTIALLY PAID\n" RESET);
    }
    else
    {
        printf(RED "Payment Status   : UNPAID\n" RESET);
    }

    printf(CYAN "------------------------------------\n" RESET);
}

void viewStudents()
{
    int i;

    printf(BLUE "\n========== ALL STUDENTS ==========\n" RESET);

    if(count == 0)
    {
        printf(RED "\nNo Student Records Found!\n" RESET);
        return;
    }

    for(i = 0; i < count; i++)
    {
        displayStudent(i);
    }
}

void recordPayment()
{
    char id[15];
    float amount;
    int index;

    printf(CYAN "\n========== RECORD PAYMENT ==========\n" RESET);

    printf("Enter Student ID: ");
    scanf("%14s", id);
    clearInput();

    index = findStudent(id);

    if(index == -1)
    {
        printf(RED "\nStudent Not Found!\n" RESET);
        return;
    }

    printf("Remaining Fee: %.2f\n",
           s[index].totalFee - s[index].paidFee);

    printf("Enter Payment Amount: ");
    scanf("%f", &amount);
    clearInput();

    if(amount <= 0 ||
       amount > s[index].totalFee - s[index].paidFee)
    {
        printf(RED "\nInvalid Payment Amount!\n" RESET);
        return;
    }

    s[index].paidFee += amount;

    saveRecords();

    printf(GREEN "\nPayment Recorded Successfully!\n" RESET);
}

void searchStudent()
{
    char id[15];
    int index;

    printf(CYAN "\n========== SEARCH STUDENT ==========\n" RESET);

    printf("Enter Student ID: ");
    scanf("%14s", id);
    clearInput();

    index = findStudent(id);

    if(index == -1)
    {
        printf(RED "\nStudent Not Found!\n" RESET);
    }
    else
    {
        displayStudent(index);
    }
}

void outstandingFees()
{
    int i;
    int found = 0;

    printf(YELLOW "\n========== OUTSTANDING FEES ==========\n" RESET);

    for(i = 0; i < count; i++)
    {
        if(s[i].paidFee < s[i].totalFee)
        {
            displayStudent(i);
            found = 1;
        }
    }

    if(found == 0)
    {
        printf(GREEN "\nNo Outstanding Fees!\n" RESET);
    }
}

void viewChallan(int index)
{
    printf(MAGENTA "\n========== FEE CHALLAN ==========\n" RESET);

    printf("\nStudent ID     : %s", s[index].id);
    printf("\nStudent Name   : %s", s[index].name);
    printf("\nProgram        : %s", s[index].program);
    printf("\nSemester       : %d", s[index].semester);
    printf("\nChallan Number : %s", s[index].challanNo);

    printf("\nTotal Fee      : %.2f", s[index].totalFee);
    printf("\nPaid Fee       : %.2f", s[index].paidFee);

    printf("\nRemaining Fee  : %.2f",
           s[index].totalFee - s[index].paidFee);

    printf("\n====================================\n");
}

void studentLogin()
{
    char id[15];
    char password[20];
    int index;
    int choice;

    printf(MAGENTA "\n========== STUDENT LOGIN ==========\n" RESET);

    printf("Enter Student ID: ");
    scanf("%14s", id);

    printf("Enter Password: ");
    scanf("%19s", password);
    clearInput();

    index = findStudent(id);

    if(index != -1 &&
       strcmp(s[index].password, password) == 0)
    {
        printf(GREEN "\nStudent Login Successful!\n" RESET);

        do
        {
            printf(BLUE "\n========== STUDENT DASHBOARD ==========\n" RESET);

            printf("\n1. View Fee Details");
            printf("\n2. View Challan");
            printf("\n3. Logout");

            printf(YELLOW "\n\nEnter your choice: " RESET);
            scanf("%d", &choice);
            clearInput();

            switch(choice)
            {
                case 1:
                    displayStudent(index);
                    break;

                case 2:
                    viewChallan(index);
                    break;

                case 3:
                    printf(GREEN "\nStudent Logged Out!\n" RESET);
                    break;

                default:
                    printf(RED "\nInvalid Choice!\n" RESET);
            }

        } while(choice != 3);
    }
    else
    {
        printf(RED "\nInvalid Student ID or Password!\n" RESET);
    }
}
