#include <termios.h>
#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "minishell.h"

int		dslash_before(char *line, int index)
{
	int		i;
	int		j;

	i = 0;
	j = index - 1;
	while (j >= 0 && line[j] == '\\')
	{
		i++;
		j--;
	}
	if (!(i % 2))
		return(1);
	return (0);
}


void	print_ww(t_word *list)
{
	while(list)
	{
		ft_printf("%s ", list->word);
		list = list->next;
	}
}

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

int		nb_args_each_exev(t_word *list)
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

int		close_all_pipe(int *pipe_fd, int nb_pipe)
{
	int		i;

	i = 0;
	while (i < nb_pipe * 2)
	{
		if (close(pipe_fd[i++] < 0))
			i = -1;
	}
	return (i);
}

int		do_all_redirection(t_word *list, int *pipe_fd, int nb_pipe, int nb_pro)
{
	if (nb_pipe)
	{
		//	if (nb_pro > 0)
		//		close(pipe_fd[nb_pro * 2 - 1]);
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
	}
	return (all_case_redirection(list));
}

void	init_int_table(int *table, int len)
{
	int		i;

	i = -1;
	while (++i < len)
		table[i] = -1;
}

int		do_all_pipe(int *pipe_fd, int nb_pipe)
{
	int		i;

	i = 0;
	while (++i <= nb_pipe)
	{
		if (pipe(pipe_fd) < 0)
		{
			perror(" do all pipe pipe()");
			i = -1;
		}
		pipe_fd = pipe_fd + 2;
	}
	return (i);
}

void	pro_is_buildin_no_pipe(t_word *list, char **env, t_sh *table)
{
	char	**pro_args;

	pro_args = args_each_exev(list, env);
	all_case_redirection(list);
	do_build(pro_args, &env, table);
}

void	actions_each_bloc(t_word *list, char **env, t_sh *table)
{
	int			pipe_fd[MAX_BUF];
	t_program	pro[MAX_BUF];
	int			nb_pid[MAX_BUF];
	int			i;
	int			j;
	int			nb_pipe;
	int			status;

	nb_pipe = nb_pipe_eachbloc(list);
	ft_printf("nb of pipe %d\n", nb_pipe);
	i = -1;
	j = 0;
	ft_bzero(pro, sizeof(pro));
	init_int_table(nb_pid, MAX_BUF);
	init_int_table(pipe_fd, MAX_BUF);
	do_all_pipe(pipe_fd, nb_pipe);
	while (list && !is_logic(list->type) && list->type != SEMI_DOT)
	{
		pro[++i].pro_args = args_each_exev(list, env);
		if (i > 0)
			close(pipe_fd[i * 2 - 1]);
		nb_pid[i] = fork();
		if (nb_pid[i] < 0)
			perror("fork()");
		else if (nb_pid[i] == 0)
		{
			if (do_all_redirection(list, pipe_fd, nb_pipe, i) == 0)
				child_pro_bin(pro[i].pro_args, env, table);
			else
				exit(0);
		}
		if (i > 0)
			close(pipe_fd[i * 2 - 2]);
		if (i < nb_pipe)
			close(pipe_fd[i * 2 + 1]);
		ft_printf("inside actions_each_bloc  00000\n");
		ft_printf(" nb_pid=%d\n", nb_pid[i]);
		while (list && !is_logic(list->type) && list->type != SEMI_DOT && list->type != PIPE)
			list = list->next;
		if (list && list->type == PIPE)
			list = list->next;
		ft_printf("list now =%s\n", list->word);
	}
	int d;
	while (j <= i)
	{
		//	close_all_pipe(pipe_fd, nb_pipe);
		ft_printf(" start wait after close_all_pipe\n");
		ft_printf(" nb_pid=%d\n", nb_pid[j]);
		ft_printf("d =%d, j =%d\n", d, j);
		if (waitpid(nb_pid[j], &status, WUNTRACED) == 1)
		{
			ft_printf(" nb_pid=%d is not waited\n", nb_pid[j]);
			kill(nb_pid[j], SIGQUIT);
		}
		else
		ft_printf("here or not 8888888\n");
		if (WIFSTOPPED(status) | WIFSIGNALED(status))
		{
			ft_printf("inside kill\n");
			kill(nb_pid[j], SIGQUIT);
			//	ft_printf("inside kill\n");
		}
		j++;
	}
}

void	actions_blocs(t_word *list, char **env, t_sh *table)
{
	t_word	*cp;
	int		find_bloc;
	int		find_err;

	find_bloc = 0;
	find_err = 0;
	cp = list;
	if (cp)
	{
		if (!remove_quoting_bloc(cp, env))
		{
			my_here_doc_word(list);
			print_words_type(list);
			actions_each_bloc(list, env, table);
		}
	}
}

void	actions_each_line(char **env, t_word *list, t_sh *table)
{
	ft_printf("\n");
	print_words_type(list);
	print_ww(list);
	if (!err_in_words(list))
	{
		actions_blocs(list, env, table);
	}
}

