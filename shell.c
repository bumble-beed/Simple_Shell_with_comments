#include "main.h"

/**
 * print_prompt - handles displaying the shell prompt to user, printf($) shows that the user will see $ on terminal
 *
 * fflush(stdout) is needed as printf doesnt write to terminal immediately because stdout is line buffered. So its waiting for new \n to indicate new line however prompt string has no \n. So fflush stdout forces everything to buffer out in terminal righ now.
 * Also on new file shell.c due to 5 function limit
 * 
 * Return: void
 */
void print_prompt(void)
{
	printf("($) ");
	fflush(stdout);
}