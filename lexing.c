#include <stdlib.h>
#include "parsing.h"

int			is_seprator(char *line, int index)
{
	if (index < ft_strlen(line))
	{
		if (line[index] == ' ' || line[index] == '<')
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
	else
	{
		ft_strcpy(add->word, "<");
		add->type = LESS;
		*index = *index + 1;
	}
	return (add);
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

void		modif_type(t_word *last, t_word *add)
{
	t_word		*cp;

	cp = last;
	if (add->type == PROGRAM)
	{
		if (is_redirector(cp->type))
			add->type = FILES;
		else
		{
			while (cp && cp->type != PROGRAM && cp->type != AND && cp->type != OR &&cp->type != PIPE)
				cp = cp->pre;
			if (cp && cp->type == PROGRAM)
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
		else if (cp->type == DLESS)
			ft_printf("DLESS ");
		else if (cp->type == AND)
			ft_printf("AND ");
		else if (cp->type == GREAT)
			ft_printf("GREAT ");
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
				ft_printf("%s ", add->word);
			res = add_word(res, add);
				print_words(add);
			}
		}
	}
	return (res);
}

int		main()
{
	t_word		*res;
	char *line = "\"ls -l 2\">   err.c && ls ;;";
	res = command_to_words(line);
	ft_printf("00000\n");
	print_words(res);
}
