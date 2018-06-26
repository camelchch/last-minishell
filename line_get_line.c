#include <stdlib.h>
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
	line->ctrl_d = ctrl_d;
	line->delete_at_position = delete_at_position;
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

int					get_line(char *prompt, char *new_line, t_line *line)
{
	unsigned long	key;
	char			*ligne;

	ligne = NULL;
	end_line = 0;
	ft_printf("%s", prompt);
	if (init_attr(SETNEW) == 0)
	{
		with_termcap = 1;
		init_line(prompt,line);
		while (((key = (int)get_key()) && key != '\n') && !end_line)
			line->engine(line, key);
		init_attr(SETOLD);
		ft_strcpy(new_line, (const char *)line->buf);
	}
	else
	{
		get_next_line(1, &ligne);
		ft_strcpy(new_line, (const char *)ligne);
		ligne ? free(ligne) : (void)ligne;
	}
	return (0);
}
