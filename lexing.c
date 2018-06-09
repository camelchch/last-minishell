#include <stdlib.h>
#include "minishell.h"
// <<& >>& with & i didn't do err handing
int			is_seprator(char *line, int index)
{
	if (index < ft_strlen(line))
	{
		if (line[index] == ' '  || line[index ] == '\t' || line[index] == '<')
			return (1);
		if (line[index] == '&' && index + 1 < ft_strlen(line) && line[index + 1] == '&')
			return (1);
		if (line[index] == '>' || line[index] == '|' || line[index] == ';')
			return (1);
	}
	return (0);
}

t_word		*malloc_add(void)
{
	t_word		*add;

	add = malloc(sizeof(t_word));
	add->next = NULL;
	add->pre = NULL;
	ft_bzero(add->word, MAX_BUF);
	return (add);
}

void		less_and(char *line, int *index, t_word *add)
{
	if (*index + 2 < ft_strlen(line) && line[*index + 2] == '-' && \
			(*index + 3 >= ft_strlen(line) || is_seprator(line, *line + 3 )))
	{
		ft_strcpy(add->word, "<&-");
		add->type = LESSANDMINUS;
		*index = *index + 3;
	}
	else
	{
		ft_strcpy(add->word, "<&");
		add->type = LESSAND;
		*index = *index + 2;
	}
}

t_word		*less_type(char *line, int *index)
{
	t_word		*add;

	add = malloc_add();
	if (*index + 1 < ft_strlen(line) && line[*index + 1] == '<')
	{
		ft_strcpy(add->word, "<<");
		add->type = DLESS;
		*index = *index + 2;
	}
	else if (*index + 1 < ft_strlen(line) && line[*index + 1] == '&')
		less_and(line, index, add);
	else
	{
		ft_strcpy(add->word, "<");
		add->type = LESS;
		*index = *index + 1;
	}
	return (add);
}

void		great_and(char *line, int *index, t_word *add)
{
	if (*index + 2 < ft_strlen(line) && line[*index + 2] == '-' && \
			(*index + 3 >= ft_strlen(line) || is_seprator(line, *line + 3 )))
	{
		ft_strcpy(add->word, ">&-");
		add->type = GREATANDMINUS;
		*index = *index + 3;
	}
	else
	{
		ft_strcpy(add->word, ">&");
		add->type = GREATAND;
		*index = *index + 2;
	}
}

t_word		*great_type(char *line, int *index)
{
	t_word		*add;

	add = malloc_add();
	if (*index + 1 < ft_strlen(line) && line[*index + 1] == '>')
	{
		ft_strcpy(add->word, ">>");
		add->type = DGREAT;
		*index = *index + 2;
	}
	else if (*index + 1 < ft_strlen(line) && line[*index + 1] == '&')
		great_and(line, index, add);
	else
	{
		ft_strcpy(add->word, ">");
		add->type = GREAT;
		*index = *index + 1;
	}
	return (add);
}

t_word		*pipe_or_type(char *line, int *index)
{
	t_word		*add;

	add = malloc_add();
	if (*index + 1 < ft_strlen(line) && line[*index + 1] == '|')
	{
		ft_strcpy(add->word, "||");
		add->type = OR;
		*index = *index + 2;
	}
	else
	{
		ft_strcpy(add->word, "|");
		add->type = PIPE;
		*index = *index + 1;
	}
	return (add);
}

t_word		*and_type(char *line, int *index)
{
	t_word		*add;

	add = malloc_add();
	if (*index + 1 < ft_strlen(line) && line[*index + 1] == '&')
	{
		ft_strcpy(add->word, "&&");
		add->type = AND;
		*index = *index + 2;
	}
	return (add);
}

t_word		*semidot_type(char *line, int *index)
{
	t_word		*add;

	add = malloc_add();
	ft_strcpy(add->word, ";");
	add->type = SEMI_DOT;
	*index = *index + 1;
	return (add);
}

t_word		*init_seprator(char *line, int *index)
{
	if (line[*index] == '<')
		return (less_type(line, index));
	else if (line[*index] == '>')
		return (great_type(line, index));
	else if (line[*index] == '|')
		return (pipe_or_type(line, index));
	else if (line[*index] == '&')
		return (and_type(line, index));
	else if (line[*index] == ';')
		return (semidot_type(line, index));
	else if (line[*index] == ';')
		return (semidot_type(line, index));
	else if (line[*index] == ' ')
		*index = *index + 1;
	return (NULL);
}

t_word		*init_add_word(char *line, int *i, int *j)
{
	t_word	*add;
	int		open_dquote;
	int		open_squote;
	int		only_nb;

	open_dquote = -1;
	open_squote = -1;
	add = NULL;
	only_nb = 1;
	// in this func j don't need to be passed in args
	*j = 0;
	if (open_dquote < 0 && open_squote < 0 && *i < ft_strlen(line) && is_seprator(line, *i))
		return (init_seprator(line, i));
	else
	{
		add = malloc_add();
		while ((open_dquote > 0 || open_squote > 0|| !is_seprator(line, *i)) && *i < ft_strlen(line))
		{
			if (line[*i] < '0' || line[*i] > '9')
				only_nb = 0;
			if (line[*i] < '0' || line[*i] > '9')
				if (line[*i] == '"' && open_squote < 0)
					open_dquote = -open_dquote;
			if (line[*i] == '\'' && open_dquote < 0)
				open_dquote = -open_squote;
			add->word[*j] = line[*i];
			*j = *j + 1;
			*i = *i + 1;
		}
		if (only_nb && (line[*i] == '<' || line[*i] == '>'))
			add->type = FD;
		else
			add->type = PROGRAM;
	}
	return (add);
}

