/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:26:55 by saxiao            #+#    #+#             */
/*   Updated: 2018/06/26 13:30:31 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <sys/types.h>
#include "libft/libft.h"

#ifndef MINISHELL_H
int		open_dquote;
int		open_squote;
int		open_backslash;
int		line_edition_ing;
int		end_line;
int		with_termcap;

#define MAX_BUF 4096
#define SETNEW 1
#define SETOLD 0

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

typedef enum s_type {
	PROGRAM = 10,
	ARG, //
	LESS,//< 
	LESSAND,// <&
	LESSANDMINUS,// <&-
	DLESS, //<<
	AND, //&&
	GREAT, //>
	GREATAND, // >&
	GREATANDMINUS, // >&-
	DGREAT, //>>
	OR,//||
	PIPE, //|
	SEMI_DOT, // ;
	FILES, //
	FD, //
	HERE_DOC_MARK,
	BUIDIN,
}			t_type;

typedef struct	s_word{
	char			word[MAX_BUF];
	t_type			type;
	struct s_word	*next;
	struct s_word	*pre;
}				t_word;

typedef struct s_save_fd{
	int		fd_2be_saved;
	int		fd_saved_in2;
	struct s_save_fd *next;
}				t_save_fd;

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define NB_KEY 20
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
#define CONTRL_S 19
#define MY_PAGE_UP 45067098907
#define MY_PAGE_DOWN 45067164443
#define OPTION_SHIFT_U 43202
#define OPTION_SHIFT_D 36547
#define CONTRL_N 14
#define SHIFT_UP 71683997260571
#define SHIFT_DOWN 71683997260571
#define CONTRL_F 6
#define CONTRL_D 4
#define DELETE_AT_POSITION 2117294875

char	temp_file[MAX_BUF];

typedef struct s_history
{
	char his[2048];
	struct s_history *next;
	struct s_history *pre;;
}				t_history;

t_history	*history;

typedef struct s_line
{
	int			pos;
	unsigned char	buf[MAX_BUF];
	unsigned char	cp[MAX_BUF];
	unsigned char	here_mark[MAX_BUF];
	unsigned char	here[MAX_BUF];
	unsigned char	ici_doc[MAX_BUF];
	int			buf_len;
	int			line_max;
	int			start_po;
	int			his_mostdown;
	int			his_mostup;
	int			up_indown;
	int			one_his;
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
	int			(*ctrl_d)(struct s_line *line);
	int			(*delete_at_position)(struct s_line *line);
	int			(*engine)(struct s_line *line, unsigned long a_key);
}				t_line;

typedef struct s_key
{
	unsigned long	a_key;
	int			(*func)(t_line *);
}				t_key;

char		new_line[MAX_BUF];
t_line		a_line;

char		*get_autoline(t_sh *table);
void		shell(int ac, char **av, char **env, t_sh *table);
void		each_cmdline(char *cmdline, char **env, t_sh *table);
void		pipes(char *cmdline, int nb_pipe, char ***env, t_sh *table);
int			no_pipe(char *cmdline);
void		signal_quith(int sign);

//termcap_setting.c
int		init_attr(int mod);
int			my_putc(int c);

//line_engine.c
int			engine(t_line *line, unsigned long key);
//void		ft_freestrstr(char **cp_env);

//line_mv_left_right.c
int			move_left(t_line *line);
int			move_nleft(t_line *line);
int			mv_left_word(t_line *line);
int			mv_right_word(t_line *line);
int			move_right(t_line *line);

//line_delete.c
int			move_nright(t_line *line);
int			delete_key(t_line *line);
int			delete_all(t_line *line);

//line_ctrl_d.c
int			delete_at_position(t_line *line);
int			ctrl_d(t_line *line);

//line_printable.c
int			printable(t_line *line, unsigned long key);
void		put_a_key(t_line *line, unsigned long key);

//line_his_up_down.c
int			history_up(t_line *line);
int			history_down(t_line *line);

//line_cp_cut.c
int			cp_all(t_line *line);
int			cp_begin(t_line *line);
int			cp_end(t_line *line);
int			cut_all(t_line *line);
int			cut_begin(t_line *line);

//line_paste_go_updown.c
int			cut_end(t_line *line);
int			paste(t_line *line);
int			go_up(t_line *line);
int			go_down(t_line *line);

//line_get_line.c
int			get_line(char *prompt, char *new_line, t_line *line);
void		init_line(char	*prompt, t_line *line);

//line_prompt_open_quote.c
void		prompt_open_quote(char *line);


//prompt.c
int			prompt(char **env, t_sh *table);

//sh_table.c
char		*ft_getenv(char **env, char *name);
char		**path(char **env);
int			calcu_index(char *name);
void		init_shtable(t_sh *table, char **path);

//update_env.c
void		update_shlvl(char ***env);
void		update_lastapp(char *lastcmd, char ***env);

//set_unset_env
int			nb_str(char **str);
char		**set_env(char **paras, char ***env);
char		**unset_env(char **paras, char **env);

//do_buildin.c
int			is_buildin(char *app);
void		do_build(char **paras, char ***env, t_sh *table);
void		replace_home(char *cp, char *home);
void		ft_exit(char ***env, t_sh *table);

//build_in_cd.c
int			cd(char **paras, char ***env);

//build_in_env.c
int			put_env(char **env, char **paras, t_sh *table);
void		put_strstr(char **str);
void		put2_str_fd(char *str1, char *str2, int fd);


//below is what i need with parsing
/*
ls -la /bin > file1 2>&- && cat -e file1 | less

WORD  >>>> ls   >    file1  2>&-    cat -e  file1  |    less
TOKEN >>>> BIN DLESS FILE  GREATAND BIN OPT FILE  PIPE  BIN

~~ exemple fait a l'arrache ~~
*/

