/*
 * OS
 * ----------------------------------------------------------------------------
 * main.c is where the main program is placed
 * ----------------------------------------------------------------------------
 * Program: minishell
 * Author: Ramsay
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "parser.h"
#include "minishell.h"
#include "ramsayboy.h"

#define BUFFER_SIZE	1024

int main()
{
	char buffer[BUFFER_SIZE];
	tline *line;
	int saved_stdin, saved_stdout, saved_stderr;

	/* Save the default values for std in, out and err */
	if(save_stds(&saved_stdin, &saved_stdout, &saved_stderr) == -1)
	{
		fprintf(stderr, "[ERROR] There was an error trying to save"
					"the value/s of stdin, stdout or/and stderr\n");
	}

	print_author_name();
	prompt();

	while(fgets(buffer, BUFFER_SIZE, stdin))
	{
		line = tokenize(buffer);

		if(strlen(buffer) > 1)
		{
			/* TODO: Function for redirecting input code */
			if(line->redirect_input)
			{
				int file_descr;

				if((file_descr = open(line->redirect_input, O_RDONLY)) == -1)
				{
					fprintf(stderr, "[ERROR] The redirect input has failed\n");
					prompt();
					continue;
				}
				else
				{
					if(dup2(file_descr, STDIN_FILENO) == -1)
					{
						fprintf(stderr, "[ERROR] There was and error "
								"trying to use dup2 with stdin\n");
					}

					if(file_descr != STDIN_FILENO)
					{
						if(close(file_descr) == -1)
						{
							fprintf(stderr, "[ERROR] There was an error trying to "
									"close a file descriptor\n");
						}
					}
				}
			}

			/* TODO: Function for redirecting output code */
			if (line->redirect_output)
			{
				int file_descr;

				if((file_descr = open(line->redirect_output, O_WRONLY | O_TRUNC
					| O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
				{
					fprintf(stderr, "[ERROR] The redirect output has failed\n");
					prompt();
					continue;
				}
				else
				{
					if(dup2(file_descr, STDOUT_FILENO) == -1)
					{
						fprintf(stderr, "[ERROR] There was and error "
								"trying to use dup2 with stdout\n");
					}

					if(file_descr != STDOUT_FILENO)
					{
						if(close(file_descr) == -1)
						{
							fprintf(stderr, "[ERROR] There was an error trying to "
									"close a file descriptor\n");
						}
					}
				}
			}

			if (line->redirect_error)
			{
				/* TODO: Fix redirect error */
				int file_descr;

				if((file_descr = open(line->redirect_error, O_WRONLY | O_TRUNC
					| O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
				{
					fprintf(stderr, "[ERROR] The redirect error has failed\n");
					prompt();
					continue;
				}
				else
				{
					if(dup2(file_descr, STDERR_FILENO) == -1)
					{
						fprintf(stderr, "[ERROR] There was and error "
								"trying to use dup2 with stderr\n");
					}

					if(file_descr != STDERR_FILENO)
					{
						if(close(file_descr) == -1)
						{
							fprintf(stderr, "[ERROR] There was an error trying to "
									"close a file descriptor\n");
						}
					}
				}
			}

			if (line->background)
			{
				/* TODO: Implement this */
			}

			if(strcmp(line->commands->argv[0], "exit") == 0)
			{
				return 0;
			}
			else if(strcmp(line->commands->argv[0], "cd") == 0)
			{
				/* TODO: Implements CD command */
				puts("cd not implemented yet");
			}
			else if(all_commands_exist(line))
			{
				char exit_code = 0;

				if(line->ncommands < 2)
				{
					exit_code = exec_command(line);
				}
				else
				{
					/* TODO: exec_ncommands */
					exit_code = exec_ncommands(line);
				}

				if(exit_code)
				{
					print_err_msg(exit_code);
				}
			}
			else
			{
				fprintf(stderr, "[ERROR] Some command or commands could not be found\n");
			}
		}

		/* Restore the default values for std in, out and err */
		if(restore_stds(saved_stdin, saved_stdout, saved_stderr) == -1)
		{
			fprintf(stderr, "[ERROR] There was an error trying to restore"
					"the value/s of stdin, stdout or/and stderr\n");
		}

		prompt();
	}

	return 0;
}