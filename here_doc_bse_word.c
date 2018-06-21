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
		ft_putendl_fd("temp file failed to be opened", 2);
}
/*
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
	i = 1;
	while (!doc.here_end)
	{
		ft_bzero(doc.here, MAX_BUF);
		i == 0 ? ft_printf("\n") : (void)i;
		i = 0;
		get_line("heredoc> ",(char *)doc.here, &doc);
		if (ft_strcmp((char *)doc.here_mark, (char *)doc.here))
		{
		if (write(temp_fd, doc.here, ft_strlen((char *)doc.here)) < 0)
			ft_putendl_fd("write into temp file failed", 2);
			write(temp_fd, "\n",1);
		}
		else
			doc.here_end = 1;
	}
	ft_printf("\n");
	if (close(temp_fd) == -1)
		ft_putendl_fd("close temp file failed", 2);
}
*/

static void	write2_temp_file(char *word)
{
	int		i;
	int		j;
	int		temp_fd;
	t_line	doc;

	i = 0;
	j = 0;
	for_here_doc(&temp_fd, &doc);
//	while (i < (int)ft_strlen(word))
//			doc.here_mark[j++] = word[i++];
	i = 1;
	while (!doc.here_end)
	{
		ft_bzero(doc.here, MAX_BUF);
		i == 0 ? ft_printf("\n") : (void)i;
		i = 0;
		get_line("heredoc> ",(char *)doc.here, &doc);
		if (ft_strcmp(word, (char *)doc.here))
		{
		if (write(temp_fd, doc.here, ft_strlen((char *)doc.here)) < 0)
			ft_putendl_fd("write into temp file failed", 2);
			write(temp_fd, "\n",1);
		}
		else
			doc.here_end = 1;
	}
	ft_printf("\n");
	if (close(temp_fd) == -1)
		ft_putendl_fd("close temp file failed", 2);
}

void	my_here_doc_word(t_word *list)
{
	while (list && !is_logic(list->type) && list->type != SEMI_DOT && list->type != PIPE)
	{
	if (list->type == DLESS)
	{
		write2_temp_file(list->next->word);
		list->type = LESS;
		list->next->type = FILES;
		ft_bzero(list->word, MAX_BUF);
		ft_strcpy(list->word, "<");
		ft_bzero(list->next->word, MAX_BUF);
		ft_strcpy(list->next->word, temp_file);
	}
		list = list->next;
	}
}
