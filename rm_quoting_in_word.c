#include "minishell.h"

static void	init_vari_for(t_helper *help, char *cp, char *vari, char *word)
{
	open_dquote = -1;
	open_squote = -1;
	help->i = -1;
	help->k = 0;
	help->index = 0;
	ft_bzero(cp, MAX_BUF);
	ft_bzero(vari, MAX_BUF);
	ft_strcpy(cp, word);
	ft_bzero(word, MAX_BUF);
}

static void	case_dquote(t_helper *help, char *cp, char *word)
{
	if (open_squote < 0)
	{
		if (!dslash_before(cp, help->i))
			word[help->index - 1] = '"';
		else
			open_dquote = -open_dquote;
	}
	else
		word[help->index++] = '"';
}

static void	case_squote(t_helper *help, char *word)
{
	if (open_dquote < 0)
		open_squote = -open_squote;
	else
		word[help->index++] = '\'';
}

static void	other_case(t_helper *help, char *cp, char *word)
{
	if (!(cp[help->i] == '\\' && !dslash_before(cp, help->i) && open_squote < 0))
		word[help->index++] = cp[help->i];
	else if (open_dquote < 0 && open_squote < 0 && help->i - 1 >= 0 && \
			cp[help->i - 1] == '\\' && dslash_before(cp, help->i - 1))
		word[help->index - 1] = cp[help->i];
}

int		remove_quoting_word(char *word, char **env)
{
	t_helper	help;
	char	cp[MAX_BUF];
	char	vari[MAX_BUF];
	char	*vari_value;

	init_vari_for(&help, cp, vari, word);
	while (cp[++(help.i)])
	{
		if (open_squote < 0 && cp[help.i] == '$')
		{
			dollor_sign(&help, cp, vari);
			vari_value = ft_getenv(env, vari);
			if (!vari_value)
				return(return_message("Undefined variable.\n", 1, 2));
			change_part_str(cp, help.i, help.j - 1, vari_value);
		}
		if (cp[help.i] == '"')
			case_dquote(&help, cp, word);
		else if (cp[help.i] == '\'')
			case_squote(&help, word);
		else
			other_case(&help, cp, word);
	}
	return (0);
}
