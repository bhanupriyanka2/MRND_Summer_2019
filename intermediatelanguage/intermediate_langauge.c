#include "structures.h"
#include <stdlib.h>
#include <string.h>

void push(int val){
	stack[++top] = val;
}


int pop(){
	return stack[top--];
}


int string_len(char *string){
	int len = 0;
	for (len = 0; string[len] != '\0'; len++);
	return len;
}


char *remove_leading_spaces(char *string){
	int index = 0;
	for (index = 0; string[index] != '\0' && string[index] == ' '; index++);
	if (string[index] == '\0')
		return string;
	char *str = (char *)malloc(sizeof(char)*string_len(string));
	int charPos = 0;
	for (index = index; string[index] != '\0'; index++){
		str[charPos++] = string[index];
	}
	str[charPos] = '\0';
	return str;
}


int string_compare(char *string1, char *string2){
	int index = 0;
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


struct tables *update_symbol_table(char *line, struct tables *tables){
	char *token = (char *)malloc(sizeof(char) * 100);
	char *mnemonic = (char *)malloc(sizeof(char) * 6);
	int index = 0;
	while (*line){

		if (*line == ' '){
			break;
		}
		token[index++] = *line++;
	}
	*line++;
	token[index] = '\0';
	strcpy(mnemonic, token);
	index = 0;
	int size = 1;
	while (*line != '\n'){
		if (*line == '[' || *line == '='){
			break;
		}
		token[index++] = *line++;
	}
	token[index] = '\0';
	if (*line == '[' || *line == '='){
		*line++;
		if (*line == ' '){
			*line++;
		}
		size = *line - '0';
	}
	tables->symbol_index = tables->symbol_index + 1;
	int len = string_len(token);
	if (token[len - 1] == ' ')
		token[len - 1] = '\0';

	strcpy(tables->symbol_table[tables->symbol_index].variable, token);
	tables->symbol_table[tables->symbol_index].address = tables->symbol_table[tables->symbol_index - 1].size + tables->symbol_table[tables->symbol_index - 1].address;
	
	if (string_compare(mnemonic, "CONST") == 1){
		tables->symbol_table[tables->symbol_index].size = 0;
		tables->memory[tables->symbol_table[tables->symbol_index].address] = size;
		return tables;
	
	}
	tables->symbol_table[tables->symbol_index].size = size;
	return tables;
}


int get_opcode(char *token){
	if (string_compare("MOV", token) == 1){
		return 0;
	}
	if (string_compare("ADD", token) == 1){
		return 3;
	}
	if (string_compare("SUB", token) == 1){
		return 4;
	}
	if (string_compare("MUL", token) == 1){
		return 5;
	}
	if (string_compare("JUMP", token) == 1){
		return 6;
	}
	if (string_compare("IF", token) == 1){
		return 7;
	}
	if (string_compare("EQ", token) == 1){
		return 8;
	}
	if (string_compare("LT", token) == 1){
		return 9;
	}
	if (string_compare("GT", token) == 1){
		return 10;
	}
	if (string_compare("LTEQ", token) == 1){
		return 11;
	}
	if (string_compare("GTEQ", token) == 1){
		return 12;
	}
	if (string_compare("PRINT", token) == 1){
		return 13;
	}
	if (string_compare("READ", token) == 1){
		return 14;
	}
	return 15;
}


int get_address(char *token, struct tables *tables){
	for (int index = 0; index < 7; index++){
		if (string_compare(token, tables->register_array[index]) == 1){
			return index;
		}
	}
	int size = 0;
	for (int index = 1; index <= tables->symbol_index; index++){
		int index1 = -1;
		for (int i = 0; token[i] != '\0'; i++)
		{
			if (token[i] == '['){
				index1 = i;
				break;
			}
		}
		if (index1 != -1){
			for (int i = index1 + 1; token[i] != '\0'; i++)
			{
				if (token[i] == ']')
					break;
				size = (size * 10) + (token[i] - '0');
			}
			token[index1] = '\0';
		}
		if (string_compare(token, tables->symbol_table[index].variable) == 1){
			return  tables->symbol_table[index].address + size;
		}
	}
	for (int index = 0; index < tables->block_index; index++){
		if (string_compare(token, tables->block_table[index].block_name) == 1){
			return tables->block_table[index].block_address;
		}
	}
	int opcode = get_opcode(token);
	if (opcode != 15)
		return opcode;
	return -1;
}


struct tables *update_tables(char *line, struct tables *tables){
	char *token = (char *)malloc(sizeof(char) * 100);
	int index = 0;
	token = strtok(line, " \n");
	int opcode = get_opcode(token);
	int arg_ind = 0;
	if (opcode == 15){
		token = strtok(line, ":");
		strcpy(token, remove_leading_spaces(token));
		if (string_compare(token, "ELSE") == 1){
			tables->instruction_table[tables->instruction_index].instr_num = tables->instruction_index;
			tables->instruction_table[tables->instruction_index].opcode = 6;
			tables->instruction_table[tables->instruction_index].arg[0] = -1;
			push(tables->instruction_table[tables->instruction_index].instr_num);
			tables->instruction_index++;
			return tables;
		}
		else if (string_compare(token, "ENDIF") == 1){
			int in = tables->instruction_index;
			while (top != -1 && tables->instruction_table[stack[top]].opcode!=7){
				int val = pop();
				for (int i = 0; i < 4; i++){
					if (tables->instruction_table[val].arg[i] == -1){
						tables->instruction_table[val].arg[i] = in;
						break;
					}
				}
				in = val + 1;
			}
			if (top != -1){
				int val = pop();
				for (int i = 0; i < 4; i++){
					if (tables->instruction_table[val].arg[i] == -1){
						tables->instruction_table[val].arg[i] = in;
						break;
					}
				}
				in = val + 1;
			}
			return tables;
		}
		tables->block_table[tables->block_index].block_address = tables->instruction_index + 1;
		strcpy(tables->block_table[tables->block_index].block_name, token);
		tables->block_index++;
		return tables;
	}
	if (opcode == 0)
	{
		token = strtok(NULL, ",\n");
		int len = string_len(token);
		if (token[len - 1] == 'X')
			opcode = 2;
		else
			opcode = 1;
		int address = get_address(token, tables);
		tables->instruction_table[tables->instruction_index].arg[arg_ind++] = address;
	}
	tables->instruction_table[tables->instruction_index].instr_num = tables->instruction_table[tables->instruction_index - 1].instr_num + 1;
	tables->instruction_table[tables->instruction_index].opcode = opcode;
	while (1){
		token = strtok(NULL, ", \n");
		if (token == NULL){
			break;
		}
		int address = get_address(token, tables);
		tables->instruction_table[tables->instruction_index].arg[arg_ind++] = address;
	}
	if (opcode == 7){
		push(tables->instruction_table[tables->instruction_index].instr_num);
	}
	tables->instruction_index++;
	return tables;
}


struct tables* line_parsing(FILE *file, struct tables *tables){
	if (file == NULL){
		printf("File doesn't exist\n");
		return;
	}
	int length = 0;
	char *line = (char *)malloc(sizeof(char) * 60);
	char *token = (char *)malloc(sizeof(char) * 6);
	int index = 0;
	while (fgets(line, 60, file) != NULL){
		if (string_compare(line, "START:\n") == 1){
			break;
		}
		tables = update_symbol_table(line, tables);
	}
	while (fgets(line, 60, file) != NULL){
		tables = update_tables(line, tables);
	}
	return tables;
}

int get_number_of_operands(int opcode){
	if (opcode == 6 || opcode == 13 || opcode == 14){
		return 1;
	}
	if (opcode == 1 || opcode == 2){
		return 2;
	}
	if (opcode == 3 || opcode == 4 || opcode == 5){
		return 3;
	}
	if (opcode == 7){
		return 4;
	}
}

void write_tables_to_file(char *filename, struct tables *tables){
	FILE *output = fopen(filename, "w");
	if (output == NULL){
		printf("Can't write to file\n");
		return;
	}
	for (int index = 1; index < tables->instruction_index; index++){
		int num_of_operands = get_number_of_operands(tables->instruction_table[index].opcode);
		fprintf(output, "%d ", tables->instruction_table[index].instr_num);
		fprintf(output, "%d ", tables->instruction_table[index].opcode);
		if (tables->instruction_table[index].opcode == 7){
			fprintf(output, "%d %d %d %d", tables->instruction_table[index].arg[0], tables->instruction_table[index].arg[2], tables->instruction_table[index].arg[1], tables->instruction_table[index].arg[3]);
		}
		else{
			for (int arg_index = 0; arg_index < num_of_operands; arg_index++){
				fprintf(output, "%d ", tables->instruction_table[index].arg[arg_index]);
			}
		}
		fputs("\n", output);
	}
	fclose(output);
}

struct tables *init(){
	struct tables *tables = (struct tables *)malloc(sizeof(struct tables));
	tables->block_index = 0;
	tables->symbol_index = 0;
	tables->instruction_index = 1;
	tables->symbol_table[0].size = 0;
	tables->symbol_table[0].address = 0;
	tables->block_table[0].block_address = 0;
	tables->instruction_table[0].instr_num = 0;
	tables->register_array[0] = "AX";
	tables->register_array[1] = "BX";
	tables->register_array[2] = "CX";
	tables->register_array[3] = "DX";
	tables->register_array[4] = "EX";
	tables->register_array[5] = "FX";
	tables->register_array[6] = "GX";
	return tables;
}

int main(){
	FILE *file = fopen("max_of_3.txt", "r");
	if (file == NULL){
		printf("Can't open file\n");
	}
	struct tables *tables = init();
	tables=line_parsing(file, tables);
	write_tables_to_file("max_of_3_opcode.txt",tables);
	fclose(file);
	return 0;
}