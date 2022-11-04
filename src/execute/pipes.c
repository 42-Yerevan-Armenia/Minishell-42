/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 21:12:42 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/01 21:12:44 by arakhurs         ###   ########.fr       */
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

void	pipe_redirections(t_spl_pipe *tmp)
{
	dup2(tmp->fd_out, 1);
	dup2(tmp->fd_in, 0);
}

void	close_fds(int (*fds)[2], t_spl_pipe *tmp, int psize)
{
	int	i;

	i = -1;
	while (++i < psize - 1)
	{
		if (close(fds[i][1]) == -1)
			perror("CLOSE FAILED");
		if (close(fds[i][0]) == -1)
			perror("CLOSE FAILED");
	}
	free(fds);
}

void	open_pipes(t_spl_pipe *tmp, int i, int (*fds)[2], int psize)
{
	if (i == 0)
	{
		if (dup2(fds[0][1], tmp->fd_out) < 0)
			exit(1);
	}
	else if (i == psize - 1)
	{
		if (dup2(fds[i - 1][0], tmp->fd_in) < 0)
			exit(1);
	}
	else
	{
		dup2(fds[i - 1][0], tmp->fd_in);
		dup2(fds[i][1], tmp->fd_out);
	}
	close_fds(fds, tmp, psize);
}

void	do_cmd(t_data *data, t_spl_pipe *tmp, int psize)
{
	int	i;

	i = 0;
	if (ft_strnstr(BUILTINS, tmp->cmd[0], 35))
		run_builtins(data, tmp);
	else
	{
		if (access(*tmp->cmd, X_OK) == 0 && ft_strcmp(*tmp->cmd, "minishell"))
			data->path = *tmp->cmd;
		else if (ft_strchr(*tmp->cmd, '/'))
			printf(NOT_FOUND, *tmp->cmd);
		else
			data->path = get_cmd(data->cmd_paths, *tmp->cmd);
		if (!data->path)
			free(data->path);
		execve(data->path, tmp->cmd, data->envp);
		printf(NOT_FOUND, *tmp->cmd);
	}
	exit(1);
}
