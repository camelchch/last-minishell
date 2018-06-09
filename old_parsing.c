#include <stdlib.h>
#include "parsing.h"
#include "minishell.h"

#define WORD_LEN 4098

void	get_type(char **lecxi, int *tab, int tab_size)
{






}

t_list_token	*get_list(char **lecxi)
{

}

t_word			*add_word_list(t_word *list, t_word *add)
{
	t_word		*cp;

	cp = list;
	if (!cp)
		return (add);
	while (cp->next)
		cp = cp->next;
	cp->next = add;
	return (list);
}

int			nb_str(char **str)
{
	int		i;

	i = 0;
	if (str)
	{
	while (*str++)
		i++;
	}
	return (i);
}

t_word		init_add_word(t_word *add, char **lecxi)
{
	t_word	*add;

	add = malloc(sizeof(t_word));
	add->content = lecxi;
	add->next = NULL;
	if (!ft_strcmp(*lecxi, "<"))
		add->type = t_operand


}

void			init_word_type(t_word *list, char **lecxi)
{
	while (*lecxi)
	{

	}
	
}
