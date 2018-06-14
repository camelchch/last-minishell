#include "minishell.h"

int		is_buildin(char *app)
{
	return (!strcmp(app, "echo") || !strcmp(app, "cd") ||\
			!strcmp(app, "setenv") || !strcmp(app, "unsetenv") ||\
			!strcmp(app, "env") || !strcmp(app, "exit"));
}
