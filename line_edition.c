#include <termios.h>
#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
//#include "shell.h"
#include "minishell.h"

#define SETNEW 1
#define SETOLD 0
t_history	*history;


void	raw_termi_mode()
{
	struct	termios	tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ECHO | ICANON);
	tattr.c_oflag &= ~(OPOST);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN,&tattr);
	tgetent(NULL, getenv("TERM"));
}

void	default_termi_mode()
{
	struct	termios	tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag |= (ECHO | ICANON);
	tattr.c_oflag |= (OPOST);
	tcsetattr(STDIN_FILENO, TCSADRAIN,&tattr);
}

void	init_attr(int mod)
{
	static struct	termios old;
	static int				oldatt = 0;
	struct	termios			new;

	if (!oldatt)
	{
		oldatt = 1;
		if (tcgetattr(0, &old) == -1)
			ft_printf("can't get att\n");
	}
	if (mod == SETNEW)
	{
		new = old;
		new.c_lflag &= ~(ECHO | ICANON);
		new.c_lflag |= ISIG;
		new.c_oflag &= ~(OPOST);
		new.c_cc[VMIN] = 1;
		new.c_cc[VTIME] = 0;
		//		new.c_cc[VTNTR] = 1;
		tcsetattr(STDIN_FILENO, TCSADRAIN, &new);
		tgetent(NULL, getenv("TERM"));
	}
	else
		//tcsetattr(STDIN_FILENO, TCSADRAIN, &old);
		default_termi_mode();
}


int		my_putc(int c)
{
	write(1, &c, 1);
	return (0);
}

int		engine(t_line *line, unsigned long  key)
{
	int		i;

	i = 0;
	if ((32 <= key && key <= 126))
		line->printable(line, key);
	else
	{
		t_key	t[NB_KEY] = {
			{ARROW_LEFT, line->move_left},
			{ARROW_RIGHT, line->move_right},
			{ARROW_UP, line->history_up},
			{ARROW_DOWN, line->history_down},
			{MY_DELECT, line->delete_key},
			{MY_END, line->move_nright},
			{MY_HOME, line->move_nleft},
			{CONTRL_L, line->mv_left_word},
			{CONTRL_H, line->mv_right_word},
			{CONTRL_A, line->cp_all},
			{CONTRL_B, line->cp_begin},
			{CONTRL_E, line->cp_end},
			{CONTRL_AT, line->cut_all},
			{CONTRL_HASH, line->cut_begin},
			{CONTRL_PERCENT, line->cut_end},
			{CONTRL_P, line->paste},
			{CONTRL_F, line->go_up},
			{CONTRL_N, line->go_down},
			//{KEY_DELECT, line->delete}
		};

		while (i < NB_KEY)
		{
			if (key == (t[i].a_key))
				t[i].func(line);
			i++;
		}
	}
	return (0);
}


int		move_left(t_line *line)
{
	int i;

	i = 0;
	if (line->pos)
	{
		if ((line->pos + line->start_po) % line->line_max == 0)
		{
			tputs(tgetstr("up", 0), 1, my_putc);
			sleep(1);
			while (i++ < line->line_max)
			{
				tputs(tgetstr("nd", 0), 1, my_putc);
				sleep(1);
			}
		}
		else
			tputs(tgetstr("le", 0), 1, my_putc);
		line->pos -= 1;
	}
	return (0);
}

int		move_nleft(t_line *line)
{
	while (line->pos > 0)
		line->move_left(line);

	return (0);
}

int		mv_left_word(t_line *line)
{
	int		left;

	left = line->pos;
	if(line->pos == line->buf_len)
		left = line->buf_len - 1;
	if (line->pos != line->buf_len &&left && line->buf[left] != ' ' && \
			line->buf[left] != '\t' && (line->buf[left - 1] == ' ' || line->buf[left - 1] == '\t'))
		left--;
	while (left > 0 && (line->buf[left] == ' ' || line->buf[left] == '\t'))
		left--;
	if (line->buf[left] != ' ' && line->buf[left] != '\t')
	{
		while (left > 0 && line->buf[left] != ' ' && line->buf[left] != '\t')
			left--;
		if (left)
			left++;
		while (line->pos > left)
			line->move_left(line);
	}
	return (0);
}

