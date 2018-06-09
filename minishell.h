/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:26:55 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/09 18:04:43 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <sys/types.h>
#include "libft/libft.h"

#ifndef MINISHELL_H

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
#define NB_KEY 18
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
#define CONTRL_HASH 27
#define CONTRL_PERCENT 29
#define CONTRL_AT 0
#define MY_PAGE_UP 45067098907
#define MY_PAGE_DOWN 45067164443
#define OPTION_SHIFT_U 43202
#define OPTION_SHIFT_D 36547
#define CONTRL_N 14
#define CONTRL_F 6


typedef struct s_history
{
	char his[2048];
	struct s_history *next;
	struct s_history *pre;;
}				t_history;

typedef struct s_line
{
	int			pos;
	unsigned char	buf[MAX_BUF];
	unsigned char	cp[MAX_BUF];
	unsigned char	here_mark[MAX_BUF];
	unsigned char	here_doc_buf[MAX_BUF];
	unsigned char	ici_doc[MAX_BUF];
	int			buf_len;
	int			line_max;
	int			start_po;
	int			his_mostdown;
	int			his_mostup;
	int			up_indown;
	int			one_his;
	int			open_dquote;
	int			open_squote;
	int			here_end;
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
	int			(*cp_all)(struct s_line *line);
	int			(*cp_begin)(struct s_line *line);
	int			(*cp_end)(struct s_line *line);
	int			(*cut_all)(struct s_line *line);
	int			(*cut_begin)(struct s_line *line);
	int			(*cut_end)(struct s_line *line);
	int			(*paste)(struct s_line *line);
	int			(*go_up)(struct s_line *line);
	int			(*go_down)(struct s_line *line);
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

//below is what i need with parsing
/*
ls -la /bin > file1 2>&- && cat -e file1 | less

WORD  >>>> ls   >    file1  2>&-    cat -e  file1  |    less
TOKEN >>>> BIN DLESS FILE  GREATAND BIN OPT FILE  PIPE  BIN

~~ exemple fait a l'arrache ~~
*/

typedef enum s_token {
	BIN = 0,
	BUILTIN,
//	OPT,
//	ARG,
	FILEREDI,
	OPERAND,
	//FILES,
}			t_token;

typedef enum s_type {
	PROGRAM = 10,
	ARG, //11
	LESS,//< 12
	LESSAND,// <&
	LESSANDMINUS,// <&-
	DLESS, //<< 13
	AND, //&& 14
	GREAT, //> 15
	GREATAND, // >& 15
	GREATANDMINUS, // >&- 15
	DGREAT, //>> 16
	OR,//|| 17
	PIPE, //| 18
	SEMI_DOT, // 19;
	FILES, //20
	FD, //21
	HERE_DOC_MARK,
}			t_type;

typedef struct	s_word{
	char			word[MAX_BUF];
	t_type			type;
	struct s_word	*next;
	struct s_word	*pre;
}				t_word;
/*
t_list *l;


if (l->next->tok == SUBTOKEN)
{
	if (l->next->tok == PIPE)
		dup2(l->out.fd, STDOUT_FILENO);
}

if (l->prev->tok == SUBTOKEN && l->prev->sub == PIPE)
*/


typedef struct	s_file{
	char 	*name;
	int		fd;
}		t_file;

typedef struct		s_list_token{
	t_token			*tok; 
//	t_operand		*next; //(default null)
//	t_operand		*prev; //(default null)
	char			*name;
	t_file			out;
	t_file			in;
	char			**args;
//	char			*opt;
	char			**env;
	struct s_list_token	*after;
	struct s_list_token	*before;
}					t_list_token;


//ls | less



//execve(ls) out > execve(less) > open(file)

t_word			*command_to_words(char *line);
void			print_words(t_word *list);
int				err_in_words(t_word *list);
#endif
