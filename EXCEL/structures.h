#include <stdio.h>
#include <stdlib.h>

#ifndef _structures_h
#define _structures_h


struct command {
	int val;
	int type;
	char *cell;
	char *expression;
	char *file_name;
};

struct cell {
	int data;
	char *string_data;
	char *expression;
};

#endif