// PART 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

struct Student
{
    int rollNo;
    char name[50];
    int age;
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main()
{
    int choice;

    printf("\n====================================");
        printf("\n STUDENT MANAGEMENT SYSTEM");
        printf("\n====================================");
        printf("\n1. Add Student");
        printf("\n2. Display Students");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Exit");
        printf("\n------------------------------------");

    while(1)
    {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nThank you for using Student Management System.\n");
                exit(0);

            default:
                printf("\nInvalid Choice! Try Again.\n");
        }
    }

    return 0;
}

// PART 2(1)
void addStudent()
{
    FILE *fp;
    struct Student s;

    fp = fopen(FILE_NAME, "ab");

    if(fp == NULL) {
        printf("\nError opening file!\n");
        return;
    }

    printf("\nEnter Roll Number : ");
    scanf("%d", &s.rollNo);
    
    printf("Enter Name : ");
    scanf(" %[^\n]", s.name);
    
    printf("Enter Age : ");
    scanf("%d", &s.age);
    
    printf("Enter Marks : ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(struct Student), 1, fp);

    fclose(fp);

    printf("\nStudent Record Added Successfully.\n");

}

// PART 2(2)
void displayStudents()
{
    FILE *fp;
    struct Student s;

    fp = fopen(FILE_NAME, "rb");

    if(fp == NULL) {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\n------------------------------------------\n");
    printf("Roll\tName\t\tAge\tMarks\n");
    printf("\n------------------------------------------\n");

    while(fread(&s, sizeof(struct Student), 1, fp))
    {
        printf("%d\t%-15s%d\t%.2f\n", s.rollNo, s.name, s.age, s.marks);
    }
    fclose(fp);
}

// PART 3
void searchStudent()
{
    FILE *fp;
    struct Student s;
    int roll;
    int found = 0;

    fp = fopen(FILE_NAME, "rb");

    if(fp == NULL) {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Roll Number to Search : ");
    scanf("%d",&roll);

    while(fread(&s, sizeof(struct Student), 1, fp)) {
        if(s.rollNo == roll) {
            printf("\nStudent Found\n");
            printf("----------------------\n");
            printf("Roll Number : %d\n",s.rollNo);
            printf("Name        : %d\n",s.name);
            printf("Age         : %d\n",s.age);
            printf("Marks       : %d\n",s.marks);

            found = 1;
            break;

        }
    }
    if(found == 0) {
        printf("\nStudent Record Not Found!!\n");
    }
    fclose(fp);
}

// PART 3(2)
void updateStudent()
{
    FILE *fp;
    struct Student s;
    int roll;
    int found = 0;

    fp = fopen(FILE_NAME, "rb+");

    if(fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Roll Number to Update: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(struct Student), 1, fp))
    {
        if(s.rollNo == roll)
        {
            printf("\nEnter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Age: ");
            scanf("%d", &s.age);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(struct Student), SEEK_CUR);

            fwrite(&s, sizeof(struct Student), 1, fp);

            printf("\nStudent Record Updated Successfully.\n");

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nStudent Record Not Found!\n");
    }

    fclose(fp);
}

// PART 4
void deleteStudent()
{
    FILE *fp, *temp;
    struct Student s;
    int roll;
    int found = 0;

    fp = fopen(FILE_NAME, "rb");

    if(fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    printf("\nEnter Roll Number to Delete: ");
    scanf("%d", &roll);

    while(fread(&s, sizeof(struct Student), 1, fp))
    {
        if(s.rollNo == roll)
        {
            found = 1;
            continue;
        }

        fwrite(&s, sizeof(struct Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);

    rename("temp.dat", FILE_NAME);

    if(found)
        printf("\nStudent Record Deleted Successfully.\n");
    else
        printf("\nStudent Record Not Found.\n");
}