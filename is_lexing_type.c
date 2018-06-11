#include "minishell.h"

int			is_seprator_w(char *line, int index)
{
	if (index < ft_strlen(line))
	{
		if (line[index] == ' '  || line[index ] == '\t' || line[index] == '<')
			return (1);
		if (line[index] == '&' && index + 1 < ft_strlen(line) && \
				line[index + 1] == '&')
			return (1);
		if (line[index] == '>' || line[index] == '|' || line[index] == ';')
			return (1);
	}
	return (0);
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
