#include<stdio.h>
#include<stdlib.h>

#ifndef _utilities_h
#define _utilities_h

int string_len(char *string);
int string_compare(char *string1, char *string2);
struct command *create_command();
int type(char *string);
struct command *command_parsing(char *command_string);

#endif