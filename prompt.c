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
	char				new_line[MAX_BUF];
	t_history			*add;
	int					quit;
	t_line				line;
	t_word				*list;

	quit = 0;
	(void)table;
	ft_strcpy(temp_file, "./42sh_tmp.c");
	while (!quit)
	{
		add = malloc(sizeof(t_history));
		ft_bzero(new_line, MAX_BUF);
		get_line("$> ",new_line, &line);
		if (not_empty(new_line))
		{
			init_add(add, new_line);
			add_history(&history, add);
			list = command_to_words(new_line);
			actions_each_line(env, list, table);
		}
		ft_printf("\n");
		if (!ft_strcmp(new_line, "exit"))
			quit = 1;
		//	ft_printf("new line =%s\n", new_line);
	}
	return (0);
}

