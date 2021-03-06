/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 17:40:08 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/20 15:55:30 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strcdup(char *s, char c)
{
	char *copy;
	int	 i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!(copy = (char *)malloc(i + 1)))
		return (NULL);
	i = 0;
	while (*s && *s != c)
		copy[i++] = *s++;
	copy[i] = '\0';
	return (copy);
}

static st_list		*add(st_list *list, int fd)
{
	st_list		*temp;
	st_list		*new;

	if (!(new = (st_list *)ft_memalloc(sizeof(st_list))))
		return (0);
	new->fd = fd;
	new->stock = ft_strdup("");
	new->next = NULL;
	if (!list)
		return (new);
	temp = list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (list);
}

static	st_list		*find(st_list *list, int fd)
{
	char		buff[BUFF_SIZE + 1];
	int			ret;
	char		*temp;

	while (fd != list->fd && list->next)
		list = list->next;
	if (fd != list->fd)
	{
		list = add(list, fd);
		list = list->next;
	}
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		temp = list->stock;
		buff[ret] = '\0';
		list->stock = ft_strjoin(list->stock, buff);
		free(temp);
		if (ft_strchr(buff, '\n'))
			break;
	}
	return (list);
}

int		get_next_line(const int fd, char **line)
{
	static	st_list		*list = NULL;
	st_list		*begin;
	char		*temp;

	if(fd < 0 || BUFF_SIZE < 1 || read(fd, "", 0))
		return (-1);
	if (!list)
		list = add(list, fd);
	begin = list;
	list = find(list, fd);
	if (!(*(list->stock)))
		return (0);
	if (ft_strchr(list->stock, '\n'))
	{
		temp = list->stock;
		*line = ft_strcdup(list->stock, '\n');
		list->stock = ft_strdup(ft_strchr(list->stock, '\n') + 1);
		free(temp);
	}
	else
	{
		*line = ft_strdup(list->stock);
		list->stock = "";
	}
	list = begin;
	return (1);
}
