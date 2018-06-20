#include <termios.h>
#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include "minishell.h"

static int	raw_termi_mode()
{
	struct	termios	tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag &= ~(ECHO | ICANON | ISIG);
	tattr.c_oflag &= ~(OPOST);
	tattr.c_cc[VMIN] = 1;
	tattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN,&tattr);
	if (tgetent(NULL, getenv("TERM")) != 1)
			return (-1);
	return (0);
}

static void	default_termi_mode()
{
	struct	termios	tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag |= (ECHO | ICANON);
	tattr.c_oflag |= (OPOST);
	tcsetattr(STDIN_FILENO, TCSADRAIN,&tattr);
}

int		init_attr(int mod)
{
	static struct	termios old;
	static int				oldatt = 0;
	struct	termios			new;

	if (!oldatt)
	{
		oldatt = 1;
		if (tcgetattr(0, &old) == -1)
			return(return_message("can't get att", -1, 2));
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
	if (tgetent(NULL, getenv("TERM")) != 1)
	{
		default_termi_mode();
			return (-1);
	}
	}
	else
		//tcsetattr(STDIN_FILENO, TCSADRAIN, &old);
		default_termi_mode();
	return (0);
}


int			my_putc(int c)
{
	write(1, &c, 1);
	return (0);
}
