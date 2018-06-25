#include <stdlib.h>
#include "minishell.h"

static void	init_add(t_history *add, char *new_line)
{
	ft_bzero(add->his, 0);
	ft_strcpy(add->his, new_line);
	add->next = NULL;
	add->pre = NULL;
}

static void	add_history(t_history **history, t_history *add)
{
	t_history	*temp;

	if (!*history)
		*history = add;
	else
	{
		temp = *history;
		(*history)->next = add;
		*history = add;
		(*history)->pre = temp;
	}
}

static int		not_empty(char *new_line)
{
	int		i;

	i = -1;
	while (new_line[++i])
	{
		if (new_line[i] != ' ' && new_line[i] != '\t')
			return (1);
	}
	return (0);
}

int			prompt(char **env, t_sh *table)
{
	t_history			*add;
	int					quit;
	t_word				*list;

	quit = 0;
	ft_strcpy(temp_file, "./42sh_tmp.c");
	while (!quit)
	{
		line_edition_ing = 1;
		add = malloc(sizeof(t_history));
		ft_bzero(new_line, MAX_BUF);
		get_line("$> ",new_line, &a_line);
			ft_printf("\n");
		if (not_empty(new_line))
		{
			line_edition_ing = 0;
			init_add(add, new_line);
			add_history(&history, add);
			list = command_to_words(new_line);
			actions_each_line(&env, list, table);
			free_word_list(list);
		}
		if (!ft_strcmp(new_line, "exit"))
			quit = 1;
	}
	return (0);
}
