#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "minishell.h"

int		err_open_file(t_word *list)
{
	if (errno == EISDIR)
		put2_str_fd(list->next->word, "  is a directory\n", 2);
	else if (errno == ENOENT)
		put2_str_fd(list->next->word, "  doesn't exit\n", 2);
	else if (errno == EACCES)
		put2_str_fd(list->next->word, "  permissions are denied\n", 2);
	else
		put2_str_fd(list->next->word, "  redirection failed\n", 2);
		return (-1);
}

int		redi_less(t_word *list)
{
	int		fd;
	int		into_fd;

	if (list->pre && list->pre->type == FD)
		fd = ft_atoi(list->pre->word);
	else
		fd = 0;
	//if (access(list->next->word, F_OK))
	into_fd = open(list->next->word, O_RDONLY);
	if (into_fd != -1)
	{
		if (dup2(into_fd, fd) < 0)
			return(return_message("dup2 failed\n", -1, 2));
		if (close(into_fd) < 0)
			return(return_message("close file failed\n", -1, 2));
	return (0);
	}
	else
		return(err_open_file(list));
}

int		redi_lessand(t_word *list)
{
	int		fd;
	int		into_fd;

	if (list->pre && list->pre->type == FD)
		fd = ft_atoi(list->pre->word);
	else
		fd = 0;
	into_fd = ft_atoi(list->next->word);
	if (dup2(into_fd, fd) < 0)
		return(return_message("bad file descriptor dup2 failed\n", -1, 2));
	if (close(into_fd) < 0)
		return(return_message("close file failed\n", -1, 2));
		return (0);
}

int		redi_lessandminus(t_word *list)
{
	int		fd;

	if (list->pre && list->pre->type == FD)
		fd = ft_atoi(list->pre->word);
	else
		fd = 0;
		if (close(fd) < 0)
		return(return_message("close file failed\n", -1, 2));
		return (0);
}