int			is_redirector(t_type type)
{
	if (type == LESS || type == DLESS || type == GREAT || type == DGREAT)
		return (1);
	return (0);
}

int			is_logic(t_type type)
{
	return (type == AND || type == OR);
	return (0);
}

int		only_nb_str(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int			program_exit_before(t_word *li)
{
	while (li && li->type != PROGRAM && li->type != AND && li->type != OR && li->type != PIPE && li->type != SEMI_DOT)
		li = li->pre;
	if (li && li->type == PROGRAM)
		return (1);
	return (0);
}

int			program_exit_after(t_word *li)
{
	while (li && li->type != PROGRAM && li->type != AND && li->type != OR && li->type != PIPE && li->type != SEMI_DOT)
		li = li->next;
	if (li && li->type == PROGRAM)
		return (1);
	return (0);
}

int			heredoc_exit_before(t_word *li)
{
	while (li && li->type != DLESS && li->type != AND && li->type != OR && li->type != PIPE && li->type != SEMI_DOT)
		li = li->pre;
	if (li && li->type == DLESS)
		return (1);
	return (0);
}

void		modif_redi_type(t_word *last, t_word *add)
{
	add->type = FILES;
	if (last->type == DLESS)
		add->type = HERE_DOC_MARK;
}

void		modif_type(t_word *last, t_word *add)
{
	t_word		*cp;

	cp = last;
	if (add->type == PROGRAM)
	{
		if (is_redirector(cp->type))
			modif_redi_type(cp, add);
		else if (cp->type == LESSAND || cp->type == GREATAND)
		{
			if (only_nb_str(add->word))
				add->type = FD;
			else
				add->type = FILES;;
		}
		else
		{
			if (program_exit_before(cp))
				add->type = ARG;
		}
	}
}

t_word		*add_word(t_word *res, t_word *add)
{
	t_word	*cp;

	cp = res;
	if (!res)
		return (add);
	while (cp->next)
		cp = cp->next;
	modif_type(cp, add);
	add->pre = cp;
	cp->next = add;
	return (res);
}

void	print_words(t_word *list)
{
	t_word	*cp;

	cp = list;
	while (cp)
	{
		if (cp->type == PROGRAM)
			ft_printf("PROGRAM ");
		else if (cp->type == ARG)
			ft_printf("ARG ");
		else if (cp->type == LESS)
			ft_printf("LESS ");
		else if (cp->type == LESSAND)
			ft_printf("LESSAND ");
		else if (cp->type == LESSANDMINUS)
			ft_printf("LESSANDMINUS");
		else if (cp->type == DLESS)
			ft_printf("DLESS ");
		else if (cp->type == AND)
			ft_printf("AND ");
		else if (cp->type == GREAT)
			ft_printf("GREAT ");
		else if (cp->type == GREATAND)
			ft_printf("GREATAND ");
		else if (cp->type == GREATANDMINUS)
			ft_printf("GREATANDMINUS ");
		else if (cp->type == DGREAT)
			ft_printf("DREAT ");
		else if (cp->type == OR)
			ft_printf("OR ");
		else if (cp->type == PIPE)
			ft_printf("PIPE ");
		else if (cp->type == SEMI_DOT)
			ft_printf("SEMI_DOT ");
		else if (cp->type == FILES)
			ft_printf("FILES ");
		else if (cp->type == FD)
			ft_printf("FD ");
		else if (cp->type == HERE_DOC_MARK)
			ft_printf("HERE_DOC_MARK ");
		cp = cp->next;
	}
}

t_word		*command_to_words(char *line)
{
	t_word	*add;
	t_word	*res;
	int		i;
	int		j;

	res = NULL;
	i = 0;
	j = 0;
	while (i < ft_strlen(line))
	{
		if (i < ft_strlen(line))
		{
			add = init_add_word(line, &i, &j);
			if (add)
			{
				//ft_printf("%s ", add->word);
				res = add_word(res, add);
			}
		}
	}
	return (res);
}

int		return_message(char *message, int re_value)
{
	ft_printf("%s", message);
	return (re_value);
}

int		err_in_words(t_word *list)
{
	t_word	*cp;
	t_word	*pre;
	t_word	*next;

	cp = list;
	while (cp)
	{
		if (cp->type == LESS || cp->type == GREAT || cp->type == GREATAND || cp->type == DGREAT)
		{
			if (!cp->next || (cp->next->type != FILES && cp->next->type != FD))
				return (return_message("\nMissing name for redirect.\n",1));
		}
		if (cp->type == DLESS)
		{
			if (!cp->next || cp->next->type != HERE_DOC_MARK)
				return (return_message("\nMissing name for redirect.\n",1));
			if (heredoc_exit_before(cp->pre))
				return (return_message("\nAmbiguous input redirect.\n",1));
		}
		if (is_redirector(cp->type) && !program_exit_before(cp->pre))
			return (return_message("\nInvalide null cmmand.\n", 1));
		if (cp->type == LESSAND && (!cp->next || cp->next->type != FD))
			return (return_message("\nMissing file descriptor.\n",1));
		if ((is_logic(cp->type) || cp->type == PIPE) && (!program_exit_before(cp->pre) || !program_exit_after(cp->next)))
			return (return_message("\nInvalide null cmmand.\n", 1));
		cp = cp->next;
	}
	return (0);
}

/*
int		main()
{
	t_word		*res;
	char *line = ";;";
	res = command_to_words(line);
	ft_printf("\n");
	print_words(res);
	if (err_in_words(res))
		ft_printf("there is err\n");
}
*/
