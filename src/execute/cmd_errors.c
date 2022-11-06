/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:07:00 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/06 18:07:02 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_errors_2(t_data *data, t_spl_pipe *tmp)
{
	if (access(*tmp->cmd, F_OK) != 0)
		ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
		ft_strjoin(*tmp->cmd, NO_DIR)), 2, FREE_ON);
	else if (access(*tmp->cmd, X_OK) != 0)
	{
		ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
		ft_strjoin(*tmp->cmd, NO_PERM)), 2, FREE_ON);
		data->exit_status = 126;
	}
	data->path = *tmp->cmd;
	return (1);
}

void	cmd_errors_1(t_data *data, t_spl_pipe *tmp)
{
	ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
	ft_strjoin(*tmp->cmd, FAR)), 2, FREE_ON);
	ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
	ft_strjoin(*tmp->cmd, USAGE)), 2, FREE_ON);
	data->exit_status = 2;
}

int	cmd_errors(t_data *data, t_spl_pipe *tmp)
{
	if (*tmp->cmd[0] == 0)
		ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
		ft_strjoin(*tmp->cmd, NOT_FOUND)), 2, FREE_ON);
	else if (tmp->cmd[0][0] == '.' && !tmp->cmd[0][1])
		cmd_errors_1(data, tmp);
	else if (opendir(*tmp->cmd) && ft_strchr(*(tmp->cmd), '/'))
	{
		ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
		ft_strjoin(*tmp->cmd, IS_DIR)), 2, FREE_ON);
		data->exit_status = 126;
	}
	else if (tmp->cmd[0][0] == '/' || (tmp->cmd[0][1] == '.' \
		&& tmp->cmd[0][1] == '/') || (tmp->cmd[0][0] == '.' \
		&& tmp->cmd[0][1] == '/') || (tmp->cmd[0][0] == '.' \
		&& tmp->cmd[0][1] == '.' && tmp->cmd[0][2] == '/'))
		cmd_errors_2(data, tmp);
	else if (tmp->cmd[0][0] == '.')
		ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
		ft_strjoin(*tmp->cmd, NOT_FOUND)), 2, FREE_ON);
	else
	{
		data->path = get_cmd(data->cmd_paths, *tmp->cmd);
		return (1);
	}
	return (0);
}
