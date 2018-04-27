#include <unistd.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "minishell.h"

int		no_pipe(char *cmdline)
{
	int		i;

	i = 0;
	while(*cmdline)
	{
		if (*cmdline++ == '|')
			i++;
	}
	return (i);
}

void	close_pipe(int *pipes, int index)
{
	int		ct;

	ct = 0;
	while (ct < index)
		close(pipes[ct++]);
}

/*
   void	pipes(char	*cmdline, int nb_pipe, char **env, t_sh *table)
   {
   char	**cmds;
   int		pipe_fd[nb_pipe * 2];
   int		ct;
   pid_t	pid;

   cmds = ft_strsplit(cmdline, '|');
   ct = 0;
   if (nb_pipe > 0)
   {
   while (ct < nb_pipe)
   pipe(pipe_fd + (ct++ *2));
   }
   ct = 0;
   while (ct <= nb_pipe)
   {
   pid = fork();
   if (pid < 0)
   exit(1);
   else if(pid == 0)
   {
   if (ct)
   dup2(pipe_fd[(ct - 1) * 2], 0);
   if (ct != nb_pipe)
   dup2(pipe_fd[ct  * 2 + 1], 1);
   close_pipe(pipe_fd, nb_pipe * 2);
   child_pro(ft_strsplit(cmds[ct],' '), env, table);
   }
   else
   {
   wait(0);
   if (ct != nb_pipe)
   close(pipe_fd[ct*2 + 1]);
   ct++;
   }
   }
   close_pipe(pipe_fd, nb_pipe * 2);
   }
   */
/*
   void	for_pipe()
   {
   int		pipe_fd[2];
   pid_t	pid;

   if (nb_pipe)
   pipe(pipe_fd);
   pid = fork();
   if (pid < 0)
   exit(1);
   else if(pid == 0)
   {
   if (in)
   {
   if (dup2(in, 0) < 0)
   ft_printf("dup2 failed \n");
   close(in);
   }
   if (ct != nb_pipe)
   dup2(pipe_fd[1], 1);
   if (is_buildin(*papra))
   do_build(papra, env, table);
   else
   child_pro(papra, *env, table);
   }
   else
   {
   wait(0);
   in = pipe_fd[0];
   close(pipe_fd[1]);
   ct++;
   }
   }
   }
   }
   }
   */

void		inside_child(int in, int nb_pipe, int *pipe_fd, int ct)
{
	if (in)
	{
		if (dup2(in, 0) < 0)
			ft_printf("dup2 failed \n");
		close(in);
	}
	if (ct != nb_pipe)
		dup2(pipe_fd[1], 1);
}

void	first_is_buildin(int in, char **papra, char ***env, t_sh *table)
{
	if (in)
	{
		if (dup2(in, 0) < 0)
			ft_printf("dup2 failed \n");
		close(in);
	}
	do_build(papra, env, table);
}

void	init_saver(int nb_pipe, t_vari *saver)
{
	saver->in = 0;
	saver->ct = -1;
	saver->num_pipe = nb_pipe;
}

void	parent_child(t_vari *saver, char **papra, char ***env, t_sh *table)
{
	if (saver->num_pipe)
		pipe(saver->pipe_fd);
	saver->pid = fork();
	if (saver->pid < 0)
		exit(1);
	else if(saver->pid == 0)
	{
		inside_child(saver->in, saver->num_pipe, saver->pipe_fd, saver->ct);
		if (is_buildin(*papra))
			do_build(papra, env, table);
		else
			child_pro(papra, *env, table);
	}
	else
	{
		waitpid(saver->pid, NULL, 0);
		saver->in = saver->pipe_fd[0];
		//close(saver->pipe_fd[1]);
	}
}

void	pipes(char	*cmdline, int nb_pipe, char ***env, t_sh *table)
{
	char	**cmds;
	char	**papra;
	t_vari	saver;

	cmds = ft_strsplit(cmdline, '|');
	init_saver(nb_pipe, &saver);
	while (++saver.ct <= nb_pipe)
	{
		papra = ft_split(cmds[saver.ct], " \t");
		if (saver.ct == nb_pipe && *papra && is_buildin(*papra))
			first_is_buildin(saver.in, papra, env, table);
		else
			parent_child(&saver, papra, env, table);
	}
}
