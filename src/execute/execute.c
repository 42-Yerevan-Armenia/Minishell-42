/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:09:43 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/05 16:45:25 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	run_builtins(t_data *data, t_spl_pipe *tmp)
{
	if (!ft_strcmp(tmp->cmd[0], "cd"))
		printf("✅ exit = %d\n", cd(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "echo"))
		printf("✅ exit = %d\n", echo(tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "env"))
		printf("✅ exit = %d\n", env(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "exit"))
		printf("✅ exit = %d\n", ft_exit(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "export"))
		printf("✅ exit = %d\n", export(data, tmp->cmd));
	else if (!ft_strcmp(tmp->cmd[0], "pwd"))
		printf("✅ exit = %d\n", pwd(data));
	else if (!ft_strcmp(tmp->cmd[0], "unset"))
		printf("✅ exit = %d\n", unset(data, tmp->cmd));
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
			pipe_redirections(tmp);
			if (psize == 1)
				do_cmd(data, tmp, psize);
			else
			{
				open_pipes(tmp, i, fds, psize);
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

	tmp = data->cmd_line->head;
	psize = data->cmd_line->size;
	data->path = get_val(data->env->head, "PATH");
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
	return (0);
}
