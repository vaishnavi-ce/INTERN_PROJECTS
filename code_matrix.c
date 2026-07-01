#include <stdio.h>
#include <stdlib.h>

#define MAX 10

void inputMatrix(int matrix[MAX][MAX], int rows, int cols);
void displayMatrix(int matrix[MAX][MAX], int rows, int cols);
void addMatrix();
void multiplyMatrix();
void transposeMatrix();
void clearScreen();

int main()
{
    int choice;

        printf("\n==========================================");
        printf("\n        MATRIX OPERATIONS SYSTEM");
        printf("\n==========================================");
        printf("\n1. Matrix Addition");
        printf("\n2. Matrix Multiplication");
        printf("\n3. Matrix Transpose");
        printf("\n4. Exit");
        printf("\n------------------------------------------");

    while(1)
    {
        printf("\nEnter your choice : ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                clearScreen();
                addMatrix();
                break;

            case 2:
                clearScreen();
                multiplyMatrix();
                break;

            case 3:
                clearScreen();
                transposeMatrix();
                break;

            case 4:
                printf("\nThank you for using Matrix Operations System.\n");
                exit(0);

            default:
                printf("\nInvalid Choice! Please Try Again.\n");
        }
    }

    return 0;
}

void inputMatrix(int matrix[MAX][MAX], int rows, int cols)
{
    int i, j;

    printf("\nEnter Matrix Elements\n\n");

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            printf("Element [%d][%d] : ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }
}

void displayMatrix(int matrix[MAX][MAX], int rows, int cols)
{
    int i, j;

    printf("\n");

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            printf("%6d", matrix[i][j]);
        }

        printf("\n");
    }
}

void clearScreen()
{
    printf("\n------------------------------------------\n");
}

void addMatrix()
{
    int A[MAX][MAX], B[MAX][MAX], Sum[MAX][MAX];
    int rows, cols;
    int i, j;

    printf("\n========== MATRIX ADDITION ==========\n");

    printf("\nEnter Number of Rows : ");
    scanf("%d", &rows);

    printf("Enter Number of Columns : ");
    scanf("%d", &cols);

    printf("\nEnter Elements of First Matrix\n");
    inputMatrix(A, rows, cols);

    printf("\nEnter Elements of Second Matrix\n");
    inputMatrix(B, rows, cols);

    printf("\nFirst Matrix");
    displayMatrix(A, rows, cols);

    printf("\nSecond Matrix");
    displayMatrix(B, rows, cols);

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            Sum[i][j] = A[i][j] + B[i][j];
        }
    }

    printf("\nAddition Result");
    displayMatrix(Sum, rows, cols);

    printf("\n------------------------------------------");
    printf("\nPress Enter to Continue...");
    getchar();
    getchar();
}

void multiplyMatrix()
{
    int A[MAX][MAX], B[MAX][MAX], Result[MAX][MAX];
    int rows1, cols1, rows2, cols2;
    int i, j, k;

    printf("\n========== MATRIX MULTIPLICATION ==========\n");

    printf("\nEnter Rows of First Matrix : ");
    scanf("%d", &rows1);

    printf("Enter Columns of First Matrix : ");
    scanf("%d", &cols1);

    printf("\nEnter Rows of Second Matrix : ");
    scanf("%d", &rows2);

    printf("Enter Columns of Second Matrix : ");
    scanf("%d", &cols2);

    if(cols1 != rows2)
    {
        printf("\nMatrix Multiplication is Not Possible!\n");
        printf("Columns of First Matrix must be equal to Rows of Second Matrix.\n");
        printf("\nPress Enter to Continue...");
        getchar();
        getchar();
        return;
    }

    printf("\nEnter Elements of First Matrix\n");
    inputMatrix(A, rows1, cols1);

    printf("\nEnter Elements of Second Matrix\n");
    inputMatrix(B, rows2, cols2);

    printf("\nFirst Matrix");
    displayMatrix(A, rows1, cols1);

    printf("\nSecond Matrix");
    displayMatrix(B, rows2, cols2);

    for(i = 0; i < rows1; i++)
    {
        for(j = 0; j < cols2; j++)
        {
            Result[i][j] = 0;

            for(k = 0; k < cols1; k++)
            {
                Result[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("\nMultiplication Result");
    displayMatrix(Result, rows1, cols2);

    printf("\n------------------------------------------");
    printf("\nPress Enter to Continue...");
    getchar();
    getchar();
}

void transposeMatrix()
{
    int A[MAX][MAX], Transpose[MAX][MAX];
    int rows, cols;
    int i, j;

    printf("\n========== MATRIX TRANSPOSE ==========\n");

    printf("\nEnter Number of Rows : ");
    scanf("%d", &rows);

    printf("Enter Number of Columns : ");
    scanf("%d", &cols);

    printf("\nEnter Elements of Matrix\n");
    inputMatrix(A, rows, cols);

    printf("\nOriginal Matrix");
    displayMatrix(A, rows, cols);

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            Transpose[j][i] = A[i][j];
        }
    }

    printf("\nTranspose Matrix");
    displayMatrix(Transpose, cols, rows);

    printf("\n------------------------------------------");
    printf("\nPress Enter to Continue...");
    getchar();
    getchar();
}