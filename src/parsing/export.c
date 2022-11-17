/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:31:56 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/17 20:35:55 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_exp(t_env *head, t_spl_pipe *node)
{
	while (head)
	{
		if (head->is_export == EXPORT || head->is_export == (ENV | EXPORT))
		{
			ft_putstr_fd("declare -x", node->fd_out, FREE_OFF);
			ft_putstr_fd(head->key, node->fd_out, FREE_OFF);
			if (head->val)
				ft_putstr_fd(head->val, node->fd_out, FREE_OFF);
			ft_putstr_fd("\n", node->fd_out, FREE_OFF);
		}
		head = head->next;
	}
	return (0);
}

static int	is_valid_args_helper(char *args, t_data *data)
{
	char	*error;

	if (args && (args[0] == '=' || args[0] == '+'))
	{
		error = ft_strjoin_2("minishell: export: ",
				ft_strjoin_1(ft_strjoin_2("`", ft_strjoin(args, "'")),
					": not a valid identifier"));
		ft_putendl_fd(error, 2, FREE_ON);
		data->exit_status = 1;
		return (1);
	}
	return (0);
}

static int	is_valid_args(char *args, t_data *data)
{
	int		i;
	char	*error;

	i = 0;
	if (is_valid_args_helper(args, data) == 1)
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
			ft_putendl_fd(error, 2, FREE_ON);
			data->exit_status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	export(t_data *data, char **args, t_spl_pipe *node)
{
	int			i;
	int			flag;
	char		**tmp;

	if (args == NULL)
		return (1);
	i = 1;
	flag = 0;
	if (args[i] == NULL && !print_exp(data->env_exp->head, node))
		return (0);
	while (args[i])
	{
		if (is_valid_args(args[i], data) && ++i)
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
	return (data->exit_status);
}
