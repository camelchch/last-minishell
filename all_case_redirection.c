#include <fcntl.h>
#include <unistd.h>
#include "minishell.h"

int		redi_great(t_word *list)
{
	int		fd;
	int		into_fd;

	if (list->pre && list->pre->type == FD)
		fd = ft_atoi(list->pre->word);
	else
		fd = 1;
	into_fd = open(list->next->word, O_CREAT | O_TRUNC | O_RDWR, S_IWUSR | S_IRUSR);
	if (into_fd != -1)
	{
		if (dup2(into_fd, fd) < 0)
			return(return_message("dup2 failed\n", -1, 2));
		if (close(into_fd) < 0)
			return(return_message("close file failed\n", -1, 2));
			return (0);
	}
	else
		return (err_open_file(list));
}

int		redi_dgreat(t_word *list)
{
	int		fd;
	int		into_fd;

	if (list->pre && list->pre->type == FD)
		fd = ft_atoi(list->pre->word);
	else
		fd = 1;
	into_fd = open(list->next->word, O_CREAT | O_APPEND | O_RDWR, S_IWUSR | S_IRUSR);
	if (into_fd != -1)
	{
		if (dup2(into_fd, fd) < 0)
			return(return_message("dup2 failed\n", -1, 2));
		if (close(into_fd) < 0)
			return(return_message("close file failed\n", -1, 2));
			return (0);
	}
	else
		return (err_open_file(list));
}

int		redi_greatand(t_word *list)
{
	int		fd;
	int		into_fd;

	if (list->pre && list->pre->type == FD)
		fd = ft_atoi(list->pre->word);
	else
		fd = 1;
	if (list->next->type == FD)
		into_fd = ft_atoi(list->next->word);
	else
	into_fd = open(list->next->word, O_CREAT | O_APPEND | O_RDWR, S_IWUSR | S_IRUSR);
	if (into_fd != -1)
	{
		if (dup2(into_fd, fd) < 0)
			return(return_message("dup2 failed\n", -1, 2));
		if (close(into_fd) < 0)
			return(return_message("close file failed\n", -1, 2));
			return (0);
	}
	else
	{
		if (list->next->type == FD)
			return (return_message("bad descriptor\n", -1, 2));
		else
			return (err_open_file(list));
	}
}

int		redi_greatandminus(t_word *list)
{
	int		fd;

	if (list->pre && list->pre->type == FD)
		fd = ft_atoi(list->pre->word);
	else
		fd = 1;
		if (close(fd) < 0)
			return (return_message("bad descriptor close failed\n", -1, 2));
		return (0);
}

int		all_case_redirection(t_word *list)
{
	int		res;

	while (list && !is_logic(list->type) && list->type != SEMI_DOT && list->type != PIPE)
	{
		if (list->type == GREAT)
			res = redi_great(list);
		else if (list->type == DGREAT)
			res = redi_dgreat(list);
		else if (list->type == GREATAND)
			res = redi_greatand(list);
		else if (list->type == GREATANDMINUS)
			res = redi_greatandminus(list);
		else if (list->type == LESS)
			res = redi_less(list);
		else if (list->type == LESSAND)
			res = redi_lessand(list);
		else if (list->type == LESSANDMINUS)
			res = redi_lessandminus(list);
		if (res < 0)
			return (-1);
		list = list->next;
	}
	return (0);
}
