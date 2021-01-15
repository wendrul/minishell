#include "minishell.h"


int		shell(t_shell sh)
{
	write(1, "$ ", 2);

	sh->i = 0;
	sh->buf[sh->i] = '\0';
	while (1)
	{
		sh->i += read(STDIN_FILENO, sh->buf, MSH_BUFF_SIZE);
		sh->buf[sh->i] = '\0';
		int j;
		if ((j = ft_indexof('\n', sh->buf)))
		{
			sh->buf[j] = '\0';
			break ;
		}
	}
	if (ft_strncmp(sh->buf, "exit", 4) == 0)
		exit(0);
	return printf("msh: %s:\n", sh->buf);
}