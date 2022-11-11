/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 20:14:04 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/11 20:15:16 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipe_redirections(t_spl_pipe *tmp)
{
	dup2(tmp->fd_out, 1);
	dup2(tmp->fd_in, 0);
}

void	pipex(int (*fds)[2], int psize)
{
	int	i;

	i = -1;
	while (++i < psize - 1)
		if (pipe(fds[i]) == -1)
			ft_putstr_fd(INPUT_FILE, 2, FREE_OFF);
}

void	pid_check(int (*fds)[2], int psize, int i, \
t_spl_pipe *tmp, t_data *data)
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
