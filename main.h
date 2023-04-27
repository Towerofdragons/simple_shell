#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#include "macros.h"

typedef struct program_data
{
    char *prog_name;
    char *input_str;
    char *cmd_name;
    int cmd_count;
    int file_desc;
    char **tokens;
    char **env_vars;
    char **alias_arr;
} program_data;

typedef struct builtin_cmds
{
    char *cmd_name;
    int (*func)(program_data *data);
} builtin_cmds;

void init_data(program_data *data, int argc, char *argv[], char **env);
void run_sisifo(char *prompt, program_data *data);
void handle_sigint(int sig UNUSED);

int get_input_line(program_data *data);
int check_logical_ops(char *cmd_array[], int i, char op_array[]);

void expand_vars(program_data *data);
void expand_aliases(program_data *data);
int add_to_buffer(char *buffer, char *str_to_add);

void tokenize_input(program_data *data);
char *_strtok(char *line, char *delim);
int execute_cmd(program_data *data);

int check_builtins(char *full_path);

char **tokenize_path(program_data *data);

int search_program(program_data *data);

void free_pointer_array(char **dirs);
void free_recur_data(program_data *data);
void free_all(program_data *data);

int exit_cmd(program_data *data);
int cd_cmd(program_data *data);
int set_working_dir(program_data *data, char *new_dir);

int help_cmd(program_data *data);
int alias_cmd(program_data *data);

int env_cmd(program_data *data);
int set_env_cmd(program_data *data);
int unset_env_cmd(program_data *data);

char *get_env_key(char* name, program_data* data);
int set_env_key(char* key, char* value, program_data* data);
int remove_env_key(char* key, program_data* data);

void print_env_vars(program_data* data);

int print_str(char* str);
int print_err_str(char* str);
int print_error_msg(int err_code, program_data* data);

int str_len(char* str);
char* str_dup(char* str);
int str_cmp(char* str1, char* str2, int num_chars);
char* str_cat(char* str1, char* str2);

void reverse_str(char* str);
void convert_long_to_str(long num, char* str, int base);
int str_to_int(char* s);

int count_chars(char* str, char* char_to_count);
int print_alias_value(program_data* data, char* alias_name);
char* get_alias_value(program_data* data, char* alias_name);
int set_alias_value(char* alias_str, program_data* data);

int builtin_exit(program_data *data);

int builtin_cd(program_data *data);

int set_work_directory(program_data *data, char *new_dir);

int builtin_help(program_data *data);

int builtin_alias(program_data *data);


/*======== builtins_env.c ========*/

int builtin_env(program_data *data);

int builtin_set_env(program_data *data);


int builtin_unset_env(program_data *data);


#endif