typedef enum s_token {
	//BIN = 0,
	//BUILTIN,
//	OPT,
//	ARG,
	FILEREDI,
	OPERAND,
	//FILES,
}			t_token;

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

typedef struct		s_helper{
		int		i;
		int		j;
		int		k;
		int		index;
}					t_helper;
//ls | less

typedef struct s_program {
		char	**pro_args;
}				t_program;


//execve(ls) out > execve(less) > open(file)

// sh_table.c
//char			*ft_getenv(char **env,char *nm);

// rm_quoting_in_word.c
int				remove_quoting_word(char *word,char **env);

// remove_quoting_list.c
void		change_part_str(char *ori, int start, int end, char *change);
void		dollor_sign(t_helper *help, char *cp, char *vari);
void		remove_quoting_list(t_word *list, char **env);
int			remove_quoting_bloc(t_word *list, char **env);

// print.c
void			print_words_type(t_word *list);

// err_in_words.c
int				err_in_words(t_word *list);
int				program_exit_before(t_word *li);

// is_lexing_type.c
int				is_seprator_w(char *line, int index);
int				is_redirector(t_type type);
int				is_logic(t_type type);

// command_to_words.c
t_word			*command_to_words(char *line);

// init_add_word.c
t_word			*init_add_word(char *line, int *i, int *j);
t_word			*malloc_add(void);

//init_seprator.c
t_word			*init_seprator(char *line,int *index);

// for_init_seprator.c
t_word			*pipe_or_type(char *line, int *index);
t_word			*and_type(char *line, int *index);
t_word			*semidot_type(char *line, int *index);
int				return_message(char *message, int re_value, int fd);

//my_here_doc.c
void			my_here_doc(char *line);
int				inclu_heredoc(char *new_line);

// here_doc_bse_word.c
void			my_here_doc_word(t_word *list);

//all_case_redirection.c
int				all_case_redirection(t_word *list);

//less_case_redirection.c
int				redi_less(t_word *list);
int				redi_lessand(t_word *list);
int			redi_lessandminus(t_word *list);
int				err_open_file(t_word *list);

//child_program.c
void		child_pro_bin(char **paras, char **env, t_sh *table);
void		child_pro_buildin(t_word *list, char **paras, char **env, t_sh *table);
void		do_child_pro(t_word *list, char **paras, char **env, t_sh *table);

//actions_each_line.c
int			dslash_before(char *line, int index);
void		print_list_word(t_word *list);
void		actions_each_line(char ***env, t_word *list, t_sh *table);

//actions_each_bloc.c
int			actions_each_bloc(t_word *list, char ***env, t_sh *table);

//helper_actiond_each_bloc.c
int			nb_pipe_eachbloc(t_word *list);
char		**args_each_exev(t_word *list, char **env);
int			close_all_pipe(int *pipe_fd, int nb_pipe, int nb_pro); // didnt really used this func.
int			do_all_redirection(t_word *list, int *pipe_fd, int nb_pipe, int nb_pro);

//helper_actiond_each_bloc_2.c
void		init_int_table(int *table, int len);
int			do_all_pipe(int *pipe_fd, int nb_pipe);
int			pro_is_buildin_no_pipe(t_word *list, char ***env, t_sh *table);

//recover_fd__buildin.c
t_save_fd	*fd_restorage(t_word *list, t_save_fd *recover);
void		recover_fd(t_save_fd *recover);
void		free_saver_fd(t_save_fd *recover);

//signal.c
void		signal_inh(int sign);
void		signal_quith(int sign);

//my_free.c
void		ft_freestrstr(char **cp_env);
void		free_sh_table(t_sh *table, int index);
void		free_pro_args(t_program *pro, int index);
void		free_word_list(t_word *list);

//helper.c
t_table		*malloc_add_sh(void);
#endif
