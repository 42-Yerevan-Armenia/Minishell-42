#include "minishell.h"

int	env(t_data *data, char **args)
{
	int	i;
	int	j;
	t_list_env *env;
	char	**tmp;

	i = 1;
	env = data->env;
	if (args == NULL)
		return (1);
	if (args[i] == NULL)
	{
		print_env(env->head);
		return (0);
	}
	return (0);
}