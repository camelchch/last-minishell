#include <stdio.h>
#ifndef SHELL_SH
#define SHELL_SH

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define MAX_BUF 2048
#define NB_KEY 1
#define	ARROW_LEFT 4479771
#define ARROW_RIGH 4414235
#define	ARROW__UP 4283163
#define ARROW_DOWN 4348699
#define KEY_DELECT 10


typedef struct s_line
{
	size_t		key;
	int			pos;
	unsigned char	buf[MAX_BUF];
	int			buf_len;
	int			line_max;
	int			start_po;

	int			(*printable)(struct s_line *line, size_t a_key);
	int			(*move_left)(struct s_line *line);
//	int			(*move_nleft)(struct s_line *line);
	int			(*engine)(struct s_line *line, size_t a_key);
}				t_line;

typedef struct s_key
{
	size_t		a_key;
	int			(*func)(t_line *);
}				t_key;

size_t		get_key();
int			printable(t_line *line, size_t key);
#endif
