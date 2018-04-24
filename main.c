/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:19:33 by saxiao            #+#    #+#             */
/*   Updated: 2018/03/22 17:25:23 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	put_env(char **env)
{
	while(*env)
		ft_printf("%s\n", *env++);
}

void	put_intable(t_table *in_tab)
{
	while (in_tab)
	{
		ft_printf("%s\n", in_tab->name);
		in_tab = in_tab->next;
	}
}

void	put_sh(t_sh *table)
{
	int		i;

	i = 0;
	while (i < 100)
	{
		if (table[i].sh_ta)
		{
			ft_printf("here is %d sh_table\n",i);
			put_intable(table[i].sh_ta);
			i++;
		}
	}
}

int		main(int ac, char **av, char **env)
{
	t_sh	table[100];
	char	**all_path;

//	put_env(env);
	(void)ac;
	(void)av;
	all_path = path(env);
	init_shtable(table, all_path);
//	put_sh(table);
	shell(ac, av, env, table);
//	get_autoline(table);
	return (0);
}
