#include "minishell.h"

static int	print_env(t_env *head)
{
	while (head)
	{
		if (head->is_export == ENV || head->is_export == (ENV | EXPORT))
			printf("%s=%s\n", head->key, head->val);
		head = head->next;
	}
	printf("***************env\n");
	return (0);
}

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