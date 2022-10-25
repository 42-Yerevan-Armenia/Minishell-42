/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:31:56 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/25 11:36:06 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// export test+t=5
// export a="'a'"

static char	**split_for_exp(char *str, char c, int *flag)
{
	char	**res;
	int		i;

	i = 0;
	res = malloc(sizeof(char *) * 3);
	fill_null((void *)&res, 3);
	while (str[i])
	{
		if (str[i] == c)
		{
			res[0] = ft_substr(str, 0, i);
			res[1] = ft_substr(str, i + 1, ft_strlen(str) - i);
			*flag = 1;
			return (res);
		}
		i++;
	}
	res[0] = ft_strdup(str);
	return (res);
}

static int	is_valid_args(char *args)
{
	int		i;
	int		j;
	char	*error;
	char	*identifier;

	i = 1;
	j = 0;
	if (args && args[0] == '=')
	{
		error = ft_strjoin_2("minishell: export: ", ft_strjoin_1(ft_strjoin_2("`", ft_strjoin(args, "'")), ": not a valid identifier"));
		ft_putendl_fd(error, 2);
		free(error);
		return (1);
	}
	while ((args[i] && args[i] != '+' && args[i] != '=')
			|| (args[i] == '+' && args[i] != '='))
	{
		if ((!ft_isalnum(args[i]) && args[i] != '_'
				&& args[i] != '$') || (ft_isdigit(args[i]) && j == 0))
		{
			error = ft_strjoin_2("minishell: export: ", ft_strjoin_1(ft_strjoin_2("`", ft_strjoin(args, "'")), ": not a valid identifier"));
			// error = ft_strjoin_1(ft_strjoin_2("`", ft_strjoin(args[i], "'")), ": not a valid identifier");
		// printf("d = %d\n", args[i][j]);
			ft_putendl_fd(error, 2);
			free(error);
		return (1);
		}
		// printf("c = %c\n", args[i][j]);
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
		tmp = split_for_exp(args[i], '=', &flag);
		// tmp = ft_split(args[i], '=');
		// printf("%s\n", tmp[0]);
		// printf("%s\n", tmp[1]);
		set_env(&exp, new_env(tmp[0], tmp[1], EXPORT));
		if (flag)
			set_env(&data->env, new_env(tmp[0], tmp[1], ENV));
		free_double((void *)&tmp);
		i++;
	}
	return (0);
}
