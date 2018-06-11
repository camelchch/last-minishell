#include "minishell.h"

void	print_words_type(t_word *list)
{
	t_word	*cp;

	cp = list;
	while (cp)
	{
		if (cp->type == PROGRAM)
			ft_printf("PROGRAM ");
		else if (cp->type == ARG)
			ft_printf("ARG ");
		else if (cp->type == LESS)
			ft_printf("LESS ");
		else if (cp->type == LESSAND)
			ft_printf("LESSAND ");
		else if (cp->type == LESSANDMINUS)
			ft_printf("LESSANDMINUS");
		else if (cp->type == DLESS)
			ft_printf("DLESS ");
		else if (cp->type == AND)
			ft_printf("AND ");
		else if (cp->type == GREAT)
			ft_printf("GREAT ");
		else if (cp->type == GREATAND)
			ft_printf("GREATAND ");
		else if (cp->type == GREATANDMINUS)
			ft_printf("GREATANDMINUS ");
		else if (cp->type == DGREAT)
			ft_printf("DREAT ");
		else if (cp->type == OR)
			ft_printf("OR ");
		else if (cp->type == PIPE)
			ft_printf("PIPE ");
		else if (cp->type == SEMI_DOT)
			ft_printf("SEMI_DOT ");
		else if (cp->type == FILES)
			ft_printf("FILES ");
		else if (cp->type == FD)
			ft_printf("FD ");
		else if (cp->type == HERE_DOC_MARK)
			ft_printf("HERE_DOC_MARK ");
		cp = cp->next;
	}
}
