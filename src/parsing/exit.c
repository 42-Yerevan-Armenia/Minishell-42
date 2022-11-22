/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:08:48 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/22 20:25:38 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_is_valid_num(char *str)
{
	int		i;
	int		j;
	int		flag;
	char	*tmp;

	i = 0;
	flag = 0;
	tmp = ft_strtrim(str, SPACES);
	if (((tmp[i] == '+' && ++flag) || (tmp[i] == '-' && --flag)) && ++i)
		while (tmp[i] && tmp[i + 1] && tmp[i] == '0')
			i++;
	j = i;
	while (tmp[i])
	{
		if (!ft_isdigit(tmp[i]))
			return (1);
		i++;
	}
	if ((i - j) > 19)
		return (1);
	if ((i - j) <= 19)
		return (0);
	if (flag == 1 || flag == 0)
		if (ft_strcmp(tmp + j, L_MAX) > 0)
			return (1);
	if (flag == -1)
		if (ft_strcmp(tmp + j, L_MIN) > 0)
			return (1);
	return (0);
}

void	ft_exit(t_data *data, char **args, t_spl_pipe *cur)
{
	if (!args[1])
		exit (ft_atoi(get_val(data->env->head, "?", FORME)));
	else if (args[1] && str_is_valid_num(args[1]))
	{
		ft_putstr_fd("exit\n", cur->fd_out, FREE_OFF);
		ft_putstr_fd("🔻minishell> : exit: ", 2, FREE_OFF);
		ft_putstr_fd(args[1], 2, FREE_OFF);
		ft_putstr_fd(": numeric argument required\n", 2, FREE_OFF);
		exit (data->exit_status = 255);
	}
	if (args && args[2])
	{
		ft_putstr_fd("exit\n", cur->fd_out, FREE_OFF);
		ft_putstr_fd(EXIT_ARG, 2, FREE_OFF);
		data->exit_status = 1;
		return ;
	}
	else
	{
		ft_putstr_fd("exit\n", cur->fd_out, FREE_OFF);
		data->exit_status = ft_atoi(args[1]);
	}
	free_all(data);
	exit(data->exit_status);
}
