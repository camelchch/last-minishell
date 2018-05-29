#ifndef PARSING_H
#define PARSING_H

ls > file1 2>&- && cat -e file1 | less

WORD  >>>> ls   >    file1  2>&-    cat -e  file1  |    less
TOKEN >>>> BIN DLESS FILE  GREATAND BIN OPT FILE  PIPE  BIN

~~ exemple fait a l'arrache ~~
struct t_token {
	BIN,
	BUILTIN,
	OPERAND
	FILE
}

enum s_operand {
	LESS,//<
	DLESS, //<<
	AND, //&&
	GREAT, //>
	DGREAT, //>>
	OR,//||
	PIPE, //|
}	t_operand;


t_list *l;


if (l->next->tok == SUBTOKEN)
{
	if (l->next->tok == PIPE)
		dup2(l->out.fd, STDOUT_FILENO);
}

if (l->prev->tok == SUBTOKEN && l->prev->sub == PIPE)



struct list_bin {
	t_token		*tok; 
	t_operand	*next; (default null)
	t_operand	*prev; (default null)
	char		*name;
	list_file	out;
	list_file	in
	char		**args;
	char		**env;
	list_bin	*next;
	list_bin	*prev;
}

strct list_file {
	char 	*name;
	int	fd;
}

ls | less



execve(ls) out > execve(less) > open(file)

#endif
