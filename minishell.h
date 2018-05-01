/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:26:55 by saxiao            #+#    #+#             */
/*   Updated: 2018/04/27 16:51:55 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <sys/types.h>
#include "libft/libft.h"

#ifndef MINISHELL_H
#define MINISHELL_H

typedef struct s_table
{
	char			name[NAME_MAX + 1];
	char			path[PATH_MAX + 1];
	struct s_table	*next;
}					t_table;

typedef struct	s_shtable
{
	t_table		*sh_ta;
}				t_sh;

typedef struct s_vari
{
	int		in;
	int		num_pipe;
	int		pipe_fd[2];
	int		ct;
	pid_t	pid;
}			t_vari;

char		*get_autoline(t_sh *table);
char		**path(char **env);
int			calcu_index(char *name);
int			is_buildin(char *app);
char		**unset_env(char **paras, char **env);
void		do_build(char **paras, char ***env, t_sh *table);
void		put_env(char **env, char **paras, t_sh *table);
char		*ft_getenv(char **env, char *name);
void		init_shtable(t_sh *table, char **path);
void		shell(int ac, char **av, char **env, t_sh *table);
void		child_pro(char **paras, char **env, t_sh *table);
void		each_cmdline(char *cmdline, char **env, t_sh *table);
void		pipes(char *cmdline, int nb_pipe, char ***env, t_sh *table);
int			no_pipe(char *cmdline);
void		signal_quith(int sign);
void		put_strstr(char **str);
void		set_env(char **paras, char ***env);
void		update_shlvl(char ***env);
void		update_lastapp(char *lastcmd, char ***env);
#include <stdio.h>
//#ifndef SHELL_SH
//#define SHELL_SH

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define MAX_BUF 2048
#define NB_KEY 3
#define	ARROW_LEFT 4479771
#define ARROW_RIGHT 4414235
#define	ARROW__UP 4283163
#define ARROW_DOWN 4348699
#define MY_DELECT 127


typedef struct s_line
{
	size_t		key;
	int			pos;
	unsigned char	buf[MAX_BUF];
	int			buf_len;
	int			line_max;
	int			start_po;

	int			(*printable)(struct s_line *line, size_t a_key);
	int			(*move_left)(struct s_line *line);
	int			(*move_right)(struct s_line *line);
	int			(*delete_key)(struct s_line *line);
//	int			(*move_nleft)(struct s_line *line);
	int			(*engine)(struct s_line *line, size_t a_key);
}				t_line;

typedef struct s_key
{
	size_t		a_key;
	int			(*func)(t_line *);
}				t_key;

size_t		get_key();
int			printable(t_line *line, size_t key);
#endif
