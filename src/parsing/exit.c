/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:08:48 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/19 19:58:34 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_is_valid_num(char **str)
{
	int		i;
	char	*s1;
	char	*s2;

	i = 0;
	while (str[++i])
		if (ft_strlen(str[i]) == 1 && (str[i][0] == '+' || str[i][0] == '-'))
			ft_free(str);
	i = -1;
	while (str[++i])
	{	
		s1 = numstr(str[i]);
		s2 = ft_itoa(ft_atoi(str[i]));
		if (ft_strcmp(s1, s2))
		{
			if (ft_strcmp(s2, "0"))
				break ;
			free_arr(&s1);
			free_arr(&s2);
			return (1);
		}
		free_arr(&s1);
		free_arr(&s2);
	}
	return (0);
}

int	ex(t_data *data, char **args, t_spl_pipe *cur)
{
	if (data->cmd_line->tail && ft_strcmp(*args, "exit"))
		return (1);
	if (!args[1] && data->cmd_line->size > 1)
		exit(0);
	else if (args[1] && str_is_valid_num(&args[1]))
	{
		ft_putstr_fd("exit\n", cur->fd_out, FREE_OFF);
		ft_putstr_fd("🔻minishell> : exit: ", 2, FREE_OFF);
		ft_putstr_fd(args[1], 2, FREE_OFF);
		ft_putstr_fd(": numeric argument required\n", 2, FREE_OFF);
		exit (data->exit_status = 255);
	}
	return (0);
}

void	ft_exit(t_data *data, char **args, t_spl_pipe *cur)
{
	ex(data, args, cur);
	if (args && args[2])
	{
		ft_putstr_fd("exit\n", cur->fd_out, FREE_OFF);
		ft_putstr_fd(EXIT_ARG, 2, FREE_OFF);
		data->exit_status = 1;
		return ;
	}
	else if (args && ft_atoi(args[1]) >= 255)
	{
		ft_putstr_fd("exit\n", cur->fd_out, FREE_OFF);
		data->exit_status = ft_atoi(args[1]) % 256;
	}
	else if (args && ft_atoi(args[1]) < 0)
	{
		ft_putstr_fd("exit\n", cur->fd_out, FREE_OFF);
		data->exit_status = ft_atoi(args[1]) - 256;
	}
	else
	{
		ft_putstr_fd("exit\n", cur->fd_out, FREE_OFF);
		data->exit_status = ft_atoi(args[1]);
	}
	free_all (data);
	exit(data->exit_status);
}
