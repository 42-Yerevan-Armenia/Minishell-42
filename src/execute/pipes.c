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

int	cmd_errors_1(t_data *data, t_spl_pipe *tmp)
{
	if (*tmp->cmd[0] == 0)
		ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
		ft_strjoin(*tmp->cmd, NOT_FOUND)), 2, FREE_ON);
	else if (tmp->cmd[0][0] == '.' && !tmp->cmd[0][1])
	{
		ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
		ft_strjoin(*tmp->cmd, FAR)), 2, FREE_ON);
		ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
		ft_strjoin(*tmp->cmd, USAGE)), 2, FREE_ON);
		data->exit_status = 2;
	}
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

void	do_cmd(t_data *data, t_spl_pipe *tmp, int psize)
{
	int	i;

	i = 0;
	if (*tmp->cmd[0] != '\0' && ft_strnstr(BUILTINS, tmp->cmd[0], 35))
		run_builtins(data, tmp);
	else
	{
		cmd_errors_1(data, tmp);
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
