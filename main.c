/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:19:33 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/21 17:24:52 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

static char	**copy_env(char **env)
{
	char	**cp;
	char	**res;
	int		ct;
	int		i;

	i = -1;
	ct = nb_str(env) + 1;
	cp = env;
	res = malloc(sizeof(char *) * ct);
	while (++i < ct - 1)
		(res)[i] = ft_strdup(cp[i]);
	res[i] = NULL;
	return (res);
}

int		main(int ac, char **av, char **env)
{
	t_sh	table[100];
	char	**all_path;
	char	**cp_env;

	//	put_env(env);
	(void)ac;
	(void)av;
	cp_env = NULL;
	signal(SIGINT, signal_inh);
	cp_env = copy_env(env);
	update_shlvl(&cp_env);
	all_path = path(cp_env);
	init_shtable(table, all_path);
	//	put_sh(table);
	prompt(cp_env, table);
	//	get_autoline(table);
	free_sh_table(table, 100);
	ft_freestrstr(cp_env);
	return (0);
}
