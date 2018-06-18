#include <curses.h>
#include <term.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "minishell.h"

static unsigned long	get_key()
{
	unsigned char	buff[6];

	ft_bzero(buff, 6);
	read(0, buff, 6);
	return (buff[0] +( buff[1] << 8) + (buff[2] << 16) + (buff[3] << 24) +\
			((unsigned long)buff[4] << 32) + ((unsigned long)buff[5] << 40));
}

static void				for_init_line(t_line *line)
{
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

void			init_line(char	*prompt, t_line *line)
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
	for_init_line(line);

}

static int			open_quote_exit(char *line)
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
		else if (line[i] == '\\' && open_dquote < 0 && open_squote < 0 && \
		dslash_before(line, i) && !line[i + 1])
			return(return_message("\nUnmatched \\ .", 1, 1));
	}
	if (open_dquote > 0)
		return(return_message("\nUnmatched \" .", 1, 1));
	if (open_squote > 0)
		return(return_message("\nUnmatched \' .", 1, 1));
	return (0);
}

int					get_line(char *prompt, char *new_line, t_line *line)
{
	unsigned long	key;

	init_attr(SETOLD);
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
