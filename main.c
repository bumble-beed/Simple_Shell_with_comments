#include "main.h"

/**
 * main entry point
 *
 * while to create a loop 
 **/
int main(int ac, char **av, char **env)
/**
 * tools that main needs - i
 */
{
	char *line = NULL; /*buffer where raw user input stored. Set to NULL as getline will handle memory allocation*/
	size_t len = 0; /*track size of allocated buffer. How much memory set aside. Set to 0 so getline allocates fresh*/
	ssize_t nread; /*store # of characters actually read*/
	pid_t child_pid; /*storage of process ID returned by fork*/
	char *argv[MAX_ARGS]; /*when command is spilt, this is where they end up e.g. ls -la becomes 2 arrays*/
	char *start; /*pointer used to walk past leading spaces*/
	int j; /*loop counter, for trimming trailing space*/
	int i; /*loop counter for filling argv tokens with strtok*/

	(void)ac;

	while (1) /*infinite loop*/
	{
        /* only print prompt if input from real person, only shows ($) if human*/
		if (isatty(STDIN_FILENO))
			print_prompt();
		/*waits for user to type something in and hit enter*/
		nread = getline(&line, &len, stdin);
		if (nread == -1) /* Exit - Ctrl+D or EOF - print newline, free memory, exit cleanly */
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			free(line);
			exit(0);
		}

		if (line[nread - 1] == '\n') /*remove trailing line \n from input */
			line[nread - 1] = '\0'; /*string ends here - to clean out the input to terminal friendy*/

		/* 1. Trim trailing spaces */
		j = 0; /*start at beginning of string "ls -la   "*/
		while (line[j] != '\0') /* walk to end of string */
			j++;
		j--; /*step back to last actual character */
		while (j >= 0 && line[j] == ' ') /*safety guard - stops it from looping to the beginning, or going into negative */
		{
			line[j] = '\0'; /*replace trailing space with end of string */
			j--; /*move backwards */
		}

		/* 2. Skip leading spaces */
		start = line; /* point start at beginning of string */
		while (*start == ' ') /* is current character a space */
			start++; /* move forward past space to next char*/

		/* If the line was only spaces, don't try to execute */
		if (*start == '\0')
			continue;
		i = 0;
		argv[i] = strtok(start, " ");
		while (argv[i] != NULL)
		{
			i++;
			argv[i] = strtok(NULL, " ");
		}
		child_pid = fork(); /* create fork - child process */
		if (child_pid == -1) /* if fork fails */
		{
			perror("Error"); /*print error */
			free(line); /* clean up memory */
			return (1); /* exit with failure */
		}

		if (child_pid == 0)
		{
			/* Use 'start' (the cleaned path), not 'line' */
			if (execve(argv[0], argv, env) == -1)
			{
				perror(av[0]);
				free(line);
				exit(1);
			}
		}
		else
		{
			wait(NULL);
		}
	}
	free(line);
	return (0);
}
