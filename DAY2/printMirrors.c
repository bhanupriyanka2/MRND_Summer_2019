#include <stdio.h>
#include<stdlib.h>


void printTillLimit(int limit, char *result, int current_state,char mirror_value[]){
	if (current_state == limit-1){
		for (int index = 0; index < limit; index++){
			printf("%c", result[index]);
		}
		printf("\n");
	}
	else{
		for (int value = 0; value < 10; value++){
			result[current_state] = mirror_value[value];
			printTillLimit(limit, result, current_state + 1,mirror_value);
		}
	}
}


int main(){
	int limit = 3;
	char *result = (char *)malloc(sizeof(char)*limit);
	for (int index = 0; index < limit; index++){
		result[index] = 0;
	}
	char mirror_values[] = "12Eh59L86\0";
	printTillLimit(limit, result, 0,mirror_values);
	getchar();
	return 0;
}