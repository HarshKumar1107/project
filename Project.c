#include<stdio.h>
#include<stdlib.h>
#include <math.h>

#define MAX_SIZE 10
#define SIZE 10
#define ROWS 100
#define COLS 100

void multiplyMatrices(int A[][COLS], int B[][COLS], int M[][COLS], int m, int n, int q) {
    int i, j, k;
     for(int i=0;i<m;i++){
        for(int j=0;j<q;j++){
            M[i][j]=0;
            for(int k=0;k<n;k++){
                M[i][j] += A[i][k]*B[k][j];
            }
        }
    } 
}

// Function to calculate the determinant of a 2D matrix
double determinant(double matrix[][SIZE], int n) {
    double det = 0, submatrix[SIZE][SIZE];

    if (n == 2) {
        return (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
    } else {
        for (int x = 0; x < n; x++) {
            int subi = 0;
            for (int i = 1; i < n; i++) {
                int subj = 0;
                for (int j = 0; j < n; j++) {
                    if (j == x)
                        continue;
                    submatrix[subi][subj] = matrix[i][j];
                    subj++;
                }
                subi++;
            }
            det = det + (x % 2 == 0 ? 1 : -1) * matrix[0][x] * determinant(submatrix, n - 1);
        }
    }
    return det;
}

void displayMatrix(int mat[][COLS], int rows, int cols) {
    int i, j;

    printf("Matrix:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void transpose(int a[][COLS],int t[][COLS],int m,int n)
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			t[j][i]=a[i][j];
		}
	}
}

void scalarMultiply(int a[][COLS],int af[][COLS],int m,int n,int f)
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			af[i][j]=f*a[i][j];
		}
	}
}

void addMatrices(int a[][COLS],int b[][COLS],int result[][COLS],int m,int n)
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			result[i][j]=a[i][j]+b[i][j];
		}
	}
}

void subtractMatrices(int a[][COLS],int b[][COLS],int result[][COLS],int m,int n)
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			result[i][j]=a[i][j]-b[i][j];
		}
	}
}

// Function to print a double type matrix
void printMatrix(double matrix[][10], int n) {
    printf("The matrix is:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%0.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}
// Function to perform row operations
void rowOperation(double matrix[][10], int n, int row1, int row2, double factor) {
    for (int j = 0; j < n; j++) {
        matrix[row1][j] -= factor * matrix[row2][j];
    }
}
// Function to calculate the inverse of a matrix
void inverseMatrix(double matrix[][10], int n) {
    double augmentedMatrix[10][10];
    int i, j, k;
    double factor, pivot;

    // Initializing the augmented matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            augmentedMatrix[i][j] = matrix[i][j];
            augmentedMatrix[i][j + n] = (i == j) ? 1 : 0;
        }
    }
    // Applying Gauss-Jordan elimination
    for (i = 0; i < n; i++) {
        pivot = augmentedMatrix[i][i];

        // Scaling the current row to make the pivot equal to 1
        for (j = 0; j < 2 * n; j++) {
            augmentedMatrix[i][j] /= pivot;
        }
        // Making all other entries in the current column equal to 0
        for (k = 0; k < n; k++) {
            if (k != i) {
                factor = augmentedMatrix[k][i];
                rowOperation(augmentedMatrix, 2 * n, k, i, factor);
            }
        }
    }

    // Extracting the inverse matrix
    double inverse[10][10];
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            inverse[i][j] = augmentedMatrix[i][j + n];
        }
    }
    
    // Printing the inverse matrix
    printf("The inverse matrix is:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%0.2f ", inverse[i][j]);
        }
        printf("\n");
    }
}

void gauss_elimination(double matrix[MAX_SIZE][MAX_SIZE], double constants[MAX_SIZE], int size) {
    // Forward elimination
    for (int k = 0; k < size - 1; k++) {
        // Check for division by zero
        if (matrix[k][k] == 0) {
            printf("Error: The system may not have a unique solution.\n");
            return;
        }
        for (int i = k + 1; i < size; i++) {
            double factor = matrix[i][k] / matrix[k][k];
            constants[i] -= factor * constants[k];
            for (int j = k; j < size; j++) {
                matrix[i][j] -= factor * matrix[k][j];
            }
        }
    }

    // Backward substitution
    double solution[MAX_SIZE];
    for (int i = size - 1; i >= 0; i--) {
        // Check for division by zero
        if (matrix[i][i] == 0) {
            printf("Error: The system may not have a unique solution.\n");
            return;
        }
        solution[i] = constants[i];
        for (int j = i + 1; j < size; j++) {
            solution[i] -= matrix[i][j] * solution[j];
        }
        solution[i] /= matrix[i][i];
    }

    // Print the solution
    printf("Solution:\n");
    for (int i = 0; i < size; i++) {
        printf("x%d = %.2f\n", i + 1, solution[i]);
    }
}

