#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

static t_save_fd	*add_2recover(t_save_fd *recover, int nb_fd)
{
	t_save_fd	*add;
	t_save_fd	*cp;
	int			save_in2;

	cp = recover;
	add = malloc(sizeof(t_save_fd));
	add->next = NULL;
	if ((save_in2 = dup(nb_fd)) < 0)
		ft_putendl_fd("dup inside add_2recover failed", 2);
	add->fd_2be_saved = nb_fd;
	add->fd_saved_in2 = save_in2;
	if (!recover)
		return (add);
	while (cp->next)
		cp = cp->next;
	cp->next = add;
	return (recover);
}

t_save_fd		*fd_restorage(t_word *l, t_save_fd *recover)
{
	int			n;

	while (l && !is_logic(l->type) && l->type != SEMI_DOT)
	{
		if (l->type == LESS || l->type == LESSAND || l->type == LESSANDMINUS)
		{
			n = (l->pre && l->pre->type == FD) ? ft_atoi(l->pre->word) : 0;
				recover = add_2recover(recover, n);
		}
		if (l->type == GREAT || l->type == GREATAND || l->type == GREATANDMINUS || l->type == DGREAT)
		{
			n = (l->pre && l->pre->type == FD) ? ft_atoi(l->pre->word) : 1;
				recover = add_2recover(recover, n);
		}
		l = l->next;
	}
return(recover);
}

void		recover_fd(t_save_fd *recover)
{
	while (recover)
	{
		if (dup2(recover->fd_saved_in2, recover->fd_2be_saved) < 0)
			ft_putendl_fd("dup failled in recover_fd", 2);
		close(recover->fd_saved_in2);
		recover = recover->next;
	}
}

void		free_saver_fd(t_save_fd *recover)
{
	t_save_fd	*temp;

	temp = NULL;
	while(recover)
	{
		temp = recover;
		close(temp->fd_saved_in2);
		recover = recover->next;
		free(temp);
	}
}
