#include <fcntl.h>
#include <unistd.h>
#include "minishell.h"

//test if there is "<<", no return -1, yes return where heredoc starts
//this func better replace by a func that is using the t_word list
int		inclu_heredoc(char *line)
{
	int		i;

	i = -1;
	while (++i < (int)ft_strlen(line) - 2)
	{
		if (line[i] == '<' && line[i + 1] == '<' && line[i + 2] != '<')
			return (i + 2);
	}
	return (-1);
}

static void	line_after_heredoc(char *line, int	after_mark, char *change)
{
	char	after[MAX_BUF];
	int		i;

	i = inclu_heredoc(line) - 2;
	ft_bzero(after, MAX_BUF);
	ft_strcpy(after, line + after_mark);
	ft_bzero(line + i, MAX_BUF - i);
	ft_strcat(line, " < ");
	ft_strcat(line, change);
	ft_strcat(line, after);
}

static void	for_here_doc(char *line, int *i, int *temp_fd, t_line *doc_line)
{
	*i = inclu_heredoc(line);
	doc_line->here_end = 0;
	ft_bzero(doc_line->here_mark, MAX_BUF);
	*temp_fd = open(temp_file, O_CREAT | O_TRUNC | O_RDWR | O_APPEND, S_IWUSR | S_IRUSR);
	if (temp_fd < 0)
		ft_printf("temp file failed to be opened\n");
	while (*i < (int)ft_strlen(line) && (line[*i] == ' ' || line[*i] == '\t'))
		*i = *i + 1;
}

void	my_here_doc(char *line)
{
	int		i;
	int		j;
	int		temp_fd;
	t_line	doc;

	j = 0;
	for_here_doc(line, &i, &temp_fd, &doc);
	while (i < (int)ft_strlen(line) && line[i] != ' ')
			doc.here_mark[j++] = line[i++];
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
	line_after_heredoc(line, i, temp_file);
}
static void	for_here_doc(char *line, int *i, int *temp_fd, t_line *doc_line)




static void	for_here_doc(char *line, int *i, int *temp_fd, t_line *doc_line)
{
	*i = inclu_heredoc(line);
	doc_line->here_end = 0;
	ft_bzero(doc_line->here_mark, MAX_BUF);
	*temp_fd = open(temp_file, O_CREAT | O_TRUNC | O_RDWR | O_APPEND, S_IWUSR | S_IRUSR);
	if (temp_fd < 0)
		ft_printf("temp file failed to be opened\n");
	while (*i < (int)ft_strlen(line) && (line[*i] == ' ' || line[*i] == '\t'))
		*i = *i + 1;
}

void	my_here_doc(char *line)
{
	int		i;
	int		j;
	int		temp_fd;
	t_line	doc;

	j = 0;
	for_here_doc(line, &i, &temp_fd, &doc);
	while (i < (int)ft_strlen(line) && line[i] != ' ')
			doc.here_mark[j++] = line[i++];
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
	line_after_heredoc(line, i, temp_file);
}
static void	for_here_doc(char *line, int *i, int *temp_fd, t_line *doc_line)

void	my_here_doc_word(t_word *list)
{
	while (list && list->type != DLESS && !is_logic(list->type) && list->type != SEMI_DOT)
		list = list->next;
	if (list && list->type == DLESS)
	{
	}

}
