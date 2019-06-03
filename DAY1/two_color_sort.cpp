#include <stdio.h>
#include <stdlib.h>

int *count_sort01(int *arr, int size){
	int count = 0;
	for (int index = 0; index < size; index++){
		if (arr[index] == 0){
			count++;
		}
	}
	printf("%d\n", count);
	for (int index = 0; index < count; index++){
		arr[index] = 0;
	}
	for (int index = count; index < size; index++){
		arr[index] = 1;
	}
	return arr;
}

int *sum_sort01(int *arr, int size){
	int sum = 0;
	for (int index = 0; index < size; index++){
		sum += arr[index];
	}
	int count = size-sum;
	for (int index = 0; index < count; index++){
		arr[index] = 0;
	}
	for (int index = count; index < size; index++){
		arr[index] = 1;
	}
	return arr;
}

int *sort01(int *arr, int size){
	int start_index = 0, end_index = size - 1;
	while (start_index < end_index){
		while (arr[start_index] != 1)
			start_index++;
		while (arr[end_index] != 0)
			end_index--;
		if (start_index > end_index)
			break;
		arr[start_index] = 0;
		arr[end_index] = 1;
		start_index += 1;
		end_index -= 1;
	}
	return arr;
}


/*int main(){
	int size;
	printf("Enter the size of array:");
	scanf("%d", &size);
	fflush(stdin);
	int *arr = (int *)malloc(sizeof(int)*size);
	printf("Enter the array elements:");
	for (int index = 0; index < size; index++){
		scanf("%d", &arr[index]);
	}
	fflush(stdin);
	//int *result1 = count_sort01(arr, size);
	//int *result2 = sum_sort01(arr, size);
    int *result3=sort01(arr, size);
	for (int index = 0; index < size; index++){
		printf("%d ", result3[index]);
	}
	getchar();
	return 0;
}*/