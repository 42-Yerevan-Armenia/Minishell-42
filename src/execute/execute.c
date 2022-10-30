/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:09:43 by arakhurs          #+#    #+#             */
/*   Updated: 2022/10/27 18:09:58 by vaghazar         ###   ########.fr       */
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

int run_builtins(t_data *data, t_spl_pipe *tmp, int psize)
{
	if (!ft_strcmp(tmp->cmd[0], "cd"))
		printf("✅ exit = %d\n", cd(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "echo"))
		printf("✅ exit = %d\n", echo(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "env"))
		printf("✅ exit = %d\n", env(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "exit"))
		printf("✅ exit = %d\n", ft_exit(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "export"))
		printf("✅ exit = %d\n", export(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "pwd"))
		printf("✅ exit = %d\n", pwd(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "unset"))
		printf("✅ exit = %d\n", unset(data, tmp->cmd));
	return (0);
}

void	do_cmd(t_data *data, t_spl_pipe *tmp, int psize)
{
	int	i;

	i = 0;
	
	if (ft_strnstr(BUILTINS, tmp->cmd[0], 35))
		run_builtins(data, tmp, psize);
	else
	{
		if (access(*tmp->cmd, F_OK) == 0)
			data->path = *tmp->cmd;
		else if (ft_strchr(*tmp->cmd, '/'))
			printf(NOT_FOUND, *tmp->cmd);
		else
			data->path = get_cmd(data->cmd_paths, *tmp->cmd);
		if (!data->path)
			free(data->path);
		execve(data->path, tmp->cmd, &tmp->cmd[0]);
		printf(NOT_FOUND, *tmp->cmd);
	}
	exit(1);
}

void	forking(int (*fds)[2], int psize, t_spl_pipe *tmp, t_data *data)
{
	int	i;

	i = -1;
	while (++i < psize - 1)
		if (pipe(fds[i]) == -1)
			ft_putstr_fd(INPUT_FILE, 2);
	i = 0;
	while (i < psize)
	{
		tmp->pid = fork();
		if (tmp->pid == -1)
			ft_putstr_fd(FORK, 2);
		else if (tmp->pid == 0)
		{
			if (psize == 1)
				do_cmd(data, tmp, psize);
			else
			{
				open_pipes(i, fds, psize);
				do_cmd(data, tmp, psize);
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
	free_double((void *)&data->cmd_paths);
	tmp = data->cmd_line->head;
	while (tmp)
	{
		waitpid(tmp->pid, &res, 0);
		tmp = tmp->next;
	}
	data->exit_status = WEXITSTATUS(res);
	return (0);
}