int main(){

    printf("\n---------Welcome to Applications of Matrix---------\n\n");

    int choice;
    printf("Enter the operation u would like to perform:\n\n");
    printf("1.Addition and subtraction of matrix\n");
    printf("2.Multiplication of a matrix\n");
    printf("3.Transpose of matrix\n");
    printf("4.Inverse of matrix\n");
    printf("5.Determinant\n");
    printf("6.Solution of matrix\n\n");
    printf("Enter the choice:\n");
    scanf("%d",&choice);


    if(choice==1)//Add/Subtract
    {
        int mat1[ROWS][COLS], mat2[ROWS][COLS], result[ROWS][COLS];
        int rows1, cols1, rows2, cols2;
        int i, j;

        printf("Enter the number of rows and columns of the first matrix: ");
        scanf("%d %d", &rows1, &cols1);

        printf("Enter the elements of the first matrix:\n");
        for (i = 0; i < rows1; i++) {
            for (j = 0; j < cols1; j++) {
                scanf("%d", &mat1[i][j]);
            }   
        }


        printf("Enter the elements of the second matrix:\n");
        for (i = 0; i < rows1; i++) {
            for (j = 0; j < cols1; j++) {
                scanf("%d", &mat2[i][j]);
            }
        }

        addMatrices(mat1, mat2, result, rows1, cols1);
        printf("Addition of matrices:");
        displayMatrix(result, rows1, cols1);
        subtractMatrices(mat1, mat2, result, rows1, cols1);
        printf("Subtraction of matrices:");
        displayMatrix(result, rows1, cols1);
    }



    if(choice==2)//Multiplication
    {
        int mat1[ROWS][COLS], mat2[ROWS][COLS], result[ROWS][COLS];
        int rows1, cols1, rows2, cols2;
        int i, j;

        printf("Enter the number of rows and columns of the first matrix: ");
        scanf("%d %d", &rows1, &cols1);

        printf("Enter the elements of the first matrix:\n");
        for (i = 0; i < rows1; i++) {
            for (j = 0; j < cols1; j++) {
                scanf("%d", &mat1[i][j]);
            }   
        }

        printf("Enter the number of rows and columns of the second matrix: ");
        scanf("%d %d", &rows2, &cols2);

        printf("Enter the elements of the second matrix:\n");
        for (i = 0; i < rows2; i++) {
            for (j = 0; j < cols2; j++) {
                scanf("%d", &mat2[i][j]);
            }
        }

        if (cols1 != rows2) {
            printf("Error: Number of columns in the first matrix should be equal to the number of rows in the second matrix.\n");
            return 0;
        }

        multiplyMatrices(mat1, mat2, result, rows1, cols1, cols2);

        displayMatrix(result, rows1, cols2);
    }
    if(choice==3)//Transpose of a matrix
    {
        int a[100][100], transpose[100][100], m, n;
        printf("Enter rows and columns: ");
        scanf("%d %d", &m, &n);

        printf("\nEnter matrix elements:\n");
        for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j) {
        printf("Enter element a%d%d: ", i + 1, j + 1);
        scanf("%d", &a[i][j]);
        }

        printf("\nEntered matrix: \n");
        for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j) {
            printf("%d  ", a[i][j]);
            if (j == n - 1)
            printf("\n");
        }

        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j) {
                transpose[j][i] = a[i][j];
        }

        printf("\nTranspose of the matrix:\n");
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                printf("%d  ", transpose[i][j]);
                if (j == m - 1)
                printf("\n");
            }
        return 0;
    }


    if(choice==4)//Inverse of a matrix
    {
        int n;
        double matrix[10][10];

        printf("Enter the size of the matrix: ");
        scanf("%d", &n);

        printf("\nEnter the elements of the matrix:\n\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%lf", &matrix[i][j]);
            }
        }
        if(determinant(matrix,n)==0.0)
        printf("Error: Matrix is not invertible[Determinant=0]\n");
        else
        {
        printMatrix(matrix, n);
        inverseMatrix(matrix, n);
        }
    }

    if(choice==5)//Determinent
    {
        double matrix[SIZE][SIZE];
        int size;

        printf("Enter the size of the matrix (maximum %d): ", SIZE);
        scanf("%d", &size);

        printf("\nEnter the elements of the matrix:\n\n");
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                scanf("%lf", &matrix[i][j]);
            }
        }

        printf("Determinant = %0.2lf\n",determinant(matrix,size));
    }


    if(choice==6)//Solution of matrix
    {
        int size;
        printf("Enter the size of the system of equations (up to %d): ", MAX_SIZE);
        scanf("%d", &size);

        // Validate the size input
        if (size <= 0 || size > MAX_SIZE) {
            printf("Invalid size. Please enter a positive integer up to %d.\n", MAX_SIZE);
            return 1;
        }   

        double matrix[MAX_SIZE][MAX_SIZE];
        double constants[MAX_SIZE];

        printf("Enter the coefficients of the equations:\n");
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                printf("Enter coefficient a%d%d: ", i + 1, j + 1);
                if (scanf("%lf", &matrix[i][j]) != 1) {
                    printf("Invalid input. Please enter a numeric value.\n");
                    return 1;
                }
            }
        }

        printf("\nEnter the constants:\n");
        for (int i = 0; i < size; i++) {
            printf("Enter constant b%d: ", i + 1);
            if (scanf("%lf", &constants[i]) != 1) {
                printf("Invalid input. Please enter a numeric value.\n");
                return 1;
            }
        }
        printf("\n");
        // Solve the system of equations using Gauss elimination
        gauss_elimination(matrix, constants, size);

        return 0;
    }


    printf("\n (:\t END OF PROGRAM \t:) \n");
    return 0;
}