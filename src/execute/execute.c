/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:09:43 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/22 15:43:59 by vaghazar         ###   ########.fr       */
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
		if (data->cmd_line->head->cmd[0] && data->cmd_line->head->cmd[0][0] && \
		ps == 1 && search_builtin(data->cmd_line->head->cmd[0], data->builtins))
		{
			ps = 0;
			run_builtins(data, data->cmd_line->head);
		}
		else if (data->cmd_line->head->cmd[0])
		{
			ps = 0;
			if (run_binar(data) == -1 && printf("barev\n"))
				return ;
		}
	}
}

int	run_builtins(t_data *data, t_spl_pipe *tmp)
{
	if (!ft_strcmp(tmp->cmd[0], "cd"))
		data->exit_status = cd(data, tmp->cmd);
	else if (!ft_strcmp(tmp->cmd[0], "echo"))
		data->exit_status = echo(tmp, tmp->cmd);
	else if (!ft_strcmp(tmp->cmd[0], "env"))
		data->exit_status = env(tmp, tmp->cmd);
	else if (!ft_strcmp(tmp->cmd[0], "exit"))
		ft_exit(data, tmp->cmd, tmp);
	else if (!ft_strcmp(tmp->cmd[0], "export"))
		data->exit_status = export(data, tmp->cmd, tmp);
	else if (!ft_strcmp(tmp->cmd[0], "pwd"))
		data->exit_status = pwd(data, tmp);
	else if (!ft_strcmp(tmp->cmd[0], "unset"))
		data->exit_status = unset(data, tmp->cmd);
	return (0);
}

int	forking(int (*fds)[2], int psize, t_spl_pipe *head, t_data *data)
{
	int			i;
	t_spl_pipe	*tmp;
	int			fd;

	tmp = head;
	pipex(fds, psize);
	i = -1;
	while (++i < psize)
	{
		tmp->pid = fork();
		// if (tmp->pid == -1)
		// 	break ;
		if (tmp->pid == -1)
		{
			tmp = head;
			// kill (tmp->pid, SIGTERM);
			// write(0, " \0", 2);
			
			close(0);
			// while (tmp)
			// {
				// sleep();
				// tmp = tmp->next;
			// }
			
			// while (tmp->next)
			// {
			// 	// printf("hajox\n");
			// 	// if (tmp->pid != -1)
			// 	printf("%d\n", tmp->pid);
			// 		if (kill (tmp->pid, SIGKILL) == 0)
			// 			printf("succes\n");
			// 	tmp = tmp->next;
			// 	usleep(10000);
			// }
			ft_putstr_fd(FORK, 2, FREE_OFF);
			data->exit_status = 1;
			// break ;
			return (-1);
/*
			close(fds[i][1]);
			dup2(fds[i][1], 0);
			ft_putstr_fd(FORK, 2, FREE_OFF);
			return (-1);
			// tmp = head;
			// kill (tmp->pid, SIGKILL);
			// break ;
*/
		}
		else if (tmp->pid == 0)
			pid_check(fds, psize, i, tmp, data);
		tmp = tmp->next;
	}
	return (0);
}

void	sig_wait(t_spl_pipe	*tmp, t_data *data)
{
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
			ft_putstr_fd("Quit: 3\n", 2, FREE_OFF);
		if (WTERMSIG(data->res) == SIGINT)
			write(1, "\n", 1);
	}
}

int	run_binar(t_data *data)
{
	t_spl_pipe	*tmp;
	int			ret;
	int			(*fds)[2];

	tmp = data->cmd_line->head;
	data->psize = data->cmd_line->size;
	data->path = get_val(data->env->head, "PATH", ENV);
	if (data->path)
		data->cmd_paths = ft_split(data->path, ':');
	fds = malloc(sizeof (*fds) * (data->psize - 1));
	ret = forking(fds, data->psize, tmp, data);
	// printf("ret = %d\n", ret);
	// if (!close_fds(fds, data->psize) && ret == -1)
	// 	return(1);
	close_fds(fds, data->psize);
	if (data->path)
		free_double((void *)&data->cmd_paths);
	if (ret == -1 && printf("\n\n\n\n\n\n\n\\n\n\n\n\n\n\n\n\n\n\n\\n\n\n"))
		return (-1);
	tmp = data->cmd_line->head;
	signal(SIGINT, SIG_IGN);
	sig_wait(tmp, data);
	hook_signals();	return (0);
}
