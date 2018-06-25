#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

static t_word	*close_fd_mv_list(t_word *list, int i, int *pipe_fd, int nb_pipe)
{
	if (i > 0)
	{
		if (close(pipe_fd[i * 2 - 2]) < 0)
			ft_printf("close fd inside mv list failed\n");
	}
	if (i < nb_pipe)
	{
		if (close(pipe_fd[i * 2 + 1]) < 0)
			ft_printf("close fd inside mv list failed\n");
	}
	while (list && !is_logic(list->type) && list->type != SEMI_DOT && list->type != PIPE)
		list = list->next;
	if (list && list->type == PIPE)
		list = list->next;
	return (list);
}

static void	wait_all_pid(int *nb_pid, int i)
{
	int		j;
	int		status;

	j = -1;
	while (++j <= i)
		waitpid(nb_pid[j], &status, WUNTRACED);
}

static void	init_for_each_bloc(t_program *pro, int index,  int *nb_pid, int *pipe_fd)
{
	int		i;

	i = -1;
	while (++i < index)
		pro[i].pro_args = NULL;
	init_int_table(nb_pid, MAX_BUF);
	init_int_table(pipe_fd, MAX_BUF);
}

static void	init_for_each_bloc_2(t_word *list, int *nb_pipe, int *i)
{
	*nb_pipe = nb_pipe_eachbloc(list);
	*i = -1;
}

int		actions_each_bloc(t_word *list, char ***env, t_sh *table)
{
	int			pipe_fd[MAX_BUF];
	t_program	pro[MAX_BUF];
	int			nb_pid[MAX_BUF];
	int			i;
	int			nb_pipe;

	init_for_each_bloc_2(list, &nb_pipe, &i);
	if (!nb_pipe && list->type == BUIDIN)
		return (pro_is_buildin_no_pipe(list, env, table));
	init_for_each_bloc(pro, MAX_BUF,  nb_pid, pipe_fd);
	do_all_pipe(pipe_fd, nb_pipe);
	while (list && !is_logic(list->type) && list->type != SEMI_DOT)
	{
		my_here_doc_word(list);
		pro[++i].pro_args = args_each_exev(list, *env);
		nb_pid[i] = fork();
		if (nb_pid[i] < 0)
			ft_putendl_fd("fork failed", 2);
		else if (nb_pid[i] == 0)
			(do_all_redirection(list, pipe_fd, nb_pipe, i)) ? exit(0) :\
				do_child_pro(list, pro[i].pro_args, *env, table);
		list = close_fd_mv_list(list, i , pipe_fd, nb_pipe);
	}
	free_pro_args(pro, MAX_BUF);
	wait_all_pid(nb_pid, i);
	return (0);
}
