#include "utilities.h"
#include "structure.h"

int string_len(char *string){
	int len = 0;
	for (len = 0; string[len] != '\0'; len++);
	return len;
}

int string_compare(char *string1, char *string2){
	int index = 0;
	//printf("%d %d", string_len(string1), string_len(string2));
	if (string_len(string1) != string_len(string2))
		return 0;
	for (index = 0; string1[index] != '\0'; index++){
		if (string1[index] != string2[index]){
			break;
		}
	}
	if (string1[index] == '\0')
		return 1;
	return 0;
}

struct command *create_command(){
	struct command *Command = (struct command *)malloc(sizeof(struct command));
	Command->src_file = (char *)malloc(sizeof(char) * 100);
	Command->dest_file= (char *)malloc(sizeof(char) * 100);
	return Command;
}

int type(char *string){
	if (string_compare("ls", string) == 1){
		return 1;
	}
	if (string_compare("format", string) == 1){
		return 2;
	}
	if (string_compare("copytofs", string) == 1){
		return 3;
	}
	if (string_compare("copyfromfs", string) == 1){
		return 4;
	}
	if (string_compare("delete", string) == 1){
		return 5;
	}
	if (string_compare("exit", string) == 1){
		return 0;
	}
	return -1;
}

struct command *command_parsing(char *command_string){
	struct command *Command = create_command();
	char *token = (char *)malloc(sizeof(char) * 100);
	int index = 0;
	while (*command_string){
		if (*command_string == ' ' || *command_string == '\t'){
			break;
		}
		token[index++] = *command_string++;
	}
	token[index] = '\0';
	Command->type = type(token);
	if (Command->type == 1 || Command->type == 2 || Command->type == 0){
		return Command;
	}
	index = 0;
	*command_string++;
	if (Command->type == 3 || Command->type == 4 || Command->type == 5){
		while (*command_string){
			if (*command_string == ' ' || *command_string == '\t'){
				break;
			}
			Command->src_file[index++] = *command_string++;
		}
		Command->src_file[index] = '\0';
		*command_string++;
		if (Command->type == 5){
			return Command;
		}
		index = 0;
		while (*command_string){
			Command->dest_file[index++] = *command_string++;
		}
		Command->dest_file[index] = '\0';
		return Command;
	}
	return Command;
}