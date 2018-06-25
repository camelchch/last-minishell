/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 11:51:08 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/25 11:53:54 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

t_table			*malloc_add_sh(void)
{
	t_table		*add;

	add = (t_table *)malloc(sizeof(t_table));
	ft_bzero(add->name, NAME_MAX + 1);
	ft_bzero(add->path, PATH_MAX + 1);
	add->next = NULL;
	return (add);
}
