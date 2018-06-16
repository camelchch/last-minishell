#include "minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

void	signal_inh(int sign)
{
	if (sign == SIGINT)
		ft_printf("\n$> ");
	if (sign == SIGQUIT)
		exit(0);
}

void	signal_quith(int sign)
{
	(void)sign;
	kill(SIGQUIT, 0);
}
