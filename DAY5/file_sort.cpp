//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#define max_buffer 3
//
//
//FILE *create_dummy_file(FILE *input, int buffer_size, char *dummyFile, long int file_length){
//	int buffer = 0;
//	int value = 0;
//	FILE *dummy = fopen(dummyFile, "w+");
//	while (ftell(input)!=file_length && buffer < buffer_size){
//		fscanf(input, "%d", &value);
//		fputc(value, dummy);
//		fputs("\n", dummy);
//		buffer++;
//	}
//	return dummy;
//}
//
//int length_of_number(int number){
//	int length = 0;
//	while (number > 0){
//		number = number / 10;
//		length++;
//	}
//	return length;
//}
//
//
//char *number_to_str(int number){
//	char *string = (char *)malloc(sizeof(char)*length_of_number(number)+1);
//	int index = length_of_number(number);
//	while (number > 0){
//		string[index--] = '0' + (number % 10);
//		number = number / 10;
//	}
//	return string;
//}
//
//int string_length(char *string){
//	int len = 0;
//	for (len = 0; string[len] != '\0'; len++);
//	return len;
//}
//
//char *str_cat(char *string1, char *string2){
//	char *concat_string = (char *)malloc(sizeof(char)*(string_length(string1)*string_length(string2) + 1));
//	int charPos = 0;
//	int length1 = string_length(string1);
//	int length2 = string_length(string2);
//	for (int index = 0; index < length1; index++){
//		concat_string[charPos++] = string1[index];
//	}
//	for (int index = 0; index < length2; index++){
//		concat_string[charPos++] = string2[index];
//	}
//	concat_string[charPos] = '\0';
//	return concat_string;
//}
//
//
//char *dummyFileName(int *fileNum){
//	char *filename = (char *)malloc(sizeof(char) * (10+string_length(number_to_str(*fileNum))));
//	filename = str_cat(str_cat("dummy", number_to_str(*fileNum)), ".txt");
//	*fileNum++;
//	return filename;
//}
//
//long int length_of_file(FILE *file){
//	fseek(file, 0, SEEK_END);
//	long int length = ftell(file);
//	fseek(file, 0, SEEK_SET);
//	return length;
//}
//
//FILE *merge_two_files(FILE *fp1, FILE *fp2){
//	char *filename = "bc";
//	FILE *fp = fopen(filename, "w+");
//	int val1 = 0, val2 = 0;
//	fscanf(fp1, "%d", &val1);
//	fscanf(fp2, "%d", &val2);
//	while (ftell(fp1)!= length_of_file(fp1) && fseek(fp2, 0, SEEK_CUR) != length_of_file(fp2)){
//		if (val1 < val2){
//			fputc(val1, fp);
//			fputs("\n", fp);
//			fscanf(fp1, "%d", &val1);
//		}
//		else{
//			fputc(val2, fp);
//			fputs("\n", fp);
//			fscanf(fp2, "%d", &val2);
//		}
//	}
//	while (ftell(fp1)!=length_of_file(fp1)){
//		fscanf(fp1, "%d", &val1);
//		fputc(val1, fp);
//		fputs("\n", fp);
//	}
//	while (ftell(fp2)!=length_of_file(fp2)){
//		fscanf(fp2, "%d", &val2);
//		fputc(val1, fp);
//		fputs("\n", fp);
//	}
//	return fp;
//}
//
//
//FILE *generate_output_file(FILE *input){
//	FILE *file,*output;
//	int fileNum = 0;
//	fseek(input, 0, SEEK_END);
//	long int length = ftell(input);
//	fseek(input, 0, SEEK_SET);
//	char *dummy_file = dummyFileName(&fileNum);
//	output = create_dummy_file(input, max_buffer, dummy_file,length);
//	dummy_file = dummyFileName(&fileNum);
//	file = create_dummy_file(input, max_buffer, dummy_file,length);
//
//	while (ftell(input) != length){
//		output = merge_two_files(output, file);
//		file = create_dummy_file(input, max_buffer, dummyFileName(&fileNum), length);
//	}
//	fclose(file);
//	return output;
//}
//
//
//int main(){
//	FILE *input = fopen("input_file.txt", "r+");
//	FILE *output = generate_output_file(input);
//	fseek(output, 0, SEEK_END);
//	long int length = ftell(output);
//	fseek(output, 0, SEEK_SET);
//	while (ftell(output)!=length){
//		int value = 0;
//		fscanf(output, "%d", &value);
//		printf("%d\n", value);
//	}
//	fclose(input);
//	fclose(output);
//	return 0;
//}
