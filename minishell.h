/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:26:55 by saxiao            #+#    #+#             */
/*   Updated: 2018/05/09 17:10:17 by saxiao           ###   ########.fr       */
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
#define NB_KEY 9
#define	ARROW_LEFT 4479771
#define ARROW_RIGHT 4414235
#define	ARROW_UP 4283163
#define ARROW_DOWN 4348699
#define MY_DELECT 127
#define MY_HOME 4741915
#define MY_END 4610843
#define CT_SHIFT_LEFT 74999712013083
#define CONTRL_L 12
#define CONTRL_H 8
#define CONTRL_A 1
#define CONTRL_B 2
#define CONTRL_E 5
#define CONTRL_P 16
#define CONTRL_HOME 79393463556891
#define CONTRL_END 77194440301339


typedef struct s_history
{
	char his[2048];
	struct s_history *next;
	struct s_history *pre;;
}				t_history;

typedef struct s_line
{
	size_t		key;
	int			pos;
	unsigned char	buf[MAX_BUF];
	unsigned char	cp[MAX_BUF];
	int			buf_len;
	int			line_max;
	int			start_po;
	int			ligne;
	int			col;
	int			his_mostdown;
	int			his_mostup;
	int			up_indown;
	int			one_his;
	t_history	*last_his;

	int			(*printable)(struct s_line *line, unsigned long  a_key);
	int			(*move_left)(struct s_line *line);
	int			(*move_right)(struct s_line *line);
	int			(*delete_key)(struct s_line *line);
	int			(*move_nleft)(struct s_line *line);
	int			(*move_nright)(struct s_line *line);
	int			(*mv_left_word)(struct s_line *line);
	int			(*mv_right_word)(struct s_line *line);
	int			(*history_up)(struct s_line *line);
	int			(*history_down)(struct s_line *line);
	int			(*engine)(struct s_line *line, unsigned long a_key);
}				t_line;

typedef struct s_key
{
	unsigned long	a_key;
	int			(*func)(t_line *);
}				t_key;


unsigned long	get_key();
int			printable(t_line *line, size_t key);
void			put_a_key(t_line *line, unsigned long key);
#endif
