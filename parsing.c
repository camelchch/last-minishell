#include "minishell.h"

int		type_can_hv_quote(t_word *list)
{
	return (list->type == PROGRAM || list->type == ARG || list->type == FILES);
	return (0);
}

// backquote didnt handle properly ex: \\" return 1 double quote
int		include_quote(char *word)
{
	int		i;

	i = 0;
	while (word[i])
	{
		if ((word[i] == '"' || word[i] == '\'') && \
			( i - 1 < 0 || word[i - 1] != '\\'))
		return (1);
	}
	return (0);
}

void	remove_quoting_word(char *word)
{
	int		i;
	int		j;
	int		k;
	char	cp[MAX_BUF];
	char	vari[MAX_BUF];
	int		open_dquote;
	int		open_squote;

	open_dquote = -1;
	open_squote = -1;
	i = 0;
	j = 0;
	ft_bzero(cp, MAX_BUF);
	ft_bzero(vari, MAX_BUF);
	ft_strcpy(cp, word);
	ft_bzero(word, MAX_BUF);
	while (cp[i])
	{
		if (open_squote < 0 && cp[i] == '$')
		{
			j = i + 1;
			while (cp[j] && cp[j] != '"')
				vari[
		}
		if ((cp[i] == '"' || cp[i] == '\'') && \
			( i - 1 < 0 || word[i - 1] != '\\'))
		{

		}
	}

}

void	remove_quoting_list(t_word *list)
{
	while (list)
	{
		if (type_can_hv_quote(list))
		{
			if (include_quote(list->word))
		}
	}
}