int		mv_right_word(t_line *line)
{
	int		rt;

	rt = line->pos;
	if (rt != line->buf_len)
	{
		while (rt < line->buf_len && line->buf[rt] != ' ' && line->buf[rt] != '\t')
			rt++;
		while (rt < line->buf_len && (line->buf[rt] == ' ' || line->buf[rt] == '\t'))
			rt++;
		if (rt < line->buf_len && rt - 1 >= 0 && (line->buf[rt - 1] == ' ' || line->buf[rt - 1] == '\t') && line->buf[rt] != ' ' && line->buf[rt] != '\t')
		{
			while (line->pos < rt)
				line->move_right(line);
		}
	}
	return (0);
}

int		move_right(t_line *line)
{
	int		i;

	i = line->line_max;
	if (line->pos < line->buf_len)
	{
		if ((line->pos + line->start_po) % line->line_max == line->line_max - 1)
		{
			tputs(tgetstr("do", 0), 1, my_putc);
			while (i-- > 0)
				tputs(tgetstr("le", 0), 1, my_putc);
		}
		else
			tputs(tgetstr("nd", 0), 1, my_putc);
		line->pos += 1;
	}

	return (0);
}

int		move_nright(t_line *line)
{
	while  (line->pos < line->buf_len)
		move_right(line);
	return (0);
}

int		delete_key(t_line *line)
{
	int		i;
	int		new_pos;

	if (line->pos > 0)
	{
		i = line->pos - 2;
		while (++i < line->buf_len)
			line->buf[i] = line->buf[i + 1];
		new_pos = line->pos - 1;
		move_nleft(line);
		i = 0;
		line->buf_len = 0;
		line->pos = 0;
		while (line->buf[i])
			put_a_key(line, line->buf[i++]);
		if ((line->buf_len + line->start_po) % line->line_max == (line->line_max - 1))
		{
			write(1, " ", 1);
			tputs(tgetstr("le", 0), 1, my_putc);
			tputs(tgetstr("nd", 0), 1, my_putc);
		}
		else
			tputs(tgetstr("dc", 0), 1, my_putc);
		i = line->buf_len - new_pos;
		while (i-- > 0)
			move_left(line);
	}
	return (0);
}

void	delete_all(t_line *line)
{
	move_nright(line);
	while (line->buf_len)
	{
		delete_key(line);
		//sleep(1);
	}
}


void	put_a_key(t_line *line, unsigned long key)
{
	if ((line->pos  +  1 + line->start_po) % line->line_max == 0)
	{
		tputs(tgetstr("ic", 0), 1, my_putc);
		write(STDOUT_FILENO, &key, 1);
		tputs(tgetstr("do", 0), 1, my_putc);
		tputs(tgetstr("cr", 0), 1, my_putc);
	}
	else
		write(STDOUT_FILENO, &key, 1);
	line->pos++;
	line->buf_len++;
}

int		printable(t_line *line, unsigned long key)
{
	int		index;
	int		positive;
	int		new_pos;
	int		new_len;

	if (line->pos == line->buf_len)
	{
		line->buf[line->pos] = key;
		put_a_key(line, key);
	}
	else
	{
		new_pos = line->pos + 1;
		new_len = line->buf_len + 1;
		index = line->buf_len + 1;
		while (--index > line->pos)
			line->buf[index] = line->buf[index -1];
		line->buf[line->pos] = key;
		index = line->pos;
		line->buf_len = line->pos;
		while (index < new_len)
		{
			put_a_key(line, line->buf[index++]);
			//sleep(1);
		}
		index = (line->buf_len + line->start_po) / line->line_max - (new_pos +line->start_po) / line->line_max;
		while ( index-- > 0)
			tputs(tgetstr("up", 0), 1, my_putc);
		//	sleep(1);
		index = (line->buf_len + line->start_po) % line->line_max - (new_pos + line->start_po) % line->line_max;
		positive = index >= 0 ? index : -index;
		while (positive-- > 0)
		{
			tputs(tgetstr(index > 0 ? "le" : "nd" , 0), 1, my_putc);
			//		sleep(1);
		}
		line->pos = new_pos;
	}
	return (0);
}

