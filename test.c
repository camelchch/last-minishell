#include <fcntl.h>
#include <unistd.h>


typedef enum {
	BIN,
	NUILTIN,
	AND, // &&
	OR, // ||
	LESS, // <
	DLESS // >
}

typedef struct s_le
{
	char		*buff;
	int (*move_cursor)(struct s_le *);
	int (*engine)(struct s_le *, size_t);
}				t_le;

typedef struct s_t
{
	int			key;
	int (*func)(struct s_le *);
}				t_t;
//line edition
int  line_edition(size_t key)
{
	return 0;
}

int		engine(t_le *this, size_t key)
{
	t_t		tableau[NB_KEY] = {
		{KEY_LEFT, this->move_lcursor},
		{KEY_RIGHT, this->move_rcursor}
	};
	
	for (i = 0; i < NB_KEY, ++i)
	ea
		if (key == tableau[i].key)
			tableau[i].func;
	}
	return (0);
}

int		move_cursor(t_le *this)
{
	//
	//
	//
	//
	//
	return (0);
}

void	init(t_le *l)
{
	l->move_cursor = move_cursor;
	l->engine = engine;
}

int		main(void)
{
	t_le	l;
	int		key = 1000;

	init(&l);
	l.engine(&l, key);
	return (0);

}
