/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:31:56 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/28 11:38:21 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// export test+t=5
// export a="'a'"

static int	is_valid_args(char *args)
{
	int		i;
	char	*error;
	char	*identifier;

	i = 0;
	if (args && (args[0] == '=' || args[0] == '+'))
	{
		error = ft_strjoin_2("minishell: export: ", ft_strjoin_1(ft_strjoin_2("`", ft_strjoin(args, "'")), ": not a valid identifier"));
		ft_putendl_fd(error, 2);
		free(error);
		return (1);
	}
	while ((args[i] && args[i] != '+' && args[i] != '=')
			|| (args[i] == '+' && args[i + 1] != '='))
	{
		if ((!ft_isalnum(args[i]) && args[i] != '_'
				&& args[i] != '$') || (ft_isdigit(args[i]) && i == 0))
		{
			error = ft_strjoin_2("minishell: export: ", ft_strjoin_1(ft_strjoin_2("`", ft_strjoin(args, "'")), ": not a valid identifier"));
			// error = ft_strjoin_1(ft_strjoin_2("`", ft_strjoin(args[i], "'")), ": not a valid identifier");
		// printf("d = %d\n", args[i][j]);
			ft_putendl_fd(error, 2);
			free(error);
		return (1);
		}
		i++;
	}
	return (0);
}

int	export(t_data *data, char **args)
{
	int			i;
	int			j;
	int			flag;
	t_list_env	*exp;
	char		**tmp;

	if (args == NULL)
		return (1);
	i = 1;
	flag = 0;
	exp = data->env_exp;
	if (args[i] == NULL)
	{
		print_exp(exp->head);
		return (0);
	}
	while (args[i])
	{
		if (is_valid_args(args[i]))
			return (1);
		tmp = split_for_env(args[i], '=');
		// tmp = ft_split(args[i], '=');
		// printf("%s\n", tmp[0]);
		// printf("%s\n", tmp[1]);
		if (tmp[1])
			set_env(data, new_env(tmp[0], tmp[1], (ENV | EXPORT)));
		else
			set_env(data, new_env(tmp[0], tmp[1], EXPORT));
		// printf("tmp = %p\n", tmp);
		// printf("tmp[0] = %p\n", tmp[0]);
		// printf("tmp[1] = %p\n", tmp[1]);
		free_double((void *)&tmp);
		i++;
	}
	// data->envp =  env_cpy(data->env);
	return (0);
}
