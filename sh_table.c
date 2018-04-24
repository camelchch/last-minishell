/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 15:43:03 by saxiao            #+#    #+#             */
/*   Updated: 2018/03/22 11:55:00 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include "minishell.h"

char	*ft_getenv(char **env, char *nm)
{
	while (env && *env)
	{
		if (!ft_strncmp(*env, ft_strjoin(nm, "="), ft_strlen(nm) + 1))
			return (*env + ft_strlen(nm) + 1);
		env++;
	}
	return (NULL);
}

char	**path(char **env)
{
	while (env && *env)
	{
		if (!ft_strncmp(*env, "PATH=", 5))
	return (ft_split(*env + 5, ":"));
		env++;
	}
	return (NULL);
}

int		calcu_index(char *name)
{
	int		cal;
	int		i;

	cal = 0;
	i = 0;
	while (name[i])
		cal = name[i++] + cal;
	cal = cal % 100;
	return (cal);
}

void	addin_table(t_sh *table, t_table *add, int index)
{
		t_table		*cp;

		if (table[index].sh_ta == NULL)
			table[index].sh_ta = add;
		else
		{
			cp = table[index].sh_ta;
			while (cp->next)
				cp = cp->next;
			cp->next = add;
		}
}

void	init_shtable(t_sh *table, char **path)
{
	DIR				*dirp;
	struct dirent	*dir;
	int				index;
	t_table			*add;

	ft_bzero(table, sizeof(t_sh) * 100);
	while (path && *path)
	{
		if ((dirp = opendir(*path)))
			{
		while ((dir = readdir(dirp)))
		{
			add = (t_table *)malloc(sizeof(t_table));
			ft_strcpy(add->name, dir->d_name);
			ft_strcpy(add->path, *path);
			ft_strcat(add->path, "/");
			ft_strcat(add->path, add->name);
			add->next = NULL;
			index = calcu_index(add->name);
			addin_table(table, add, index);
		}
		}
		path++;
	}
}
