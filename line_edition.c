#include <termios.h>
#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
//#include "shell.h"
#include "minishell.h"

#define SETNEW 1
#define SETOLD 0
char		**history;


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
		new.c_oflag &= ~(OPOST);
		new.c_cc[VMIN] = 1;
		new.c_cc[VTIME] = 0;
		tcsetattr(STDIN_FILENO, TCSADRAIN, &new);
		tgetent(NULL, getenv("TERM"));
	}
	else
		//tcsetattr(STDIN_FILENO, TCSADRAIN, &old);
		default_termi_mode();
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
	if ((32 <= key && key <= 126))
		line->printable(line, key);
	else
	{
		t_key	t[NB_KEY] = {
			{ARROW_LEFT, line->move_left},
			{ARROW_RIGHT, line->move_right},
			{MY_DELECT, line->delete_key},
			//	{KEY_LAST, line->move_nright},
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


int		move_nleft(t_line *line)
{
	while (line->pos > 0)
		line->move_left(line);

	return (0);
}


int		my_putc(int c)
{
	write(1, &c, 1);
	return (0);
}

int		move_left(t_line *line)
{
	if (line->pos)
	{
		tputs(tgetstr("le", 0), 1, my_putc);
		line->pos -= 1;
	}

	return (0);
}

int		move_right(t_line *line)
{
	if (line->pos < line->buf_len)
	{
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

	line->move_left(line);
	if (line->pos >= 0)
		tputs(tgetstr("dc", 0), 1, my_putc);
	i = line->pos - 1;
	while (++i < line->buf_len - 1)
		line->buf[i] = line->buf[i + 1];
	line->buf_len--;

	return (0);
}

int		printable(t_line *line, size_t key)
{
	int		index;

	if (line->pos == line->buf_len)
	{
		(line->buf)[line->buf_len] = key;
		write(STDOUT_FILENO, line->buf + line-> pos, 1);
	}
	else
	{
		index = line->buf_len + 1;
		while (--index > line->pos)
			line->buf[index] = line->buf[index -1];
		line->buf[line->pos] = key;
		write(1, line->buf + line->pos, line->buf_len - line->pos + 1);
		index = line->buf_len - line->pos + 2;
		while (--index > 1)
			tputs(tgetstr("le", 0), 1, my_putc);
	}
	line->pos++;
	line->buf_len++;

	return (0);
}

size_t		get_key()
{
	unsigned char	buff[4];

	ft_bzero(buff, 4);
	read(0, buff, 4);
	return (buff[0] +( buff[1] << 8) + (buff[2] << 16) + (buff[3] << 24));
}

void	init_line(t_line *line)
{
	ft_bzero(line->buf, MAX_BUF);
	line->key = 0;
	line->pos = 0;
	line->buf_len = 0;
	line->line_max = tgetnum("co");
	line->start_po = 4;
	line->printable = printable;
	line->move_left = move_left;
	line->move_right = move_right;
	line->delete_key = delete_key;
	//	line->move_nleft = move_nleft;
	line->engine = engine;


}

void	get_line(char *new_line)
{
	size_t		key;
	t_line		line;

	ft_printf("$> ");
	init_attr(SETNEW);
	init_line(&line);
	while ((key = (int)get_key()) != EOF && key != '\n')
		line.engine(&line, key);
	init_attr(SETOLD);
	ft_strcpy(new_line, (const char *)line.buf);
}

int		main()
{
	char new_line[2048];

	ft_bzero(new_line, 2048);
	get_line(new_line);
	ft_printf("new line =%s\n", new_line);

	return (0);
}
