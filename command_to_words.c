#include "minishell.h"

static int		only_nb_str(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static void		modif_redi_type(t_word *last, t_word *add)
{
	add->type = FILES;
	if (last->type == DLESS)
		add->type = HERE_DOC_MARK;
}

static void		modif_type(t_word *last, t_word *add)
{
	t_word		*cp;

	cp = last;
	if (add->type == PROGRAM)
	{
		if (is_redirector(cp->type))
			modif_redi_type(cp, add);
		else if (cp->type == LESSAND || cp->type == GREATAND)
		{
			if (only_nb_str(add->word))
				add->type = FD;
			else
				add->type = FILES;;
		}
		else
		{
			if (program_exit_before(cp))
				add->type = ARG;
		}
	}
}

static t_word		*add_word(t_word *res, t_word *add)
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
				res = add_word(res, add);
		}
	}
	return (res);
}
