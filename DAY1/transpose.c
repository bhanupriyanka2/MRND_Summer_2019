#include <stdio.h>
#include <stdlib.h>

int **transpose_matrix(int **matrix, int m, int n){
	int **transpose = (int **)malloc(sizeof(int *)*n);
	for (int i = 0; i < m; i++){
		transpose[i] = (int *)malloc(sizeof(int)*m);
	}
	for (int row = 0; row < m; row++){
		for (int col = 0; col < n; col++){
			transpose[col][row] = matrix[row][col];
		}
	}
	return transpose;
}

/*int main(){
	int m, n;
	printf("Enter number of rows:");
	scanf("%d", &m);
	fflush(stdin);
	printf("Enter number of columns:");
	scanf("%d", &n);
	fflush(stdin);
	int **matrix = (int **)malloc(sizeof(int *)*m);
	for (int i = 0; i < m; i++){
		matrix[i] = (int *)malloc(sizeof(int)*n);
	}
	printf("Elements of matrix");
	for (int row = 0; row < m; row++){
		for (int col = 0; col < n; col++){
			scanf("%d",&matrix[row][col]);
		}
	}
	fflush(stdin);
	int **result = transpose_matrix(matrix, m, n); 
	for (int row = 0; row < n; row++){
		for (int col = 0; col < m; col++){
			printf("%d ", result[row][col]);
		}
		printf("\n");
	}
	getchar();
	return 0;
}*/