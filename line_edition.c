#include <termios.h>
#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include "shell.h"
#include "minishell.h"

#define SETNEW 1
#define SETOLD 0


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

void	init_attr(int mod)
{
	static struct	termios *old;
	struct	termios			new;

	if (old == NULL)
		tcgetattr(STDIN_FILENO, old);
	if (mod == SETNEW)
	{
		new = *old;
		new.c_lflag &= ~(ECHO | ICANON);
		new.c_oflag &= ~(OPOST);
		new.c_cc[VMIN] = 1;
		new.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSADRAIN, &new);
	}
	else
		tcsetattr(STDIN_FILENO, TCSADRAIN, old);
}

void	default_termi_mode()
{
	struct	termios	tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag |= (ECHO | ICANON);
	tattr.c_oflag |= (OPOST);
	tcsetattr(STDIN_FILENO, TCSADRAIN,&tattr);
}

/*
 * void	init_keytab(t_key *tab, int NB_KEY)
{
	int		i;

	i = 0;
}
*/

int		engine(t_line *line, size_t key)
{
	int		i;

	i = 0;
	t_key	t[NB_KEY] = {
		{KEY_LEFT, line->move_left},
		{KEY_RIGHT, line->move_right},
		{KEY_BEGIN, line->move_nleft},
		{KEY_LAST, line->move_nright},
		{KEY_DELECT, line->delete}
	};

	while (i < NB_KEY)
	{
		if (key == (t[i].a_key))
				t[i].func(line);
		i++;
	}
	return (0);
}


int		move_nleft(t_line *line)
{
	while (line->pos > 0)
		line->move_left(line);
}


int		my_putc(int c)
{
	write(1, &c, 1);
	return (0);
}

int		move_left(t_line *line)
{
	tputs(tgetstr("li", 0), 1, my_putc);
	line->pos -= 1;
}

int		delete_key(t_line *line)
{
	line->move_left(line);
	tputs(tgetstr("li", 0), 1, my_putc);
}


size_t		get_key()
{
	char	buff[4];

	ft_bzero(buff, 4);
	read(0, buff, 4);
	return (*buff + (*buff << 8) + (*buff << 16) + (*buff << 24));
}

void	init(t_line *line)
{

}

char	*get_line()
{
	size_t		key;

	key = get_key();


}

int		main()
{

	return (0);
}
