/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 21:12:42 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/26 13:35:02 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	tmp = 0;
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		if (access(command, X_OK) == 0)
			return (command);
		paths++;
	}
	return (NULL);
}

int	close_fds(int (*fds)[2], int psize)
{
	int	i;

	i = -1;
	while (++i < psize - 1)
	{
		if (close(fds[i][1]) == -1 || close(fds[i][0]) == -1)
		{
			ft_perror("🔻minishell: close");
			return (START_RD_LN);
		}
	}
	free(fds);
	return (0);
}

int	open_pipes(t_spl_pipe *tmp, int i, int (*fds)[2], int psize)
{
	if (i == 0)
	{
		if (dup2(fds[0][1], tmp->fd_out) == -1)
		{
			ft_perror("🔻minishell: dup2");
			return (START_RD_LN);
		}
	}
	else if (i == psize - 1)
	{
		if (dup2(fds[i - 1][0], tmp->fd_in) == -1)
		{
			ft_perror("🔻minishell: dup2");
			return (START_RD_LN);
		}
	}
	else
	{
		if (dup2(fds[i - 1][0], tmp->fd_in) == -1 \
		|| dup2(fds[i][1], tmp->fd_out) == -1)
			return (START_RD_LN);
	}
	if (close_fds(fds, psize) == START_RD_LN)
		return (START_RD_LN);
	return (0);
}

void	do_cmd(t_data *data, t_spl_pipe *tmp)
{
	int	i;

	i = 0;
	if (*tmp->cmd[0] != '\0' && search_builtin(tmp->cmd[0], data->builtins))
		run_builtins(data, tmp);
	else
	{
		if (cmd_errors(data, tmp) == 1)
			execve(data->path, tmp->cmd, data->envp);
	}
	exit(data->exit_status);
}
