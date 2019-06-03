#include <stdio.h>
#include<stdlib.h>

void printTillLimit(int limit,int *result,int current_state){
	if (current_state == limit){
		for (int index = 0; index < limit; index++){
			printf("%d", result[index]);
		}
		printf("\n");
	}
	else{
		for (int value = 0; value < 10; value++){
			result[current_state] = value;
			printTillLimit(limit, result, current_state + 1);
		}
	}
}

int main(){
	int limit = 3;
	int *result = (int *)malloc(sizeof(int)*limit);
	for (int index = 0; index < limit; index++){
		result[index] = 0;
	}
	printTillLimit(limit, result, 0);
	getchar();
	return 0;
}