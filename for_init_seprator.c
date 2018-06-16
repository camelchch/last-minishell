#include <unistd.h>
#include "minishell.h"

t_word		*pipe_or_type(char *line, int *index)
{
	t_word		*add;

	add = malloc_add();
	if (*index + 1 < (int)ft_strlen(line) && line[*index + 1] == '|')
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
	if (*index + 1 < (int)ft_strlen(line) && line[*index + 1] == '&')
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

	(void)line;
	add = malloc_add();
	ft_strcpy(add->word, ";");
	add->type = SEMI_DOT;
	*index = *index + 1;
	return (add);
}

//if write failed/? 
int		return_message(char *message, int re_value, int fd)
{
	write(fd, message, ft_strlen(message));
	return (re_value);
}
