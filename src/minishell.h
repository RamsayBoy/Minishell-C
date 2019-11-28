#ifndef MINISHELL_H_INCLUDED
#define MINISHELL_H_INCLUDED

#include "parser.h"

int save_stds(int *saved_stdin, int *saved_stdout, int *saved_stderr);
int restore_stds(int saved_stdin, int saved_stdout, int saved_stderr);
void prompt();
int all_commands_exist(tline *line);
int exec_command(tline *line);
int exec_ncommands(tline *line);
void print_err_msg(char code);

#endif