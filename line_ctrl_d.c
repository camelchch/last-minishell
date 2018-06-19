#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include "minishell.h"

int			delete_at_position(t_line *line)
{
	if(line->pos < line->buf_len)
	{
		move_right(line);
		delete_key(line);
		move_left(line);
	}
	return (0);
}

int			ctrl_d(t_line *line)
{

	if (line->buf_len)
		delete_at_position(line);
	else
	{
		ft_printf("exit");
		exit(0);
	}
	return (0);
}