void	init_add(t_history *add, char *new_line)
{
	ft_bzero(add->his, 0);
	ft_strcpy(add->his, new_line);
	add->next = NULL;
	add->pre = NULL;
}

int				history_up(t_line *line)
{
	int		i;

	i = -1;

	if (line->buf_len)
		delete_all(line);
	if (line->last_his)
	{
		if (!line->his_mostdown && line->last_his->pre)
			line->last_his = (line->last_his)->pre;
		//if (!line->his_mostup)
		if (!line->his_mostup)
		{
			while (line->last_his->his[++i])
			{
				put_a_key(line, line->last_his->his[i]);
				line->buf[i] = line->last_his->his[i];
			}
		}
		if (line->his_mostup == 1)
			line->up_indown = 1;
		if (!line->last_his->next)
			line->his_mostdown = 0;
		if (!line->last_his->pre)
			line->his_mostup = 1;
		if (line->up_indown  && !line->last_his->next)
			line->one_his = 1;
	}
	return (0);
}


int				history_down(t_line *line)
{
	int		i;

	i = -1;

	if (line->buf_len)
		delete_all(line);
	if (line->last_his && !line->last_his->next && !line->one_his)
		line->his_mostup = 0;
	if (line->last_his && (line->last_his->next || line->one_his))
	{
		if (!line->up_indown && (line->last_his)->next)
			line->last_his = (line->last_his)->next;
		while (line->last_his->his[++i])
		{
			put_a_key(line, line->last_his->his[i]);
			line->buf[i] = line->last_his->his[i];
		}
		line->his_mostup = 0;
		line->up_indown = 0;
		if (!line->last_his->next)
			line->his_mostdown = 0;
		if (!line->last_his->pre)
			line->his_mostup = 1;
		line->one_his = 0;
	}
	else if (line->last_his && !line->last_his->next)
		line->his_mostdown = 1;
	return (0);
}

unsigned long	get_key()
{
	unsigned char	buff[6];

	ft_bzero(buff, 6);
	read(0, buff, 6);
	return (buff[0] +( buff[1] << 8) + (buff[2] << 16) + (buff[3] << 24) +\
			((unsigned long)buff[4] << 32) + ((unsigned long)buff[5] << 40));
}

int		cp_all(t_line *line)
{
	ft_bzero(line->cp, MAX_BUF);
	ft_strcpy((char *)line->cp, (char *)line->buf);
	return (0);
}

int		cp_begin(t_line *line)
{
	int		i;

	i = line->pos;
	ft_bzero(line->cp, MAX_BUF);
	ft_strncpy((char *)line->cp, (char *)line->buf, i);
	return (0);
}

int		cp_end(t_line *line)
{
	int		i;

	i = line->buf_len - line->pos;
	ft_bzero(line->cp, MAX_BUF);
	ft_strncpy((char *)line->cp, (char *)line->buf + line->pos, i);
	return (0);
}

int		cut_all(t_line *line)
{
	cp_all(line);
	delete_all(line);
	return (0);
}

int		cut_begin(t_line *line)
{
	cp_begin(line);
	while (line->pos)
		delete_key(line);
	return (0);
}

int		cut_end(t_line *line)
{
	int		i;

	i = line->buf_len - line->pos;
	cp_end(line);
	move_nright(line);
	while (i--)
		delete_key(line);
	return (0);
}

int		paste(t_line *line)
{
	int		index;
	int		i;
	char	rest[MAX_BUF];

	index = line->pos;
	ft_bzero(rest, MAX_BUF);
	ft_strcpy(rest, (char *)line->buf + index);
	i = 0;
	while ( line->cp[i])
		line->buf[index++] = line->cp[i++];
	i = 0;
	while ( rest[i])
		line->buf[index++] = rest[i++];
	i = line->buf_len - line->pos;
	line->buf_len = line->pos;
	index = line->pos;
	while (line->buf[index])
		put_a_key(line, line->buf[index++]);
	while (i--)
		move_left(line);
	return (0);
}

