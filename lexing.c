#include <stdlib.h>
#include "parsing.h"

int			is_seprator(char *line, int index)
{
	if (index < ft_strlen(line))
	{
		return (line[index] == '<' || \
				(line[index] == '&' &&
				 index + 1 < ft_strlen(line) && line[index + 1] == '&') \
				line[index] == '>' || line[index] == | || line[index] == ';');
	}
	return (0);
}

void		less_type(char *line, int *index, t_word *add)
{
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
}

void		great_type(char *line, int *index, t_word *add)
{
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
}

void		pipe_or_type(char *line, int *index, t_word *add)
{
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
}

void		and_type(char *line, int *index, t_word *add)
{
	if (*index + 1 < ft_strlen(line) && line[*index + 1] == '&')
	{
		ft_strcpy(add->word, "&&");
		add->type = AND;
		*index = *index + 2;
	}
}

void		semidot_type(char *line, int *index, t_word *add)
{
	ft_strcpy(add->word, ";");
	add->type = SEMI_DOT;
	*index = *index + 1;
}

void		init_seprator(char *line, int *index, t_word *add)
{
	if (line[*index] == '<')
		less_type(line, index, add);
	else if (line[*index] == '>')
		great_type(line, index, add);
	else if (line[*index] == '|')
		pipe_or_type(line, index, add);
	else if (line[*index] == '&')
		and_type(line, index, add);
	else if (line[*index] == ';')
		semidot_type(line, index, add);
}

t_word		*init_add_word(char *line, int *i, int *j)
{
	t_word	*add;
	int		open_dquote;
	int		open_squote;

	open_dquote = -1;
	open_squote = -1;
	add = malloc(sizeof(t_word));
	add->next = NULL;
	ft_bzero(add->word, MAX_BUF);
	if (open_dquote < 0 && open_squote < 0 && *i < ft_strlen(line) && is_seprator(line, *i))
		init_seprator(line, i, add);
	else
	{
		while ((open_dquote > 0 || open_squote > 0|| !is_seprator(line, *i)) && *i < ft_strlen(line))
		{
			if (line[*i] == '"' && open_squote < 0)
				open_dquote = -open_dquote;
			if (line[*i] == '\'' && open_dquote < 0)
				open_dquote = -open_squote;
			add->word[*j++] = line[*i++];
		}
		add->type = PROGRAM;
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
	cp->next = add;
	return (res);
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
		while (i < ft_strlen(line) && line[i] == ' ')
			i++;
		if (i < ft_strlen(line))
		{
			add = init_add_word(line, &i, &j);
			res = add_word(res, add);
		}
	}	
}
