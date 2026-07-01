//PART 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "bank.dat"

struct Account
{
    int accountNumber;
    char name[50];
    float balance;
};

void createAccount();
void depositMoney();
void withdrawMoney();
void balanceEnquiry();
void displayaccounts();

int main()
{
    int choice;

    printf("\n=====================================");
        printf("\n   BANK ACCOUNT MANAGEMENT SYSTEM");
        printf("\n=====================================");
        printf("\n1. Create Account");
        printf("\n2. Deposit Money");
        printf("\n3. Withdraw Money");
        printf("\n4. Balance Enquiry");
        printf("\n5. Display All Accounts");
        printf("\n6. Exit");
        printf("\n-------------------------------------");

    while(1)
    {
        printf("\nEnter Your Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                depositMoney();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                balanceEnquiry();
                break;

            case 5:
                displayaccounts();
                break;

            case 6:
                printf("\nThank You For Using Bank Management System.\n");
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}


//PART 2(1)
void createAccount()
{
    FILE *fp;
    struct Account acc, temp;
    int found = 0;

    fp = fopen(FILE_NAME, "ab+");

    if(fp == NULL)
    {
        printf("\nError Opening File!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &acc.accountNumber);

    rewind(fp);

    while(fread(&temp, sizeof(struct Account), 1, fp))
    {
        if(temp.accountNumber == acc.accountNumber)
        {
            found = 1;
            break;
        }
    }

    if(found)
    {
        printf("\nAccount Number Already Exists!\n");
        fclose(fp);
        return;
    }

    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", acc.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    if(acc.balance < 0)
    {
        printf("\nInitial Balance Cannot Be Negative!\n");
        fclose(fp);
        return;
    }

    fwrite(&acc, sizeof(struct Account), 1, fp);

    fclose(fp);

    printf("\nAccount Created Successfully.\n");
}

//PART 2(2)
void depositMoney()
{
    FILE *fp;
    struct Account acc;
    int accNo;
    float amount;
    int found = 0;

    fp = fopen(FILE_NAME, "rb+");

    if(fp == NULL)
    {
        printf("\nNo Account Found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while(fread(&acc, sizeof(struct Account), 1, fp))
    {
        if(acc.accountNumber == accNo)
        {
            printf("Enter Deposit Amount: ");
            scanf("%f", &amount);

            acc.balance += amount;

            fseek(fp, -sizeof(struct Account), SEEK_CUR);

            fwrite(&acc, sizeof(struct Account), 1, fp);

            printf("\nAmount Deposited Successfully.\n");
            printf("Current Balance : %.2f\n", acc.balance);

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nAccount Not Found!\n");
    }

    fclose(fp);
}


// PART 3(1)
void withdrawMoney()
{
    FILE *fp;
    struct Account acc;
    int accNo;
    float amount;
    int found = 0;

    fp = fopen(FILE_NAME, "rb+");

    if(fp == NULL)
    {
        printf("\nNo Account Found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while(fread(&acc, sizeof(struct Account), 1, fp))
    {
        if(acc.accountNumber == accNo)
        {
            found = 1;

            printf("Enter Withdraw Amount: ");
            scanf("%f", &amount);

            if(amount > acc.balance)
            {
                printf("\nInsufficient Balance!\n");
            }
            else
            {
                acc.balance -= amount;

                fseek(fp, -sizeof(struct Account), SEEK_CUR);

                fwrite(&acc, sizeof(struct Account), 1, fp);

                printf("\nAmount Withdrawn Successfully.\n");
                printf("Current Balance : %.2f\n", acc.balance);
            }

            break;
        }
    }

    if(found == 0)
    {
        printf("\nAccount Not Found!\n");
    }

    fclose(fp);
}

// PART 3(2)
void balanceEnquiry()
{
    FILE *fp;
    struct Account acc;
    int accNo;
    int found = 0;

    fp = fopen(FILE_NAME, "rb");

    if(fp == NULL)
    {
        printf("\nNo Account Found!\n");
        return;
    }

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while(fread(&acc, sizeof(struct Account), 1, fp))
    {
        if(acc.accountNumber == accNo)
        {
            printf("\n========== ACCOUNT DETAILS ==========\n");
            printf("Account Number : %d\n", acc.accountNumber);
            printf("Account Holder : %s\n", acc.name);
            printf("Current Balance: %.2f\n", acc.balance);

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nAccount Not Found!\n");
    }

    fclose(fp);
}


void displayaccounts()
{
    FILE *fp;
    struct Account acc;
    int count = 0;

    fp = fopen(FILE_NAME, "rb");

    if(fp == NULL)
    {
        printf("\nNo Accounts Found!\n");
        return;
    }

    printf("\n==============================================");
    printf("\n         LIST OF BANK ACCOUNTS");
    printf("\n==============================================");
    printf("\n%-15s %-25s", "Account No", "Account Holder");
    printf("\n----------------------------------------------");

    while(fread(&acc, sizeof(struct Account), 1, fp))
    {
        printf("\n%-15d %-25s",
               acc.accountNumber,
               acc.name);

        count++;
    }

    if(count == 0)
    {
        printf("\nNo Accounts Available.");
    }

    printf("\n----------------------------------------------");
    printf("\nTotal Accounts : %d\n", count);

    fclose(fp);
}

