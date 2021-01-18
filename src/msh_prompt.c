#include "minishell.h"


int		shell()
{
	char *line;
	printf("€ ");
	fflush(stdout);
	if (get_next_line(STDIN_FILENO, &line) == -1)
		exit(0);
	return printf("msh: %s:\n", line);
}