#ifndef PARSING_H
#define PARSING_H
/*
ls -la /bin > file1 2>&- && cat -e file1 | less

WORD  >>>> ls   >    file1  2>&-    cat -e  file1  |    less
TOKEN >>>> BIN DLESS FILE  GREATAND BIN OPT FILE  PIPE  BIN

~~ exemple fait a l'arrache ~~
*/

typedef enum s_token {
	BIN = 0,
	BUILTIN,
//	OPT,
//	ARG,
	FILEREDI,
	OPERAND,
	//FILES,
}			t_token;

typedef enum s_type {
	PROGRAM = 10,
	ARG, //11
	LESS,//< 12
	LESSAND,// <&
	LESSANDMINUS,// <&-
	DLESS, //<< 13
	AND, //&& 14
	GREAT, //> 15
	GREATAND, // >& 15
	GREATANDMINUS, // >&- 15
	DGREAT, //>> 16
	OR,//|| 17
	PIPE, //| 18
	SEMI_DOT, // 19;
	FILES, //20
	FD, //21
	HERE_DOC_MARK,
}			t_type;

typedef struct	s_word{
	char			word[MAX_BUF];
	t_type			type;
	struct s_word	*next;
	struct s_word	*pre;
}				t_word;
/*
t_list *l;


if (l->next->tok == SUBTOKEN)
{
	if (l->next->tok == PIPE)
		dup2(l->out.fd, STDOUT_FILENO);
}

if (l->prev->tok == SUBTOKEN && l->prev->sub == PIPE)
*/


typedef struct	s_file{
	char 	*name;
	int		fd;
}		t_file;

typedef struct		s_list_token{
	t_token			*tok; 
//	t_operand		*next; //(default null)
//	t_operand		*prev; //(default null)
	char			*name;
	t_file			out;
	t_file			in;
	char			**args;
//	char			*opt;
	char			**env;
	struct s_list_token	*after;
	struct s_list_token	*before;
}					t_list_token;


//ls | less



//execve(ls) out > execve(less) > open(file)

#endif
