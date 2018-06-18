/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:19:33 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/18 15:05:47 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static void	free_sh_table(t_sh *table, int index)
{
	int			i;
	t_table		*cp;

	i = 0;
	while (i < index)
	{
		while (table[i].sh_ta)
		{
			cp = table[i].sh_ta;
			while (cp->next)
				cp = cp->next;
			free(cp);
		}
		i++;
	}
}

static char	**copy_env(char **env)
{
	char	**cp;
	char	**res;
	int		ct;
	int		i;

	i = 0;
	ct = nb_str(env) + 1;
	cp = env;
	res = malloc(sizeof(char *) * ct);
	while (i < ct - 1)
		(res)[i++] = ft_strdup(*cp++);
	res[i] = NULL;
	return (res);
}

static void	ft_freestrstr(char **str)
{
	char	*temp;
	char	**cp;

	if (str)
	{
		cp = str;
		while (*str)
		{
			temp = *str;
			str++;
			free(temp);
		}
		free(cp);
	}
}

int		main(int ac, char **av, char **env)
{
	t_sh	table[100];
	char	**all_path;
	char	**cp_env;

	//	put_env(env);
	(void)ac;
	(void)av;
	signal(SIGINT, signal_inh);
	cp_env = copy_env(env);
	update_shlvl(&cp_env);
	all_path = path(cp_env);
	init_shtable(table, all_path);
	//	put_sh(table);
	prompt(env, table);
	//	get_autoline(table);
	free_sh_table(table, 100);
	ft_freestrstr(cp_env);
	return (0);
}
