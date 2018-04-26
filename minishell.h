/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 12:26:55 by saxiao            #+#    #+#             */
/*   Updated: 2018/04/26 14:36:45 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft/libft.h"

#ifndef MINISHELL_H
#define MINISHELL_H

typedef struct s_table
{
	char			name[NAME_MAX + 1];
	char			path[PATH_MAX + 1];
	struct s_table	*next;
}					t_table;

typedef struct	s_shtable
{
	t_table		*sh_ta;
}				t_sh;

char		*get_autoline(t_sh *table);
char		**path(char **env);
int			calcu_index(char *name);
int			is_buildin(char *app);
char		**unset_env(char **paras, char **env);
void		do_build(char **paras, char ***env, t_sh *table);
void		put_env(char **env, char **paras, t_sh *table);
char		*ft_getenv(char **env, char *name);
void		init_shtable(t_sh *table, char **path);
void		shell(int ac, char **av, char **env, t_sh *table);
void		child_pro(char **paras, char **env, t_sh *table);
void		each_cmdline(char *cmdline, char **env, t_sh *table);
void		pipes(char *cmdline, int nb_pipe, char **env, t_sh *table);
int			no_pipe(char *cmdline);
void		signal_quith(int sign);
void		put_strstr(char **str);
#endif
