/*
 * OS
 * ----------------------------------------------------------------------------
 * minishell.c	is where the functions related to the operation of the shell
 * 				are placed
 * ----------------------------------------------------------------------------
 * Program: minishell
 * Author: Ramsay
 */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/parser.h"
#include "../include/minishell.h"

#define RESET_COLOR	"\x1b[0m"
#define MAGENTA_T	"\x1b[35m"

/* TODO: Function header comment */

int save_stds(int *saved_stdin, int *saved_stdout, int *saved_stderr)
{
	*saved_stdin = dup(STDIN_FILENO);
	if(*saved_stdin < 0)
	{
		fprintf(stderr, "[ERROR] There was an error trying to "
				"save stdin file descriptor\n");
		return -1;
	}

	*saved_stdout = dup(STDOUT_FILENO);
	if(*saved_stdout < 0)
	{
		fprintf(stderr, "[ERROR] There was an error trying to "
				"save stdout file descriptor\n");
		return -1;
	}

	*saved_stderr = dup(STDERR_FILENO);
	if(*saved_stderr < 0)
	{
		fprintf(stderr, "[ERROR] There was an error trying to "
				"save stderr file descriptor\n");
		return -1;
	}

	return 0;
}

/* TODO: Function header comment */

int restore_stds(int saved_stdin, int saved_stdout, int saved_stderr)
{
	if(dup2(saved_stdin, STDIN_FILENO) == -1)
	{
		fprintf(stderr, "[ERROR] There was and error "
				"trying to restore stdin initial value\n");

		return -1;
	}

	if(dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		fprintf(stderr, "[ERROR] There was and error "
				"trying to restore stdout initial value\n");

		return -1;
	}

	if(dup2(saved_stderr, STDERR_FILENO) == -1)
	{
		fprintf(stderr, "[ERROR] There was and error "
				"trying to restore stderr initial value\n");

		return -1;
	}

	return 0;
}

void prompt()
{
	printf(MAGENTA_T "msh> " RESET_COLOR);
}

/*
 * Function: all_commands_exist
 * ----------------------------------------------------------------------------
 * Check if all the line commands exist
 *
 * line: line that contains all the commands written
 *
 * returns: 1 in case that all commands written exist; 0 in other case
 */

int all_commands_exist(tline *line)
{
	int i;

	for(i = 0; i < line->ncommands; i++)
	{
		if(line->commands[i].filename == NULL)
		{
			return 0;
		}
	}

	return 1;
}

/* TODO: Function header comment */

int exec_command(tline *line)
{
	pid_t pid = fork();
	int status;

	if(pid < 0)
	{
		return 1;
	}
	else if(pid == 0)
	{
		execvp(line->commands[0].filename, line->commands[0].argv);
		exit(2);
	}
	else
	{
		wait(&status);

		if(WIFEXITED(status))
		{
			return WEXITSTATUS(status);
		}

		return 3;
	}
}

/* TODO: Function header comment */

int exec_ncommands(tline *line)
{
	/* TODO: Implement this function */
	return 0;
}

/* TODO: Function header comment */

void print_err_msg(char code)
{
	switch(code)
	{
		case 1:
			fprintf(stderr, "[ERROR] There was an error with the fork() call\n");
			break;
		case 2:
			fprintf(stderr, "[ERROR] There was a error during execvp() executation\n");
			break;
		case 3:
			fprintf(stderr, "[ERROR] Child process has not terminated normally\n");
			break;
	}
}