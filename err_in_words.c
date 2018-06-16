#include "minishell.h"

int			program_exit_before(t_word *li)
{
	while (li && li->type != PROGRAM && li->type != AND && li->type != OR && li->type != PIPE && li->type != SEMI_DOT)
		li = li->pre;
	if (li && li->type == PROGRAM)
		return (1);
	return (0);
}

static int			program_exit_after(t_word *li)
{
	while (li && li->type != PROGRAM && li->type != AND && li->type != OR\
			&& li->type != PIPE && li->type != SEMI_DOT)
		li = li->next;
	if (li && li->type == PROGRAM)
		return (1);
	return (0);
}

static int			heredoc_exit_before(t_word *li)
{
	while (li && li->type != DLESS && li->type != AND && li->type != OR &&\
			li->type != PIPE && li->type != SEMI_DOT)
		li = li->pre;
	if (li && li->type == DLESS)
		return (1);
	return (0);
}

static int		test_for_err_func(t_word *cp)
{
	if (cp->type == LESS || cp->type == GREAT || cp->type == GREATAND \
			|| cp->type == DGREAT)
	{
		if (!cp->next || (cp->next->type != FILES && cp->next->type != FD))
			return (1);
	}
	return (0);
}

// <<& >>& with & i didn't do err handing
int		err_in_words(t_word *cp)
{
	while (cp)
	{
		if (test_for_err_func(cp))
			return (return_message("\nMissing name for redirect.\n",1, 1));
		if (cp->type == DLESS)
		{
			if (!cp->next || cp->next->type != HERE_DOC_MARK)
				return (return_message("\nMissing name for redirect.\n",1, 1));
			if (heredoc_exit_before(cp->pre))
				return (return_message("\nAmbiguous input redirect.\n",1, 1));
		}
		if (is_redirector(cp->type) && !program_exit_before(cp->pre))
			return (return_message("\nInvalide null cmmand.\n", 1, 1));
		if (cp->type == LESSAND && (!cp->next || cp->next->type != FD))
			return (return_message("\nMissing file descriptor.\n",1, 1));
		if ((is_logic(cp->type) || cp->type == PIPE) &&\
			(!program_exit_before(cp->pre) || !program_exit_after(cp->next)))
			return (return_message("\nInvalide null cmmand.\n", 1, 1));
		cp = cp->next;
	}
	return (0);
}
