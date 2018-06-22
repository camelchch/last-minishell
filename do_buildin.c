#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

int		is_buildin(char *app)
{
	return (!strcmp(app, "echo") || !strcmp(app, "cd") ||\
			!strcmp(app, "setenv") || !strcmp(app, "unsetenv") ||\
			!strcmp(app, "env") || !strcmp(app, "exit"));
}

static void	echo(char **paras)
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

static void	ft_exit(void)
{
	exit(0);
}

void		replace_home(char *cp, char *home)
{
	int		i;
	char	temp[PATH_MAX + 1];

	ft_bzero(temp, PATH_MAX + 1);
	i = 0;
	while (cp[i] && cp[i] != '~')
		i++;
	ft_strcpy(temp, cp + i + 1);
	ft_bzero(cp + i, PATH_MAX + 1 - i);
	ft_strcpy(cp + i, home);
	ft_strcat(cp, temp);
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
		if (*(paras + 1) && !ft_strcmp(*(paras + 1), "PATH"))
			init_shtable(table, path(*env));
	}
	else if (!ft_strcmp(*paras, "env"))
		put_env(*env, paras, table);
	else if (!ft_strcmp(*paras, "exit"))
		ft_exit();
}
