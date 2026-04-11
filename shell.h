#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

char **clean_getline(char **lineptr);
char **stroke_getline(char *command_line);
char *no_new_line(char *impious_line);
void print_array(char **s);
char *_strdup(char *str);
void free_array(char **grid);
int get_strlenght(char *s);
char **get_clean_path_directories(char **env);
int count_double_dot(char *s);
int array_lenght(char **array);
int fork_and_launch(char *path, char **prompt);
void free_everything(char *buff, char **prompt, char **dir_path);
int print_error_message(char *shell_name, char **command, int loop_count);
int get_dir_lenght(char *s1, char *s2);
int launch_with_dir(char **prompt);
int launch_with_command(int how_many_dir_in_path, char **prompt_command, char **path_directories);
char *get_path_from_env(char **env);
int is_build_in(char **prompt_command);
int build_in_centralizer(int build_int, char **prompt_command, char *lineptr, int actual_return);
int exit_build_in(char **prompt_command, char *lineptr, int actual_return);
int env_build_in();
int _strcmp(char *s1, char *s2);
#endif