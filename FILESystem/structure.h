#include <stdio.h>

#ifndef _structure_h
#define _structure_h

struct file{
	unsigned int offset;
	unsigned int length;
	char filename[20];
	int padding[1];
};

struct command{
	int type;
	char *src_file;
	char *dest_file;
};

#endif