int		go_up(t_line *line)
{
	int		i;

	if (line->pos > line->line_max - line->start_po - 1)
	{
		tputs(tgetstr("up", 0), 1, my_putc);
		line->pos = line->pos - line->line_max;
		sleep(1);
		if ((line->pos + line->start_po) / line->line_max == 0 && \
				(line->pos + line->start_po) % line->line_max < line->start_po)
		{
			i = line->start_po - (line->pos + line->start_po) % line->line_max;
			while (i--)
			{
				move_right(line);
				sleep (1);
			}
		}
	}
	return (0);

}

int		go_down(t_line *line)
{
	int		i;

	if ((line->buf_len - 1 + line->start_po) / line->line_max >
			(line->pos + line->start_po) / line->line_max)
	{
		tputs(tgetstr("do", 0), 1, my_putc);
		line->pos = line->pos + line->line_max;
		if (line->pos > line->buf_len - 1)
		{
			i = line->pos - (line->buf_len - 1);
			while (i--)
				move_left(line);
		}
	}
	return (0);
}

void	init_line(char	*prompt, t_line *line)
{
	ft_bzero(line->buf, MAX_BUF);
	ft_bzero(line->ici_doc, MAX_BUF);
	line->pos = 0;
	line->buf_len = 0;
	line->line_max = tgetnum("co");
	line->start_po = ft_strlen(prompt);
	line->his_mostdown = 1;
	line->his_mostup = 0;
	line->up_indown = 0;
	line->one_his = 0;
	line->last_his = history;

	line->printable = printable;
	line->move_left = move_left;
	line->move_right = move_right;
	line->move_nleft = move_nleft;
	line->move_nright = move_nright;
	line->delete_key = delete_key;
	line->mv_left_word = mv_left_word;
	line->mv_right_word = mv_right_word;
	line->history_up = history_up;
	line->history_down = history_down;
	line->cp_all = cp_all;
	line->cp_begin = cp_begin;
	line->cp_end = cp_end;
	line->cut_all = cut_all;
	line->cut_begin = cut_begin;
	line->cut_end = cut_end;
	line->paste = paste;
	line->go_up = go_up;
	line->go_down = go_down;
	line->engine = engine;
}


void	add_history(t_history **history, t_history *add)
{
	t_history	*temp;

	if (!*history)
		*history = add;
	else
	{
		temp = *history;
		(*history)->next = add;
		*history = add;
		(*history)->pre = temp;
	}
}

int		not_empty(char *new_line)
{
	int		i;

	i = -1;
	while (new_line[++i])
	{
		if (new_line[i] != ' ' && new_line[i] != '\t')
			return (1);
	}
	return (0);
}

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

int		open_quote_exit(char *line)
{
	int		open_dquote;
	int		open_squote;
	int		i;

	open_dquote = -1;
	open_squote = -1;
	i = -1;
	while (line[++i])
	{
		if (line[i] == '"' && open_squote < 0 && dslash_before(line, i))
			open_dquote = -open_dquote;
		else if (line[i] == '\'' && open_dquote < 0)
			open_squote = -open_squote;
		else if (line[i] == '\\' && open_dquote < 0 && open_squote < 0 && dslash_before(line, i) && !line[i + 1])
			return(return_message("\nUnmatched \\ .", 1));
	}
	if (open_dquote > 0)
		return(return_message("\nUnmatched \" .", 1));
	if (open_squote > 0)
		return(return_message("\nUnmatched \' .", 1));
	return (0);
}

