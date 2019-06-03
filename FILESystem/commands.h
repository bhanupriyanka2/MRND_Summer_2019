#include <stdio.h>

#ifndef _commands_h
#define _commands_h
#define FILEBEGIN 3000000

void copy_from_disk(char *src_file, char *dest_file, int table_len);
void copy_to_disk(char *src_file, char *dest_file, int file_offset, int table_len, int table_offset);
void copy_file(FILE *input, char *dest_file, int file_offset, int table_offset);
int file_len(FILE *file);
void add_file_entry(char *input_file, int file_offset, int table_offset);
void list_of_files(int table_len);
void format();
void delete_file(char *filename,int table_len);

#endif