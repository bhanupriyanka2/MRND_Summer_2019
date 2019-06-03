#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <errno.h>

extern int errno;

void set_bit(char *buf, int bit, int val){
	int byte = bit / 8;
	char mask = 1 << (bit % 8);
	if (val)
		buf[byte] |= mask;
	else
		buf[byte] &= -mask;
}

int get_bit(char *buf, int bit){
	int byte = bit / 8;
	char mask = 1 << (bit % 8);
	return buf[byte] & mask ? 1 : 0;
}

void sort_file(char *buffer, char *inp_file_name, long lower_bound, long upper_bound){

	FILE *inp_file;
	char *number = (char *)malloc(sizeof(char)*10);

	for (int count = 0; count < 10;count++){
		fopen_s(&inp_file, inp_file_name, "r");
		/*fseek(inp_file, 0, SEEK_SET);
		if (inp_file == NULL){
			fprintf(stderr, "value %d\n", errno);
			fprintf(stderr, "error opening:%s", strerror(errno));
			break;
		}*/
		if (number == NULL){
			number = (char *)malloc(sizeof(char) * 10);
		}
		if (fgets(number, 9, inp_file) == NULL){
			fprintf(stderr, "value %d\n", errno);
			fprintf(stderr, "error opening:%s", strerror(errno));
			break;
		}
		number=fgets(number, 9, inp_file);
		while (number != NULL){
			long index;
			sscanf(number, "%ld", &index);
			index -= count * 1000000;
			if (index>lower_bound && index<upper_bound)
				set_bit(buffer, index, 1);
			number = fgets(number, 9, inp_file);
		}
		printf("displaying....");
		for (long i = 0; i < 1000000; i++)
			if (get_bit(buffer, i))
				printf("%ld\n", i + (count*1000000));

		printf("resetting.... ");
		for (long i = 0; i < 1000000; i++)
			set_bit(buffer, i, 0);
		fclose(inp_file);
	}
}


int main(){
	char *array = (char *)malloc(128000 * sizeof(char));
	for (long i = 0; i < 1000000; i++)
		set_bit(array,i,0);
	sort_file(array, "num_inp.txt", 0, 999999);
	system("pause");
	return 0;
}