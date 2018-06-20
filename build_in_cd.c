#include <unistd.h>
#include "minishell.h"

static void	init_tempwd(char **tempwd, int ct, char ***paras, char *path)
{
	//char	*temp;
	(void)ct;
	(void)paras;

	tempwd[0] = "no real meaning here";
	tempwd[1] = "OLDPWD";
	tempwd[2] = getcwd(path, PATH_MAX + 1);
	tempwd[3] = NULL;
	/*	if (ct == 2)
		{
		temp = **paras;
		(*paras)++;
		free(temp);
		}
		*/
}

static void		oldpwd_home(char **cp, char ***env, int ct)
{
	(void)ct;
	if (ct == 1 || ft_strcmp(*cp, "~"))
	{
		*cp = ft_getenv(*env, "HOME");
		if (!*cp)
			ft_putendl_fd("enviroment HOME is not set", 2);
	}
	else
	{
		*cp = ft_getenv(*env, "OLDPWD");
		if (!*cp)
			ft_putendl_fd("enviroment OLDPWD  is not set", 2);
	}
}

static void	for_cd(char *paras, char ***env, char **tempwd, char *path)
{
	if (!chdir(paras))
	{
		set_env(tempwd, env);
		tempwd[1] = "PWD";
		tempwd[2] = getcwd(path, PATH_MAX);
		set_env(tempwd, env);
	}
	else
	{
		if (access(paras, F_OK))
			put2_str_fd(paras, " :no such file or directory\n", 2);
		else if (access(paras, X_OK))
			ft_putendl_fd("permission denied", 2);
	}
}

int		cd(char **paras, char ***env)
{
	int		ct;
	char	*tempwd[4];
	char	path[PATH_MAX + 1];
	char	*cp;

	ct = nb_str(paras);
	if (ct == 1)
		cp = paras[0];
	else
		cp = paras[1];
	if (ct != 1 && ct != 2)
		return(return_message("Too many arguments--usage : cd path\n", 1, 2));
	else
	{
		init_tempwd(tempwd, ct, &paras, path);
		if (ct == 1 || (ct == 2 && (!ft_strcmp(*(paras + 1), "~") || !ft_strcmp(*(paras + 1), "-"))))
			oldpwd_home(&cp, env, ct);
		for_cd(cp, env, tempwd, path);
		return (0);
	}
}
