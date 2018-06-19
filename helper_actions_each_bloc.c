#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

int		nb_pipe_eachbloc(t_word *list)
{
	int		i;

	i = 0;
	while (list && !is_logic(list->type) && list->type != SEMI_DOT)
	{
		if (list->type == PIPE)
			i++;
		list = list->next;
	}
	return (i);
}

static int		nb_args_each_exev(t_word *list)
{
	int		i;

	i = 0;
	while (list && !is_logic(list->type) && list->type != SEMI_DOT && list->type != PIPE)
	{
		if (list->type == PROGRAM || list->type == BUIDIN || list->type == ARG)
			i++;
		list = list->next;
	}
	return (i);
}

char	**args_each_exev(t_word *list, char **env)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * (nb_args_each_exev(list) + 1));
	while (list && !is_logic(list->type) && list->type != SEMI_DOT && list->type != PIPE)
	{
		if (list->type == PROGRAM || list->type == BUIDIN || list->type == ARG)
			res[i++] = list->word;
		list = list->next;
	}
	res[i] = 0;
	return(res);
}

int		close_all_pipe(int *pipe_fd, int nb_pipe, int nb_pro)
{
	int		i;

	i = 0;
	while (i < nb_pipe * 2)
	{
		if ((nb_pro && i != nb_pro *2 -2 ) || (nb_pro < nb_pipe && i != nb_pro *2 + 1))
		{
			if (close(pipe_fd[i] < 0))
			{
				ft_printf("close failed in close_all_pipe i=%d nb_pro=%d\n", i, nb_pro);
				perror("close failed");
			}
		}
		i++;
	}
	return (0);
}

int		do_all_redirection(t_word *list, int *pipe_fd, int nb_pipe, int nb_pro)
{
	if (nb_pipe)
	{
		if (nb_pro)
		{
			if (dup2(pipe_fd[nb_pro * 2 - 2], 0) < 0)
				return(return_message("dup failed\n", -1, 2));
		}
		if (nb_pro < nb_pipe)
		{
			if (dup2(pipe_fd[nb_pro * 2 + 1], 1) < 0)
				return(return_message("dup failed\n", -1, 2));
		}
		if (!nb_pro)
			close(pipe_fd[0]);
		else if (nb_pro == nb_pipe)
			close(pipe_fd[nb_pipe * 2 - 1]);
		else
		{
			close(pipe_fd[nb_pro * 2 - 1]);
			close(pipe_fd[nb_pro * 2]);
		}
	}
	return (all_case_redirection(list));
}
