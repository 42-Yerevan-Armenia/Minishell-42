/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 21:12:42 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/07 09:23:52 by vaghazar         ###   ########.fr       */
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

void	close_fds(int (*fds)[2], int psize)
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
	close_fds(fds, psize);
}

void	do_cmd(t_data *data, t_spl_pipe *tmp, int psize)
{
	int	i;

	i = 0;
	if (*tmp->cmd[0] != '\0' && search_builtin(tmp->cmd[0], data->builtins))
		run_builtins(data, tmp);
	else
	{
		cmd_errors(data, tmp);
		if (!data->path)
		{
			free(data->path);
			ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
			ft_strjoin(*tmp->cmd, NOT_FOUND)), 2, FREE_ON);
			data->exit_status = 127;
		}
		execve(data->path, tmp->cmd, data->envp);
	}
	exit(data->exit_status);
}
