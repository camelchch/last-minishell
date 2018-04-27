#include "minishell.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>

char	*path_in_sh(char *app, t_sh *table)
{
	int			index;
	t_table		*cp;

	index = calcu_index(app);
	cp = table[index].sh_ta;
	while (cp)
	{
		if (!strcmp(app, cp->name))
			return (cp->path);
		cp = cp->next;
	}
	return (NULL);
}

/*void	put_choice(t_sh *table, char *cmd)
  {
  ft_printf("huhu\n");
  (void)table;
  (void)cmd;
  }

  char	*get_autoline(t_sh *table)
  {
  char	buf[1];
  char	*cmd;

  cmd = NULL;
  while (read(1, buf, 1) > 0 && *buf != '\n' && (*buf == ' ' || *buf == '\t'))
  ;;

  while (*buf != '\t' && *buf != ' ' && *buf != '\n')
  {
  cmd = ft_strjoin(cmd, buf);
  read(1, buf, 1);
  }
  ft_printf("00000000000000\n");
  if (*buf == '\t')
  {
  put_choice(table, cmd);
  ft_printf("just tring");
  }
  return (NULL);
  }
  */

void	signal_inh(int sign)
{
	if (sign == SIGINT)
		ft_printf("\n$> ");
	if (sign == SIGQUIT)
		exit(0);
}

void	signal_quith(int sign)
{
	(void)sign;
		kill(SIGQUIT, 0);
}

void	shell(int ac, char **av, char **env, t_sh *table)
{
	char	*line;
//	char	**paras;
	//	char	*path;
	char	**cmd;
//	pid_t	pid_no;

	(void)ac;
	(void)av;

	line = NULL;
	signal(SIGINT, signal_inh);
//	signal(SIGQUIT, signal_quith);
	while(1)
	{
		ft_printf("$> ");
		//		get_autoline(table);
		if (get_next_line(1, &line) > 0)
		{
		cmd = ft_strsplit(line, ';');
		while (*cmd)
		{
			//each_cmdline(*cmd, env, table);
		//	ft_printf("in shell cmd=%s\n",*cmd);
			pipes(*cmd, no_pipe(*cmd), &env, table);
			cmd++;
		}
		}
	}
}

void	each_cmdline(char *cmdline, char **env, t_sh *table)
{
	char	**paras;
	pid_t	pid_no;

	paras = ft_strsplit(cmdline, ' ');
	if (is_buildin(*paras))
		do_build(paras, &env, table);
	else
	{
		pid_no = fork();
		if (pid_no < 0)
			ft_printf("fork failled");
		else if (pid_no == 0)
			child_pro(paras, env, table);
		else
		{
			if (wait(NULL) == -1)
				ft_printf("wait failled\n");
		}
	}
}

int		is_minishell(char *program)
{
	int		i;

	if (ft_strstr(program, "/"))
	{
		i = ft_strlen(program) - 1;
		while (i >= 0 && program[i] != '/')
			i--;
		program = program + i + 1;
	}
	if (ft_strcmp(program, "minishell"))
		return (0);
	return (1);
}

void	update_shlvl(char ***env)
{
	char	**cp;
	int		level;
	char	*shlvl[4];
	char	*lv;

	cp = *env;
	level = 1;
	while (*cp && !(!ft_strncmp(*cp, "SHLVL", 5)))
			cp++;
	if (*cp)
		level = ft_atoi(*cp + 6) + 1;
	lv = ft_itoa(level);
	shlvl[0] = "no real meaning here";
	shlvl[1] = "SHLVL";
	shlvl[2] = lv;
	shlvl[3] = NULL;
	set_env(shlvl, env);
}

void	update_lastapp(char *lastcmd, char ***env)
{
	char *lastapp[4];

	lastapp[0] = "no real meaning here";
	lastapp[1] = "_";
	lastapp[2] = lastcmd;
	lastapp[3] = NULL;
	set_env(lastapp, env);
}

void	child_pro(char **paras, char **env, t_sh *table)
{
	char	*path;

	if (!access(*paras, F_OK))
	{
		update_lastapp(*paras, &env);
		execve(*paras, paras, env);
		ft_printf("permission denied for this program: %s\n", *paras);
		exit(0) ;
	}
	path = path_in_sh(*paras, table);
	if (!path)
	{
		ft_printf("%s : there is no such program\n", *paras);
		exit(0) ;
	}
	else
	{
		update_lastapp(path, &env);
		execve(path, paras, env);
		ft_printf("permission denied for this program %s\n", *paras);
		exit(0) ;
	}
}