int		get_line(char *prompt, char *new_line, t_line *line)
{
	unsigned long	key;

	ft_printf("%s", prompt);
	init_attr(SETNEW);
	init_line(prompt,line);
	while (((key = (int)get_key()) && key != '\n'))
	{
		if (key == '\n')
			break;
		line->engine(line, key);
	}
	init_attr(SETOLD);
	if (open_quote_exit((char *)line->buf))
		ft_bzero(line->buf, MAX_BUF);
	ft_strcpy(new_line, (const char *)line->buf);
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

void	redi_great(t_word *list)
{
	int		fd;
	int		into_fd;

	if (list->pre && list->pre->type == FD)
		fd = ft_atoi(list->pre->word);
	else
		fd = 1;
	into_fd = open(list->next->word, O_CREAT | O_TRUNC | O_RDWR, S_IWUSR | S_IRUSR);
	if (into_fd)
	{
	if (dup2(into_fd, fd) < 0)
		ft_printf("dup2 failed\n");
	close(into_fd);
	}
	else
		ft_printf("open file failed\n");
}

void	close_all_pipe(int *pipe_fd, int nb_pipe)
{
	int		i;

	i = 0;
	while (i < nb_pipe * 2)
		close(pipe_fd[i++]);
}

void	do_all_redirection(t_word *list, int *pipe_fd, int nb_pipe, int nb_pro)
{
	if (nb_pipe)
	{
	if (nb_pro > 0)
		close(pipe_fd[nb_pro * 2 - 1]);
		if (nb_pro)
		{
			if (dup2(pipe_fd[nb_pro * 2 - 2], 0) < 0)
				perror("dup2()");
		}
		if (nb_pro < nb_pipe)
			dup2(pipe_fd[nb_pro * 2 + 1], 1);
			/*
		if (nb_pro == nb_pipe)
			close(pipe_fd[1]);
		if (!nb_pro)
			close(pipe_fd[0]);
			*/
	}

	while (list && !is_logic(list->type) && list->type != SEMI_DOT && list->type != PIPE)
	{
		if (list->type == GREAT)
			redi_great(list);
		list = list->next;
	}
}

void	init_pid_table(int *table, int len)
{
	int		i;

	i = -1;
	while (++i < len)
		table[i] = -1;
}

void	do_all_pipe(int *pipe_fd, int nb_pipe)
{
	int		i;

	i = 0;
	while (++i <= nb_pipe)
	{
		if (pipe(pipe_fd) < 0)
			perror("pipe()");
		pipe_fd = pipe_fd + 2;
	}
}


void	actions_each_bloc(t_word *list, char **env)
{
	int			pipe_fd[MAX_BUF];
	t_program	pro[MAX_BUF];
	int			nb_pid[MAX_BUF];
	int			i;
	int			j;
	int			nb_pipe;

	nb_pipe = nb_pipe_eachbloc(list);
	i = -1;
	j = 0;
	ft_bzero(pro, sizeof(pro));
	init_pid_table(nb_pid, MAX_BUF);
	init_pid_table(pipe_fd, MAX_BUF);
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
	do_all_redirection(list, pipe_fd, nb_pipe, i);

	execve((pro[i].pro_args)[0], pro[i].pro_args, env);
	ft_printf("failed\n");
	}
	ft_printf("inside actions_each_bloc  00000\n");
	while (list && !is_logic(list->type) && list->type != SEMI_DOT && list->type != PIPE)
		list = list->next;
	ft_printf("list here is %s\n", list->word);
	if (list && list->type == PIPE)
		list = list->next;
	}
	while (j <= i)
	{
		close_all_pipe(pipe_fd, nb_pipe);
		//if (nb_pipe)
		//	close(pipe_fd[1]);
		if (waitpid(nb_pid[j++], NULL, 0) < 0)
			perror("wait()");
	}
}

void	actions_blocs(t_word *list, char **env)
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
			actions_each_bloc(list, env);
		}
	}
}

void	actions_each_line(char **env, char *new_line, t_history *add, t_word *list)
{
	init_add(add, new_line);
	add_history(&history, add);
	list = command_to_words(new_line);
	ft_printf("\n");
	print_words_type(list);
	print_ww(list);
	if (!err_in_words(list))
	{
		actions_blocs(list, env);
	}
}

int		prompt(char **env)
{
	char				new_line[MAX_BUF];
	t_history			*add;
	int					quit;
	t_line				line;
	t_word				*list;

	quit = 0;
	ft_strcpy(temp_file, "./42sh_tmp.c");
	while (!quit)
	{
		add = malloc(sizeof(t_history));
		ft_bzero(new_line, MAX_BUF);
		get_line("$> ",new_line, &line);
		if (not_empty(new_line))
			actions_each_line(env, new_line, add, list); 
		ft_printf("\n");
		if (!ft_strcmp(new_line, "exit"))
			quit = 1;
		//	ft_printf("new line =%s\n", new_line);
	}
	return (0);
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	prompt(env);
}
