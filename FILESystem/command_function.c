#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "utilities.h"
#include "commands.h"


int file_len(FILE *file){
	if (file == NULL){
		printf("No file");
		return -1;
	}
	fseek(file, 0L, SEEK_END);
	int length = ftell(file);
	return length;
}

void delete_file(char *filename, int table_len){
	int count = 0;
	struct file entry1, entry2;
	FILE *disk = fopen("disk.hdd", "rb+");
	if (disk == NULL){
		printf("Can't read disk\n");
		return;
	}
	fseek(disk, 8, SEEK_SET);
	while (count < table_len){
		fread(&entry1, sizeof(struct file), 1, disk);
		if (string_compare(entry1.filename, filename) == 1){
			break;
		}
		count++;
	}
	if (count == table_len){
		printf("Specified file doesn't exist in disk\n");
		return;
	}
	if (count == table_len - 1){
		table_len -= 1;
		fseek(disk, 0, SEEK_SET);
		fwrite(&table_len, sizeof(table_len), 1, disk);
		fclose(disk);
		return;
	}
	while (count < table_len - 1){
		fread(&entry2, sizeof(struct file), 1, disk);
		count++;
	}
	strcpy(entry1.filename, entry2.filename);
	entry1.length = entry2.length;
	entry1.offset = entry2.offset;
	table_len -= 1;
	fseek(disk, 0, SEEK_SET);
	fwrite(&table_len, sizeof(table_len), 1, disk);
	fseek(disk, 8, SEEK_SET);
	fwrite(&entry1, sizeof(struct file), 1, disk);
	fclose(disk);
	return;
}

void format(){
	FILE *disk = fopen("disk.hdd", "rb+");
	int table_len = 0;
	if (disk == NULL){
		printf("Cant format disk\n");
		return;
	}
	fseek(disk, 0, SEEK_SET);
	fwrite(&table_len, sizeof(table_len), 1, disk);
	int file_offset = FILEBEGIN;
	fseek(disk, 4, SEEK_SET);
	fwrite(&file_offset, sizeof(file_offset), 1, disk);
	fclose(disk);
}


void add_file_entry(char *input_file, int file_offset, int table_offset,FILE *src_file) {
	struct file entry;
	int index = 0;
	while (input_file[index] && input_file[index] != '\n') {
		entry.filename[index] = input_file[index];
		index++;
	}

	entry.filename[index] = '\0';

	entry.offset = (unsigned)file_offset;
	entry.length = (unsigned)file_len(src_file);

	FILE *output = fopen("disk.hdd", "rb+");
	if (!output) {
		printf("add entry: harddisk is null");
	}
	else {
		fseek(output, table_offset, SEEK_SET);
		fwrite(&entry, sizeof(entry), 1, output);
	}

	fclose(output);

}

void copy_file(FILE *input, char *dest_file, int file_offset, int table_offset){
	if (input == NULL){
		printf("Can't open source file\n");
		return;
	}
	FILE *output = fopen("disk.hdd", "rb+");
	if (output == NULL){
		printf("Can't write to desitnation file\n");
		return;
	}
	fseek(output, file_offset, SEEK_SET);
	char ch;
	while (fread(&ch, sizeof(char), 1, input)){
		fwrite(&ch, sizeof(char), 1, output);
	}
	fclose(output);
	add_file_entry(dest_file, file_offset, table_offset,input);
}


void list_of_files(int table_len){
	int count = 0;
	FILE *disk = fopen("disk.hdd", "rb+");
	if (disk == NULL){
		printf("No disk to list files\n");
		return;
	}
	fseek(disk, 8, SEEK_SET);
	struct file entry;
	while (count < table_len){
		int pos = ftell(disk);
		if (fread(&entry, sizeof(struct file), 1, disk)){
			//printf("%d\n", pos);
			printf("%s\n", entry.filename);
			count++;
		}
	}
	fclose(disk);
}

void copy_to_disk(char *src_file, char *dest_file, int file_offset,int table_len,int table_offset){  
	FILE *disk = fopen("disk.hdd", "rb+");
	table_offset = 8 + table_len * 32;
	FILE *input = fopen(src_file, "rb+");

	copy_file(input,dest_file, file_offset, table_offset);

	table_len += 1;
	fseek(disk, 0, SEEK_SET);
	fwrite(&table_len, sizeof(table_len), 1, disk);

	file_offset += file_len(input)+1;
	fseek(disk, 4, SEEK_SET);
	fwrite(&file_offset, sizeof(file_offset), 1, disk);
	fclose(input);
	fclose(disk);
}

void copy_from_disk(char *src_file, char *dest_file, int table_len){
	int count = 0;
	struct file entry;
	FILE *disk = fopen("disk.hdd", "rb+");
	if (disk == NULL){
		printf("Can't read disk\n");
		return;
	}
	FILE *output = fopen(dest_file, "wb");
	if (output == NULL){
		printf("Can't write to output\n");
	}
	fseek(disk, 8, SEEK_SET);
	while (count < table_len){
		fread(&entry, sizeof(struct file), 1, disk);
		if (string_compare(entry.filename, src_file) == 1){
			break;
		}
		count++;
	}
	if (count == table_len){
		printf("Specified file doesn't exist in disk\n");
		return;
	}
	fseek(disk, entry.offset, SEEK_SET);
	char ch;
	unsigned int position = entry.offset;
	while (position < entry.length + entry.offset){
		fread(&ch, sizeof(char), 1, disk);
		fwrite(&ch, sizeof(char), 1, output);
		position++;
	}
	fclose(disk);
	fclose(output);
}