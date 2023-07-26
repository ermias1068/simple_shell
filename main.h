#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

extern char **environ;

typedef struct DataShell
{
	char **arguments;
	char *input_line;
	char **args;
	int exit_status;
	int command_counter;
	char **environment;
	char *process_id;
} data_shell;

typedef struct SepListNode
{
	char separator;
	struct SepListNode *next;
} sep_list;

typedef struct LineListNode
{
	char *line;
	struct LineListNode *next;
} line_list;

typedef struct ReplaceVarList
{
	int var_length;
	char *value;
	int value_length;
	struct ReplaceVarList *next;
} r_var;

typedef struct BuiltinCommand
{
	char *name;
	int (*function)(data_shell *datash);
} builtin_t;

void clear_resources(data_shell *datash);
void initialize_data(data_shell *datash, char **arguments);
void add_separator_node_end(sep_list **head, char separator);
void free_separator_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);
r_var *add_rvar_node(r_var **head, int var_length, char *var, int value_length);
void free_rvar_list(r_var **head);
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);
void rev_string(char *s);
int repeated_char(char *input, int index);
int error_sep_operator(char *input, int index, char last_sep);
int first_char(char *input, int *index);
void print_syntax_error(data_shell *datash, char *input, int index, int bool);
int check_syntax_error(data_shell *datash, char *input);
char *read_line(int *eof);
void shell_loop(data_shell *datash);
char *without_comment(char *input);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);
void check_env(r_var **head, char *input, data_shell *data);
int check_vars(r_var **head, char *input, char *start, data_shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int new_len);
char *replace_var(char *input, data_shell *datash);
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
int exec_line(data_shell *datash);
int is_change_directory(char *path, int *index);
char *_which(char *cmd, char **environment);
int is_executable(data_shell *datash);
int check_error_cmd(char *directory, data_shell *datash);
int command_execution(data_shell *datash);
char *_getenv(const char *name, char **environment);
int env_builtin(data_shell *datash);
char *copy_info(char *name, char *value);
void set_environment_variable(char *name, char *value, data_shell *datash);
int setenv_builtin(data_shell *datash);
int unsetenv_builtin(data_shell *datash);
void dot_cd(data_shell *datash);
void cd_to(data_shell *datash);
void cd_previous(data_shell *datash);
void cd_to_home(data_shell *datash);
int cd_builtin(data_shell *datash);
int (*get_builtin(char *cmd))(data_shell *datash);
int exit_shell(data_shell *datash);
int get_len(int number);
char *int_to_string(int number);
int _atoi(char *str);
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_get_cd(data_shell *datash);
char *error_not_found(data_shell *datash);
char *error_exit_shell(data_shell *datash);
char *error_get_alias(char **arguments);
char *error_env(data_shell *datash);
char *error_syntax(char **arguments);
char *error_permission(char **arguments);
char *error_path_126(data_shell *datash);
int get_error(data_shell *datash, int eval);
void get_sigint(int sig);
void print_help_env(void);
void print_help_setenv(void);
void print_help_unsetenv(void);
void print_help_general(void);
void print_help_exit(void);
void print_help(void);
void print_help_alias(void);
void print_help_cd(void);
int print_help(data_shell *datash);

#endif /* MAIN_H */

