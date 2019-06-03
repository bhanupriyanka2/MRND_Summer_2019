#include <stdio.h>
#include <stdlib.h>

int *subArray(int *Arr, int size, int index_to_skip){
	int *sub_arr = (int *)malloc(sizeof(int)*size - 1);
	int pos = 0;
	for (int index = 0; index < size; index++){
		if (index == index_to_skip){
			continue;
		}
		sub_arr[pos++] = Arr[index];
	}
	return sub_arr;
}

void permutations(int *Arr, int current_state, int size, int *result){
	if (size == 0){
		for (int index = 0; index < current_state; index++){
			printf("%d ", result[index]);
		}
		printf("\n");
	}
	else{
		for (int index = 0; index < size; index++){
			int index1 = 0;
			for (index1 = 0; index1 < index; index1++){
				if (Arr[index1] == Arr[index]){
					break;
				}
			}
			if (index1 != index){
				continue;
			}
			int current_element = Arr[index];
			result[current_state] = current_element;
			int *sub_Arr = subArray(Arr, size, index);
			permutations(sub_Arr, current_state + 1, size - 1, result);
		}
	}
}


void possible_permutations(int *Arr, int size){
	int *result = (int *)malloc(sizeof(int)*size);
	permutations(Arr, 0, size, result);
}

/*int main(){
int Arr[] = { 1, 3, 5, 5 };
possible_permutations(Arr, 4);
getchar();
}*/