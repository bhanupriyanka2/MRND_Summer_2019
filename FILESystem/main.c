#include "structure.h"
#include "utilities.h"
#include "commands.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
	FILE *disk = fopen("disk.hdd", "rb+");
	if (disk == NULL){
		printf("Cant open hard disk\n");
		return 1;
	}
	printf("Commands:\n1.copytofs-copy file to filesystem\n2.copyfromfs - copy file from filesystem\n3.format - format disk\n4.delete - delete file from file system\n5.ls -list files\n6.exit\n");
	struct command *Command = create_command();
	int file_offset;
	int table_len, table_offset;
	while (1){
		if (fread(&table_len, sizeof(table_len), 1, disk)) {
			//printf("table len: %d\n", table_len);
		}

		if (fread(&file_offset, sizeof(file_offset), 1, disk)) {
			if (file_offset < FILEBEGIN)
				file_offset = FILEBEGIN;
			//printf("File offset: %d\n", file_offset);
		}
		printf(">>>");
		char *command = (char *)malloc(sizeof(char) * 100);
		gets(command);
		Command = command_parsing(command);
		if (Command->type == 1){
			list_of_files(table_len);
		}
		if (Command->type == 2){
			format(table_len);
		}
		if (Command->type == 3){
			table_offset = 8 + table_len * 32;
			copy_to_disk(Command->src_file,Command->dest_file, file_offset,table_len,table_offset);
		}
		if (Command->type == 4){
			copy_from_disk(Command->src_file, Command->dest_file, table_len,file_offset);
		}
		if (Command->type == 5){
			delete_file(Command->src_file, table_len);
		}
		if (Command->type == 0){
			break;
		}
		rewind(disk);
	}
	getchar();
}