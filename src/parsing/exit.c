/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 01:08:48 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/26 15:45:38 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_is_valid_num_helper(int i, int j, char *tmp, int flag)
{
	if ((i - j) > 19)
		return (1);
	if ((i - j) < 19)
		return (0);
	if (flag == 1 || flag == 0)
		if (ft_strcmp(tmp + j, L_MAX) > 0)
			return (1);
	if (flag == -1)
		if (ft_strcmp(tmp + j, L_MIN) > 0)
			return (1);
	return (0);
}

int	str_is_valid_num(char *str)
{
	int		i;
	int		j;
	int		flag;
	char	*tmp;

	i = 0;
	flag = 0;
	tmp = ft_strtrim(str, SPACES);
	if ((((tmp[i] == '+' && ++flag) || (tmp[i] == '-' && --flag))
			&& ++i) || tmp[i])
		while (tmp[i] && tmp[i + 1] && tmp[i] == '0')
			i++;
	j = i;
	if (str && tmp[i] == '\0' && !free_arr(&tmp))
		return (1);
	while (tmp[i])
	{
		if (!ft_isdigit(tmp[i]) && !free_arr(&tmp))
			return (1);
		i++;
	}
	if ((str_is_valid_num_helper(i, j, tmp, flag) != 0 && !free_arr(&tmp)))
		return (1);
	return (free_arr(&tmp));
}

void	ft_exit(t_data *data, char **args, t_spl_pipe *cur)
{
	if (!args[1] && data->cmd_line->size > 1)
		exit (0);
	else if (!args[1])
		data->exit_status = ft_atoi(get_val(data->env->head, "?", FORME));
	else if (args[1] && str_is_valid_num(args[1]))
	{
		ft_putstr_fd("🔻minishell> : exit: ", 2, FREE_OFF);
		ft_putstr_fd(args[1], 2, FREE_OFF);
		ft_putstr_fd(": numeric argument required\n", 2, FREE_OFF);
		data->exit_status = 255;
	}
	else if (args && args[1] && args[2])
	{
		if (data->cmd_line->size == 1)
			ft_putstr_fd("exit\n", cur->fd_out, FREE_OFF);
		ft_putstr_fd(EXIT_ARG, 2, FREE_OFF);
		data->exit_status = 1;
		return ;
	}
	else
		data->exit_status = ft_atoi(args[1]);
	if (data->cmd_line->size == 1)
		ft_putstr_fd("exit\n", cur->fd_out, FREE_OFF);
	free_all(data);
	exit(data->exit_status);
}
