/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:19:33 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/21 13:48:31 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

void	free_sh_table(t_sh *table, int index)
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

void	ft_freestrstr(char **str)
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
