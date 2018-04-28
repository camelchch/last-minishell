#include <stdio.h>
#ifndef SHELL_SH
#define SHELL_SH

#define STDIN_FILENO 1
#define NB_KEY 1
#define	KEY_LEFT
#define KEY_RIGHT
#define	KEY_UP
#define KEY_DOWN
#define KEY_DELECT


typedef struct s_line
{
	size_t		key;
	int			pos;
	char		buf[2048];
	int			buf_len;

	int			(*move_left)(struct s_line *line);
	int			(*move_nleft)(struct s_line *line);
	int		(*engine)(struct s_line *line, size_t a_key);
}				t_line;

typedef struct s_key
{
	size_t		a_key;
	int		(*func)(t_line *);
}				t_key;

#endif
