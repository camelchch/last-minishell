#include <unistd.h>
#include <curses.h>
#include <term.h>
#include "minishell.h"

int			move_nright(t_line *line)
{
	while  (line->pos < line->buf_len)
		move_right(line);
	return (0);
}

static void	for_delect_key(void)
{
			write(1, " ", 1);
			tputs(tgetstr("le", 0), 1, my_putc);
			tputs(tgetstr("nd", 0), 1, my_putc);
}

int			delete_key(t_line *l)
{
	int		i;
	int		new_pos;

	if (l->pos > 0)
	{
		i = l->pos - 2;
		while (++i < l->buf_len)
			l->buf[i] = l->buf[i + 1];
		new_pos = l->pos - 1;
		move_nleft(l);
		i = 0;
		l->buf_len = 0;
		l->pos = 0;
		while (l->buf[i])
			put_a_key(l, l->buf[i++]);
		if ((l->buf_len + l->start_po) % l->line_max == (l->line_max - 1))
			for_delect_key();
		else
			tputs(tgetstr("dc", 0), 1, my_putc);
		i = l->buf_len - new_pos;
		while (i-- > 0)
			move_left(l);
	}
	return (0);
}

int			delete_all(t_line *line)
{
	move_nright(line);
	while (line->buf_len)
		delete_key(line);
	return (0);
}
