/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:19:33 by saxiao            #+#    #+#             */
/*   Updated: 2018/04/26 14:32:50 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	put_strstr(char **str)
{
		while(*str)
			ft_printf("%s\n", *str++);
}

void	put_env(char **env, char **paras, t_sh *table)
{
	char	*new_env[2048];
	char	**cp;
	int		i;

	paras++;
	i = 0;
	cp = env;
	new_env[0] = 0;
	if (!*paras)
		put_strstr(env);
	else if (*paras && **paras == '-')
	{
		if ((*paras)[1] == 'i')
		{
			paras++;
			while (*paras && ft_strstr(*paras, "="))
				new_env[i++] = *paras++;
			new_env[i] = NULL;
			if (*paras)
			pipes(*paras, no_pipe(*paras), new_env, table);
		}
		else if ((*paras)[1] == 'u')
		{
			cp  = env;
			while (*cp)
				new_env[i++] = *cp++;
			new_env[i] = NULL;
	cp = unset_env(paras, new_env);
			paras = paras + 2;
			put_strstr(cp);
			if (*paras)
			pipes(*paras, no_pipe(*paras), new_env, table);
			//child_pro(paras, cp, table);
		}
		else
			ft_printf("Usage: env [-u name] [-i] [name=value ...] [utlity]\n");
	}
	else
			pipes(*paras, no_pipe(*paras), env, table);
			//child_pro(paras, env, table);



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
