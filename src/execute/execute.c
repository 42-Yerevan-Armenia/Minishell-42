/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:09:43 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/09 18:59:41 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_data *data)
{
	int		i;
	int		ps;

	ps = data->cmd_line->size;
	i = -1;
	while (i++ < ps)
	{
		if (data->cmd_line->head->cmd[0] && data->cmd_line->head->cmd[0][0] \
		&& ps == 1 && search_builtin(data->cmd_line->head->cmd[0], data->builtins))
		{
			ps = 0;
			run_builtins(data, data->cmd_line->head);
		}
		else if (data->cmd_line->head->cmd[0])
		{
			ps = 0;
			run_binar(data);
		}
	}
}

int	run_builtins(t_data *data, t_spl_pipe *tmp)
{
	if (!ft_strcmp(tmp->cmd[0], "cd"))
		data->exit_status = cd(data, tmp->cmd);
	else if (!ft_strcmp(tmp->cmd[0], "echo"))
		data->exit_status = echo(tmp->cmd);
	else if (!ft_strcmp(tmp->cmd[0], "env"))
		data->exit_status = env(data, tmp->cmd);
	else if (!ft_strcmp(tmp->cmd[0], "exit"))
		data->exit_status = ft_exit(data, tmp->cmd);
	else if (!ft_strcmp(tmp->cmd[0], "export"))
		data->exit_status = export(data, tmp->cmd);
	else if (!ft_strcmp(tmp->cmd[0], "pwd"))
		data->exit_status = pwd(data);
	else if (!ft_strcmp(tmp->cmd[0], "unset"))
		data->exit_status = unset(data, tmp->cmd);
	return (0);
}

void	pipex(int (*fds)[2], int psize)
{
	int	i;

	i = -1;
	while (++i < psize - 1)
		if (pipe(fds[i]) == -1)
			ft_putstr_fd(INPUT_FILE, 2, FREE_OFF);
}

void	pipe_redirections(t_spl_pipe *tmp)
{
	dup2(tmp->fd_out, 1);
	dup2(tmp->fd_in, 0);
}

void	forking(int (*fds)[2], int psize, t_spl_pipe *tmp, t_data *data)
{
	int	i;

	pipex(fds, psize);
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
			signal(SIGQUIT, SIG_DFL);
			pipe_redirections(tmp);
			if (psize == 1)
				do_cmd(data, tmp);
			else
			{
				open_pipes(tmp, i, fds, psize);
				do_cmd(data, tmp);
			}
		}
		tmp = tmp->next;
	}
}


int	run_binar(t_data *data)
{
	t_spl_pipe	*tmp;
	int			(*fds)[2];

	tmp = data->cmd_line->head;
	data->psize = data->cmd_line->size;
	data->path = get_val(data->env->head, "PATH");
	if (!data->path)
		ft_putstr_fd(ft_strjoin_2("🔻minishell> ", \
		ft_strjoin(*tmp->cmd, NO_DIR)), 2, FREE_ON);
	data->cmd_paths = ft_split(data->path, ':');
	fds = malloc(sizeof (*fds) * (data->psize - 1));
	forking(fds, data->psize, tmp, data);
	close_fds(fds, data->psize);
	free_double((void *)&data->cmd_paths);
	tmp = data->cmd_line->head;
	signal(SIGINT, SIG_IGN);
	while (tmp)
	{
		waitpid(tmp->pid, &data->res, 0);
		tmp = tmp->next;
	}
	if (WIFEXITED(data->res))
		data->exit_status = WEXITSTATUS(data->res);
	else if (WIFSIGNALED(data->res))
	{
		data->exit_status = WTERMSIG(data->res) + 128;
		if (WTERMSIG(data->res) == SIGQUIT)
			printf("Quit: 3\n");
		if (WTERMSIG(data->res) == SIGINT)
			write(1, "\n", 1);
	}
	hook_signals();
	return (0);
}
