/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:09:20 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/18 16:35:01 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_args(char *args, t_data *data)
{
	int		i;
	char	*error;

	i = 0;
	while (args)
	{
		if ((args[0] == '\0' || (!ft_isalnum(args[i])
					&& args[i] != '_') || (ft_isdigit(args[i])
					&& i == 0)))
		{
			error = ft_strjoin_2("🔻minishell: unset: ", 
					ft_strjoin_1(ft_strjoin_2
						("`", ft_strjoin(args, "'")),
						": not a valid identifier ❌"));
			ft_putendl_fd(error, 2, FREE_ON);
			data->exit_status = 1;
			return (1);
		}
		i++;
		if (args[i] == '\0')
			break ;
	}
	return (0);
}

int	unset(t_data *data, char **args)
{
	int	i;
	int	flag;

	if (args == NULL)
		return (1);
	i = 1;
	flag = 0;
	data->exit_status = 0;
	while (args[i])
	{
		if (is_valid_args(args[i], data) && ++i)
			continue ;
		del_env_node(data->env, args[i], ENV);
		del_env_node(data->env_exp, args[i], EXPORT);
		i++;
	}
	data->envp = env_cpy(data, data->env);
	return (data->exit_status);
}
