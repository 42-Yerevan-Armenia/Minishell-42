/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:09:43 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/04 12:56:32 by vaghazar         ###   ########.fr       */
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
		// if (close(tmp->fd_in) != 0)
		// 	perror("CLOSE FAILED");
		// if (close(tmp->fd_out) != 1)
		// 	perror("CLOSE FAILED");
	}
	free(fds);
}

void	open_pipes(t_data *data, t_spl_pipe *tmp, int i, int (*fds)[2], int psize)
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
		if (access(*tmp->cmd, F_OK) == 0 && ft_strcmp(*tmp->cmd, "minishell"))
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

void	forking(int (*fds)[2], int psize, t_spl_pipe *tmp, t_data *data)
{
	int	i;

	i = -1;
	while (++i < psize - 1)
		if (pipe(fds[i]) == -1)
			ft_putstr_fd(INPUT_FILE, 2, FREE_OFF);
	i = -1;
	while (++i < psize)
	{
		tmp->pid = fork();
		if (tmp->pid == -1)
		{
			ft_putstr_fd(FORK, 2, FREE_OFF);
			break ;
		}
		else if (tmp->pid == 0)
		{
			if (psize == 1)
				do_cmd(data, tmp, psize);
			else
			{
				open_pipes(data, tmp, i, fds, psize);
				do_cmd(data, tmp, psize);
			}
		}
		tmp = tmp->next;
	}
}

int	execute(t_data *data)
{
	t_spl_pipe	*tmp;
	int			psize;
	int			res;
	int			(*fds)[2];
	int			i;

	// printf("❎ %s\n", get_val(data->env->head, "PATH"));
	// printf("❎ %s\n", *data->envp);
	tmp = data->cmd_line->head;
	psize = data->cmd_line->size;
	data->path = get_val(data->env->head, "PATH");
	//data->path = getenv("PATH");
	if (!data->path)
		return (printf(NO_DIR, *tmp->cmd));
	data->cmd_paths = ft_split(data->path, ':');
	fds = malloc(sizeof (*fds) * (psize - 1));
	forking(fds, psize, tmp, data);
	close_fds(fds, tmp, psize);
	free_double((void *)&data->cmd_paths);
	tmp = data->cmd_line->head;
	while (tmp)
	{
		waitpid(tmp->pid, &res, 0);
		tmp = tmp->next;
	}
	data->exit_status = WEXITSTATUS(res);
	//pipes(data, psize, tmp);
	return (0);
}
