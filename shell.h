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

char **clean_getline(void);
char **stroke_getline(char *command_line);
char *no_new_line(char *impious_line);
void print_array(char **s);
char *_strdup(char *str);
void free_array(char **grid);
int get_strlenght(char *s);
char **get_clean_path_directories(void);
int count_double_dot(char *s);
int array_lenght(char **array);
int fork_and_launch(char *path, char **prompt);
void free_everything(char *buff, char **prompt, char **dir_path);
void exit_if_more_than_two(int args);
void free_and_exit_null_prompt(char **prompt);
int get_dir_lenght(char *s1, char *s2);
#endif