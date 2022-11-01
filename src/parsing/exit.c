/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:08:48 by arakhurs          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/10/31 13:39:08 by arakhurs         ###   ########.fr       */
=======
/*   Updated: 2022/11/01 13:57:37 by vaghazar         ###   ########.fr       */
>>>>>>> 2986292a5d5b862f2e8953458a064a6855f124aa
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
	int	exit_status;

<<<<<<< HEAD
	if (data->cmd_line->tail && ft_strcmp(*args, "exit"))
=======
	if (data->cmd_line->tail)
>>>>>>> 2986292a5d5b862f2e8953458a064a6855f124aa
		return (1);
	else
		ft_putstr_fd("exit\n", 1, FREE_OFF);
	if (args && data->exit_status >= 2 && !str_is_valid_num(args[1]))
	{
		ft_putstr_fd("🔻minishell> : exit: ", 2, FREE_OFF);
		ft_putstr_fd(args[1], 2, FREE_OFF);
		ft_putstr_fd(": numeric argument required\n", 2, FREE_OFF);
		exit_status = 255;
	}
	else if (args && data->exit_status > 2)
	{
		ft_putstr_fd("🔻minishell> : exit: too many arguments\n", 2, FREE_OFF);
		exit_status = 1;
	}
	else if (args && data->exit_status == 2)
		exit_status = ft_atoi(args[1]) % 256;
	else
		exit_status = 0;
	free_envp(&data->env);
	exit(1);
	return (0);
}
