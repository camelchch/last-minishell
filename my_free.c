/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:19:33 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/21 16:58:33 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	free_sh_table(t_sh *table, int index)
{
	int			i;
	t_table		*cp;
	t_table		*temp;

	i = 0;
	while (i < index)
	{
		if (table[i].sh_ta)
		{
			cp = table[i].sh_ta;
			while (cp)
			{
				temp = cp;
				cp = cp->next;
			free(temp);
			}
		}
		table[i].sh_ta = NULL;
		i++;
	}
}

void	ft_freestrstr(char **str)
{
	char	**temp;

	if (str)
	{
		temp = str;
		while (*str)
		{
			free(*str);
			str++;
		}
		free(temp);
	}
}

void	free_pro_args(t_program *pro, int index)
{
	int		i;

	i = -1;
	while (++i < index && pro[i].pro_args)
		free(pro[i].pro_args);
}

void	free_word_list(t_word *list)
{
	t_word *temp;

	while(list)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
}
