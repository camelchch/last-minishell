#include "minishell.h"

static int		type_can_hv_quote(t_word *list)
{
	return (list->type == PROGRAM || list->type == ARG || list->type == FILES);
	return (0);
}

static int		include_quote(char *word)
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

void	change_part_str(char *ori, int start, int end, char *change)
{
	char	after[MAX_BUF];

	ft_bzero(after, MAX_BUF);
	ft_strcpy(after, ori + end + 1);
	ft_bzero(ori + start, MAX_BUF - start);
	ft_strcat(ori, change);
	ft_strcat(ori, after);
}

void	dollor_sign(t_helper *help, char *cp, char *vari)
{
	help->j = help->i + 1;
	while (cp[help->j] && cp[help->j] != '"')
		vari[(help->k)++] = cp[(help->j)++];
}

void	remove_quoting_list(t_word *list, char **env)
{
	while (list)
	{
		if (type_can_hv_quote(list))
		{
			remove_quoting_word(list->word, env);
		}
		list = list->next;
	}
}
