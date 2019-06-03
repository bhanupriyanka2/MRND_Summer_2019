#include <stdio.h>
#include<stdlib.h>
#include <unordered_map>

using namespace std;


long fibonacci(long n){
	if (n == 0){
		return 0;
	}
	if (n == 1){
		return 1;
	}
	return fibonacci(n - 1) + fibonacci(n - 2);
}


long fibonacci_memorized(int n, std::unordered_map <int, int>& fib){
	if (n < 0)
		return 0;
	if (n == 1 || n == 0)
		return 1;
	if (fib[n - 1] && fib[n - 2])
	{
		return fib[n - 1] + fib[n - 2];
	}
	else if (fib[n - 1] && !fib[n - 2])
	{
		return fib[n - 1] + fibonacci_memorized(n - 2, fib);
	}
	else if (!fib[n - 1] && fib[n - 2])
	{
		return fibonacci_memorized(n - 1, fib) + fib[n - 2];
	}
	else if (!fib[n - 1] && !fib[n - 2])
	{
		return fibonacci_memorized(n - 1, fib) + fibonacci_memorized(n - 2, fib);
	}
}


int **matrix_space_allocation(int rows, int cols){
	int **matrix = (int **)malloc(sizeof(int *)*rows);
	for (int row = 0; row < rows; row++){
		matrix[row] = (int *)malloc(sizeof(int)*cols);
	}
	return matrix;
}


int **matrix_multiplication(int **matrix_A, int **matrix_B, int row_A, int col_B, int col_A){
	int **result = matrix_space_allocation(row_A, col_B);
	for (int row = 0; row < row_A; row++){
		for (int col = 0; col < col_B; col++){
			result[row][col] = 0;
		}
	}
	for (int row = 0; row < row_A; row++){
		for (int col = 0; col < col_B; col++){
			for (int index = 0; index < col_A; index++){
				result[row][col] += matrix_A[row][index] * matrix_B[index][col];
			}
		}
	}
	return result;
}


int **matrix_exponentiation(int n, int **matrix_A){
	if (n == 2){
		return matrix_multiplication(matrix_A, matrix_A, 2, 2, 2);
	}
	if (n % 2 == 0){
		return matrix_multiplication(matrix_exponentiation(n / 2, matrix_A), matrix_exponentiation(n / 2, matrix_A),2,2,2);
	}
	return matrix_multiplication(matrix_A, matrix_multiplication(matrix_exponentiation(n / 2, matrix_A), matrix_exponentiation(n / 2, matrix_A), 2, 2, 2), 2, 2, 2);
}


int  **fibonacci_matrix_exponentiation(int n, int **matrix_A, int **matrix_fib){
	matrix_fib = matrix_multiplication(matrix_exponentiation(n, matrix_A), matrix_fib,2,1,2);
	return matrix_fib;
}




/*int main(){
	long n = 8;
	int row_A = 2, row_B = 2, col_A = 2, col_B = 1;
	int **matrix_A =matrix_space_allocaion(row_A,col_A);
	int **matrix_B = matrix_space_allocation(row_B,col_B);
	printf("Enter matrix_A:\n");
	for (int i = 0; i < row_A; i++){
		for (int j = 0; j < col_A; j++){
			scanf("%d", &matrix_A[i][j]);
		}
	}
	fflush(stdin);
	printf("Enter matrix_B:\n");
	for (int i = 0; i < row_B; i++){
		for (int j = 0; j < col_B; j++){
			scanf("%d", &matrix_B[i][j]);
		}
	}
	fflush(stdin);
	int **result = fibonacci_matrix_exponentiation(n, matrix_A, matrix_B);
    long fib=fibonacci(n);
    printf("%d",fib);
	printf("fibonacci number :%d", result[0][0]);
	getchar();
	return 0;
}*/