/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:09:43 by arakhurs          #+#    #+#             */
/*   Updated: 2022/10/26 21:22:54 by arakhurs         ###   ########.fr       */
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
		if (access(command, F_OK) == 0)
			return (command);
		free(command);
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
		close(fds[i][1]);
		close(fds[i][0]);
	}
	free(fds);
}

void	open_pipes(int i, int (*fds)[2], int psize)
{
	if (i == 0)
	{
		if (dup2(fds[0][1], 1) < 0)
			exit(1);
	}
	else if (psize - 1 == i)
	{
		if (dup2(fds[i - 1][0], 0) < 0)
			exit(1);
	}
	else
	{
		dup2(fds[i - 1][0], 0);
		dup2(fds[i][1], 1);
	}
	close_fds(fds, psize);
}

void	do_cmd(t_data *data, t_spl_pipe *tmp)
{
	int	i;

	i = 0;
	if (access(*tmp->cmd, F_OK) == 0)
		data->path = *tmp->cmd;
	else if (ft_strchr(*tmp->cmd, '/'))
	{
		printf("🔻minishell> %s: command not found ❌\n", *tmp->cmd);
		exit(1);
	}
	else
		data->path = get_cmd(data->cmd_paths, *data->cmd_line->head->cmd);
	if (!data->path)
		free(data->path);
	execve(data->path, tmp->cmd, &tmp->cmd[0]);
	printf("🔻minishell> %s: command not found ❌\n", *tmp->cmd);//EXIT not work
	exit(1);
}

void	forking(int (*fds)[2], int psize, t_spl_pipe *tmp, t_data *data)
{
	int	i;

	i = -1;
	while (++i < psize - 1)
		if (pipe(fds[i]) == -1)
		{
			printf("🔻minishell> Input File: No such file or directory ❌\n");
			free(fds);
			fds = NULL;
		}
	i = 0;
	while (i < psize)
	{
		tmp->pid = fork();
		if (tmp->pid == -1)
			printf("🔻minishell> fork: Resource temporarily unavailable ❌\n");
		else if (tmp->pid == 0)
		{
			if (psize == 1)
				do_cmd(data, tmp);
			else
			{
				open_pipes(i, fds, psize);
				do_cmd(data, tmp);
			}
		}
		tmp = tmp->next;
		i++;
	}
}

int	execute(t_data *data)
{
	t_spl_pipe	*tmp;
	int			psize;
	int			res;
	int			(*fds)[2];
	int			i;

	tmp = data->cmd_line->head;
	psize = data->cmd_line->size;
	data->path = getenv("PATH");
	data->cmd_paths = ft_split(data->path, ':');
	fds = malloc(sizeof (*fds) * (psize - 1));
	forking(fds, psize, tmp, data);
	close_fds(fds, psize);
	i = -1;
	while (data->cmd_paths[++i])
		free(data->cmd_paths[i]);
	free(data->cmd_paths);
	tmp = data->cmd_line->head;
	while (tmp)
	{
		waitpid(tmp->pid, &res, 0);
		tmp = tmp->next;
	}
	data->exit_status = WEXITSTATUS(res);
	return (0);
}

void	b_fork(int (*fds)[2], int psize, t_spl_pipe *tmp, t_data *data)
{
	int	i;
	data->path = getenv("PATH");
	data->cmd_paths = ft_split(data->path, ':');
	i = -1;
	while (data->cmd_paths[++i])
		free(data->cmd_paths[i]);
	free(data->cmd_paths);

	i = -1;
	while (++i < psize - 1)
		if (pipe(fds[i]) == -1)
		{
			printf("🔻minishell> Input File: No such file or directory ❌\n");
			free(fds);
			fds = NULL;
		}
	i = 0;
	while (i < psize)
	{
		tmp->pid = fork();
		if (tmp->pid == -1)
			printf("🔻minishell> fork: Resource temporarily unavailable ❌\n");
		else if (tmp->pid == 0)
		{
			open_pipes(i, fds, psize);
			//do_cmd(data, tmp);
			printf("exit = %d\n", ft_exit(data, tmp->cmd));
		}
		tmp = tmp->next;
		i++;
	}
}

void	builtin_forking(t_data *data)
{
	t_spl_pipe	*tmp;
	int			psize;
	int			res;
	int			(*fds)[2];

	tmp = data->cmd_line->head;
	psize = data->cmd_line->size;


	fds = malloc(sizeof (*fds) * (psize - 1));
	b_fork(fds, psize, tmp, data);
	close_fds(fds, psize);

	tmp = data->cmd_line->head;
	while (tmp)
	{
		waitpid(tmp->pid, &res, 0);
		tmp = tmp->next;
	}
	data->exit_status = WEXITSTATUS(res);
}
