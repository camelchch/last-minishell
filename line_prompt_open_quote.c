#include "minishell.h"

//the case '\\\' is not yet totally done
static int			open_quote_exit(char *line)
{
	int		i;

	i = -1;
	open_squote = -1;
	open_dquote = -1;
	open_backslash = -1;
	while (line[++i])
	{
		if (line[i] == '"' && open_squote < 0 && dslash_before(line, i))
			open_dquote = -open_dquote;
		else if (line[i] == '\'' && open_dquote < 0 && !(!dslash_before(line, i) && open_squote < 0))
			open_squote = -open_squote;
		else if (line[i] == '\\' && open_dquote < 0 && open_squote < 0 && \
				dslash_before(line, i) && !line[i + 1])
			open_backslash = -open_backslash;
	}
	if (open_dquote > 0 || open_squote > 0 || open_backslash > 0)
		return(1);
	return (0);
}

void				prompt_open_quote(char *line)
{
	char	new_line[MAX_BUF];
	t_line	quote_line;

	while (open_quote_exit(line))
	{
		ft_bzero(new_line, MAX_BUF);
		if (open_backslash > 0)
		{
			get_line("> ", new_line, &quote_line);
			line[ft_strlen(line) - 1] = '\0';
			ft_strcat(line, new_line);
			with_termcap ? ft_printf("\n") : (void)with_termcap;
		}
		else
		{
			ft_strcat(line, "\n");
			if (open_dquote > 0)
				get_line("dquote> ", new_line, &quote_line);
			else
				get_line("quote> ", new_line, &quote_line);
			ft_strcat(line, new_line);
			with_termcap ? ft_printf("\n") : (void)with_termcap;
		}
	}
}
