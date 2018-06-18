
#include <signal.h>
#include "minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void	signal_inh(int sign)
{
	if (sign == SIGINT)
	{
		if (line_edition_ing)
		{
		init_attr(SETOLD);
		ft_printf("\n$> ");
		ft_bzero(new_line, MAX_BUF);
		init_line("$> ", &a_line);
		init_attr(SETNEW);
		}
		else
		init_attr(SETOLD);

	}
	if (sign == SIGQUIT)
		exit(0);
}

void	signal_quith(int sign)
{
	(void)sign;
	kill(SIGQUIT, 0);
}
