/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:31:56 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/01 20:16:04 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_exp(t_env *head)
{
	while (head)
	{
		if (head->is_export == EXPORT || head->is_export == (ENV | EXPORT))
		{
			printf("declare -x %s", head->key);
			if (head->val)
				printf("=\"%s\"", head->val);
			printf("\n");
		}
		head = head->next;
	}
	return (0);
}

static int	is_valid_args_helper(char *args)
{
	char	*error;

	if (args && (args[0] == '=' || args[0] == '+'))
	{
		error = ft_strjoin_2("minishell: export: ",
				ft_strjoin_1(ft_strjoin_2("`", ft_strjoin(args, "'")),
					": not a valid identifier"));
		ft_putendl_fd(error, 2, 1);
		return (1);
	}
	return (0);
}

static int	is_valid_args(char *args)
{
	int		i;
	char	*error;

	i = 0;
	if (is_valid_args_helper(args) == 1)
		return (1);
	while ((args[i] && args[i] != '+' && args[i] != '=') || (args[i] == '+'
			&& args[i + 1] != '='))
	{
		if ((!ft_isalnum(args[i]) && args[i] != '_')
			|| (ft_isdigit(args[i]) && i == 0))
		{
			error = ft_strjoin_2("minishell: export: ", ft_strjoin_1(
						ft_strjoin_2("`", ft_strjoin(args, "'")),
						": not a valid identifier"));
			ft_putendl_fd(error, 2, 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	export(t_data *data, char **args)
{
	int			i;
	int			flag;
	char		**tmp;

	if (args == NULL)
		return (1);
	i = 1;
	flag = 0;
	if (args[i] == NULL && !print_exp(data->env_exp->head))
		return (0);
	while (args[i])
	{
		if (is_valid_args(args[i]) && ++i)
			continue ;
		tmp = split_for_env(args[i], '=');
		if (tmp[1])
			set_env(data, new_env(tmp[0], tmp[1], (ENV | EXPORT)));
		else
			set_env(data, new_env(tmp[0], tmp[1], EXPORT));
		free_double((void *)&tmp);
		i++;
	}
	data->envp = env_cpy(data, data->env);
	return (0);
}
