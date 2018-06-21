#include "minishell.h"

int			dslash_before(char *line, int index)
{
	int		i;
	int		j;

	i = 0;
	j = index - 1;
	while (j >= 0 && line[j] == '\\')
	{
		i++;
		j--;
	}
	if (!(i % 2))
		return(1);
	return (0);
}


void		print_list_word(t_word *list)
{
	while(list)
	{
		ft_printf("%s ", list->word);
		list = list->next;
	}
}

static void	actions_blocs(t_word *list, char **env, t_sh *table)
{
	t_word	*cp;
	int		find_bloc;
	int		find_err;

	find_bloc = 0;
	find_err = 0;
	cp = list;
	while (cp)
	{
	while (cp && !is_logic(cp->type) && cp->type != SEMI_DOT)
	{
		if (!remove_quoting_bloc(cp, env))
			actions_each_bloc(cp, env, table);
	while (cp && !is_logic(cp->type) && cp->type != SEMI_DOT)
			cp = cp->next;
	if (cp && cp->type != SEMI_DOT)
		cp = cp->next;
	}
	if (cp)
		cp = cp->next;
	}
}

void		actions_each_line(char **env, t_word *list, t_sh *table)
{
	if (!err_in_words(list))
		actions_blocs(list, env, table);
}
