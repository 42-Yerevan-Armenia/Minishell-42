/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:08:48 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/01 21:10:17 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_is_valid_num(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] || !ft_isdigit(str[i - 1]) || i > 19)
		return (0);
	return (1);
}

int	ft_exit(t_data *data, char **args)
{
	if (data->cmd_line->tail && ft_strcmp(*args, "exit"))
		return (1);
	else if (!args[1])
	{
		ft_putstr_fd("exit\n", 1, FREE_OFF);
		exit(data->exit_status = 127);
	}
	if (args[1] && !str_is_valid_num(args[1]))
	{
		ft_putstr_fd("🔻minishell> : exit: ", 2, FREE_OFF);
		ft_putstr_fd(args[1], 2, FREE_OFF);
		ft_putstr_fd(": numeric argument required\n", 2, FREE_OFF);
		data->exit_status = 255;
	}
	else if (args && args[2])
	{
		ft_putstr_fd(EXIT_ARG, 2, FREE_OFF);
		data->exit_status = 1;
	}
	else if (args && ft_atoi(args[1]) >= 255)
		data->exit_status = ft_atoi(args[1]) % 256;
	else if (args && ft_atoi(args[1]) <= 0)
		data->exit_status = ft_atoi(args[1]) - 256;
	else
		data->exit_status = 0;
	exit(data->exit_status);
	return (0);
}
