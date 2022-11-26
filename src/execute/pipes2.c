/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:14:04 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/26 13:07:35 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pipe_redirections(t_spl_pipe *tmp)
{
	if (dup2(tmp->fd_out, 1) == -1 || dup2(tmp->fd_in, 0) == -1)
	{
		if (close(tmp->fd_out) == -1 || close(tmp->fd_in) == -1)
			return (START_RD_LN);
		return (START_RD_LN);
	}
	return (0);
}

int	pipex(int (*fds)[2], int psize)
{
	int	i;

	i = -1;
	while (++i < psize - 1)
	{
		if (pipe(fds[i]) == -1)
		{
			ft_perror("🔻minishell: pipe");
			close_fds(fds, i + 1);
			return (START_RD_LN);
		}
	}
	return (0);
}

int	pid_check(int (*fds)[2], int psize, int i, \
t_spl_pipe *tmp, t_data *data)
{
	signal(SIGQUIT, SIG_DFL);
	if (pipe_redirections(tmp) == START_RD_LN)
		return (START_RD_LN);
	if (psize == 1)
		do_cmd(data, tmp);
	else
	{
		if (open_pipes(tmp, i, fds, psize) == START_RD_LN)
			return (START_RD_LN);
		do_cmd(data, tmp);
	}
	return (0);
}
