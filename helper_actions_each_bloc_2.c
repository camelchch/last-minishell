#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

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
			ft_printf("pipe failed in  do all pipe pipe()\n");
			i = -1;
		}
		pipe_fd = pipe_fd + 2;
	}
	return (i);
}

int		pro_is_buildin_no_pipe(t_word *list, char ***env, t_sh *table)
{
	char		**pro_args;
	t_save_fd	*recover;

	recover = NULL;
	pro_args = NULL;
	recover = fd_restorage(list, recover);
	pro_args = args_each_exev(list, *env);
	all_case_redirection(list);
	do_build(pro_args, env, table);
	recover_fd(recover);
	free_saver_fd(recover);
	if (pro_args)
		free(pro_args);
	return (0);
}
