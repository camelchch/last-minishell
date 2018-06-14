#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

void	echo(char **paras)
{
	int		ct;

	ct = nb_str(paras);
	paras++;
	while (*paras)
	{
		ft_printf("%s", *paras++);
		if (ct-- > 2)
			ft_printf(" ");
		else
			ft_printf("\n");
	}
}

void	ft_exit(void)
{
	exit(0);
}

void	do_build(char **paras, char ***env, t_sh *table)
{
	update_lastapp(*paras, env);
	if (!ft_strcmp(*paras, "cd"))
		cd(paras, env);
	else if (!ft_strcmp(*paras, "echo"))
		echo(paras);
	else if (!ft_strcmp(*paras, "setenv") || !ft_strcmp(*paras, "unsetenv"))
	{
		if (!ft_strcmp(*paras, "unsetenv"))
			*env = unset_env(paras, *env);
		else
			set_env(paras, env);
		if (!ft_strcmp((*paras + 1), "PATH"))
			init_shtable(table, path(*env));
	}
	else if (!ft_strcmp(*paras, "env"))
		put_env(*env, paras, table);
	else if (!ft_strcmp(*paras, "exit"))
		ft_exit();
}
