#ifndef MAIN_H /*include gaurd to prevent header from being added 2x*/
#define MAIN_H 

#include <stdio.h> /*Standard I/O (printf, getline, etc.)*/
#include <stdlib.h> /*Memory allocation, exit, etc.*/
#include <unistd.h> /*POSIX API (fork, execve, write, etc.)*/
#include <sys/types.h> /*Type definitions (pid_t, etc.)*/
#include <sys/stat.h> /*File status (stat)*/
#include <sys/wait.h> /*Process wait (waitpid)*/
#include <string.h> /*String functions (strtok, strlen, etc.)*/
#include <signal.h> /*Signal handling*/
#include <errno.h> /*Error codes*/

#define MAX_ARGS 64 
/*increase limit to max 65 */

extern char **environ;

/* shell.c */
/** tells the main.c file that if print_prompt exists here, it takes no arguments and returns nothing. 
 * Its here so any.c file can call print_prompt without the compiler complaining. void
 * void print_prompt(void); → declaration, ends with ;, no body, lives in the header
 * void print_prompt(void) { ... } → definition, has the actual code body, lives in the .c file
 */
void print_prompt(void); 
char *trim_line(char *line); /*strip unwanted characters*/
char **split_line(char *line, char **argv); /*take cleaned string and break up into array of tokens which becomes argv*/
void print_error(char *prog, int line_no, char *cmd); /*print error to stderr when command not found*/

/* path.c */
char *get_env(const char *name);
char *find_path(char *cmd);

/* builtins.c */
int handle_builtin(char **argv, char *line, int last_status);

/* main.c */
int execute_command(char **argv, char *prog, int line_no);

#endif /* MAIN_H */
