#include <stdio.h>
#include <stdlib.h>

int *sort012(int *arr, int size){
	int countOf1 = 0, countOf2 = 0, index = 0;
	for (index = 0; index < size; index++){
		if (arr[index] == 1){
			countOf1++;
		}
		else if (arr[index] == 2){
			countOf2++;
		}
	}
	for (index = 0; index < size - countOf1 - countOf2; index++){
		arr[index] = 0;
	}
	for (index = index; index < size - countOf2; index++){
		arr[index] = 1;
	}
	for (index = index; index < size; index++){
		arr[index] = 2;
	}
	return arr;
}

//int main(){
//	int size;
//	printf("Enter the size of array:");
//	scanf("%d", &size);
//	fflush(stdin);
//	int *arr = (int *)malloc(sizeof(int)*size);
//	printf("Enter the array elements:");
//	for (int index = 0; index < size; index++){
//		scanf("%d", &arr[index]);
//	}
//	fflush(stdin);
//	int *result = sort012(arr, size);
//	for (int index = 0; index < size; index++){
//		printf("%d ", result[index]);
//	}
//	getchar();
//	return 0;
//}