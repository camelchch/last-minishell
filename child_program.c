#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

static char	*path_in_sh(char *app, t_sh *table)
{
	int			index;
	t_table		*cp;

	index = calcu_index(app);
	cp = table[index].sh_ta;
	while (cp)
	{
		if (!strcmp(app, cp->name))
			return (cp->path);
		cp = cp->next;
	}
	return (NULL);
}

void	child_pro_bin(char **paras, char **env, t_sh *table)
{
	char	*path;

	if (!access(*paras, F_OK))
	{
		update_lastapp(*paras, &env);
		execve(*paras, paras, env);
		put2_str_fd(*paras, " permission denied for this program.\n", 2);
		exit(0);
	}
	path = path_in_sh(*paras, table);
	if (!path)
	{
		put2_str_fd(*paras, " there is no such program.\n", 2);
		free_sh_table(table, 100);
		ft_freestrstr(env);
		free(paras);
		exit(0);
	}
	else
	{
		update_lastapp(path, &env);
		execve(path, paras, env);
		put2_str_fd(*paras, " permission denied for this program.\n", 2);
		exit(0);
	}
}

void	child_pro_buildin(t_word *list, char **paras, char **env, t_sh *table)
{
	char	**pro_args;

	pro_args = args_each_exev(list, env);
	all_case_redirection(list);
	do_build(paras, &env, table);
	exit(0);
}

void	do_child_pro(t_word *list, char **paras, char **env, t_sh *table)
{
	if (is_buildin(list->word))
		child_pro_buildin(list, paras, env, table);
	else
		child_pro_bin(paras, env, table);
}
