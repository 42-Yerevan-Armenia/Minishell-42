/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:07:00 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/16 20:55:14 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	no_access(char *cmd, t_data *data)
{
	if (ft_strchr(cmd, '.'))
	{
		ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
		ft_strjoin(cmd, NO_PERM)), 2, FREE_ON);
		data->exit_status = 126;
	}
	else if (ft_strchr(cmd, '/'))
	{
		ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
		ft_strjoin(cmd, NO_DIR)), 2, FREE_ON);
		data->exit_status = 127;
	}
	else
	{
		ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
		ft_strjoin(cmd, NOT_FOUND)), 2, FREE_ON);
		data->exit_status = 127;
	}
}

int	cmd_errors_2(t_data *data, t_spl_pipe *tmp)
{
	if (access(*tmp->cmd, F_OK) != 0)
		no_dir(tmp, data);
	else if (access(*tmp->cmd, X_OK) != 0)
		no_perm(tmp, data);
	data->path = *tmp->cmd;
	return (1);
}

void	cmd_errors_1(t_data *data, t_spl_pipe *tmp)
{
	ft_putstr_fd(ft_strjoin(*tmp->cmd, FAR), 2, FREE_ON);
	ft_putstr_fd(ft_strjoin(*tmp->cmd, USAGE), 2, FREE_ON);
	data->exit_status = 2;
}

void	check_path(t_data *data, t_spl_pipe *tmp)
{
	if (ft_strchr(*tmp->cmd, '/') && access(*tmp->cmd, X_OK) == 0)
		data->path = *tmp->cmd;
	else if (data->path)
	{
		data->path = get_cmd(data->cmd_paths, *tmp->cmd);
		if (data->path == NULL)
			if (!(access(*tmp->cmd, X_OK) == 0))
				no_access(*tmp->cmd, data);
	}
	else if (access(*tmp->cmd, X_OK) != 0)
		not_found(tmp, data);
	else
		no_dir(tmp, data);
}

int	cmd_errors(t_data *data, t_spl_pipe *tmp)
{
	if (*tmp->cmd[0] == 0)
		not_found(tmp, data);
	else if (tmp->cmd[0][0] == '.' && !tmp->cmd[0][1])
		cmd_errors_1(data, tmp);
	else if (opendir(*tmp->cmd) && ft_strchr(*(tmp->cmd), '/'))
		is_dir(tmp, data);
	else if (tmp->cmd[0][0] == '/' || (tmp->cmd[0][1] == '.' \
		&& tmp->cmd[0][1] == '/') || (tmp->cmd[0][0] == '.' \
		&& tmp->cmd[0][1] == '/') || (tmp->cmd[0][0] == '.' \
		&& tmp->cmd[0][1] == '.' && tmp->cmd[0][2] == '/')
		|| (!data->path && !ft_strchr(*tmp->cmd, '/')))
	{
		cmd_errors_2(data, tmp);
		data->path = ft_strdup(*tmp->cmd);
		return (1);
	}
	else if (tmp->cmd[0][0] == '.')
		not_found(tmp, data);
	else
	{
		check_path(data, tmp);
		return (1);
	}
	return (0);
}
