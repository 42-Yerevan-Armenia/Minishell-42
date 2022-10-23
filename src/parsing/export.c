/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:31:56 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/22 16:32:04 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			res[1] = ft_substr(str, i + 1, ft_strlen(str - i));
			*flag = 1;
			return (res);
		}
		i++;
	}
	// printf("%d\n", i);
	res[0] = ft_strdup(str);
	// printf("res = %s\n", res[1]);
	return (res);
}

static int	is_valid_args(t_data *data, char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j] && args[i][j] != '+' && args[i][j] != '=')
		{
			if ((!ft_isalnum(args[i][j]) && args[i][j] != '_'
					&& args[i][j] != '$') || (ft_isdigit(args[i][j]) && j == 0))
			{
				// errno = ft_strjoin(ft_strjoin_all(args + 1),
				// ": not a valid identifier");
				ft_perror("minishell: export: ");
				return (1);
			}
			j++;
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

	if (is_valid_args(data, args))
		return (1);
	i = 1;
	flag = 0;
	exp = data->env_exp;
	if (args == NULL)
		return (1);
	if (args[i] == NULL)
	{
		print_exp(exp->head);
		return (0);
	}
	while (args[i])
	{
		tmp = split_for_exp(args[i], '=', &flag);
		// tmp = ft_split(args[i], '=');
		// printf("%s\n", tmp[0]);
		// printf("%d\n", tmp[1]);
		set_env(&exp, new_env(tmp[0], tmp[1], EXPORT));
		if (flag)
			set_env(&data->env, new_env(tmp[0], tmp[1], ENV));
		free_double(&tmp);
		i++;
	}
	return (0);
}
