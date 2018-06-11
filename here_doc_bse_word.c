#include <fcntl.h>
#include <unistd.h>
#include "minishell.h"
//just be careful that temp_file is public. don't use this name for other use
static void	for_here_doc(int *temp_fd, t_line *doc_line)
{
	doc_line->here_end = 0;
	ft_bzero(doc_line->here_mark, MAX_BUF);
	*temp_fd = open(temp_file, O_CREAT | O_TRUNC | O_RDWR | O_APPEND, S_IWUSR | S_IRUSR);
	if (temp_fd < 0)
		ft_printf("temp file failed to be opened\n");
}

static void	write2_temp_file(char *word)
{
	int		i;
	int		j;
	int		temp_fd;
	t_line	doc;

	i = 0;
	j = 0;
	for_here_doc(&temp_fd, &doc);
	while (i < (int)ft_strlen(word))
			doc.here_mark[j++] = word[i++];
	while (!doc.here_end)
	{
		ft_bzero(doc.here, MAX_BUF);
		get_line("\nheredoc> ",(char *)doc.here, &doc);
		if (ft_strcmp((char *)doc.here_mark, (char *)doc.here))
		{
		if (write(temp_fd, doc.here, ft_strlen((char *)doc.here)) < 0)
			ft_printf("write into temp file failed\n");
			write(temp_fd, "\n",1);
		}
		else
			doc.here_end = 1;
	}
	if (close(temp_fd) == -1)
		ft_printf("close temp file failed\n");
}

void	my_here_doc_word(t_word *list)
{
	while (list && list->type != DLESS && !is_logic(list->type) && list->type != SEMI_DOT)
		list = list->next;
	if (list && list->type == DLESS)
	{
		write2_temp_file(list->next->word);
		list->type = LESS;
		list->next->type = FILES;
		ft_bzero(list->word, MAX_BUF);
		ft_strcpy(list->word, "<");
		ft_bzero(list->next->word, MAX_BUF);
		ft_strcpy(list->next->word, temp_file);
	}
}
