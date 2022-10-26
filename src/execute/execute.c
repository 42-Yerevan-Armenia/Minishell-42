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
		if (dup2(fds[0][1], 1) < 0 && !ft_perror("minishell"))
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
		printf("🔻minishell> %s: No such file or directory ❌\n", *tmp->cmd);
	else
		data->path = get_cmd(data->cmd_paths, *tmp->cmd);
	if (!data->path)
		free(data->path);
	execve(data->path, tmp->cmd, &tmp->cmd[0]);
	exit(1);
}

void	execute(t_data *data)
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
	// if (tmp->fd_in != -1)
	// 	dup2(tmp->fd_in, tmp->fds[0][0]);
	// dup2(tmp->fd_out, tmp->fds[psize][1]);
	i = -1;
	while (++i < psize - 1)
		pipe(fds[i]);
	i = 0;
	while (i < psize)
	{
		tmp->pid = fork();
		if (tmp->pid == -1)
			printf("❌ Error\n");
		if (tmp->pid == 0)
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
}

int	main(int ac, char **av, char **envp)
{
	t_parse	parser;
	t_data	data;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (ac == 1)
	{
		init(&parser, &data, envp);
		data.error_message = NULL;
		while (1)
		{
			parser.rd_ln = readline("🔻minishell> ");
			if (parser.rd_ln[0])
			{
				add_history(parser.rd_ln);
				parsing(&parser);
				execute(&data);
				free_spl_pipe(&data.cmd_line);
			}
			free_arr(&parser.rd_ln);
		}
		free_envp(&data.env);
	}
}
