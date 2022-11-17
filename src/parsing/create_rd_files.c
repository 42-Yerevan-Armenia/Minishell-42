/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rd_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:32:59 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/17 20:34:36 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_infiles(t_spl_pipe *head, int i, t_data *data)
{
	if (head->fd_in != 0)
		if (close(head->fd_in) == -1 && !ft_perror("minishell: "))
			return (START_RD_LN);
	head->fd_in = open(head->rdc[i], O_RDONLY);
	if (head->fd_in == -1 && \
		!ft_perror(ft_strjoin("minishell: ", head->rdc[i])))
	{
		data->exit_status = 1;
		return (START_RD_LN);
	}
	return (0);
}

int	create_outfiles(t_spl_pipe *head, int i, int mode)
{
	if (head->fd_out != 1)
		if (close(head->fd_out) == -1 && !ft_perror("minishell: "))
			return (START_RD_LN);
	head->fd_out = open(head->rdc[i],
			O_CREAT | mode | O_RDWR, 0644);
	if (head->fd_out == -1 && ft_strjoin("minishell: ", head->rdc[i]))
		return (START_RD_LN);
	return (0);
}

int	create_rd_files(t_spl_pipe *head, t_data *data)
{
	int			i;
	int			mode;

	i = -1;
	while (head->rdc[++i])
	{
		if (!ft_strcmp(head->rdc[i], BAD_RDR)
			&& ft_putstr_fd(BAD_RDR, 2, FREE_OFF)
			&& put_exit_s(head->data, 1))
			return (START_RD_LN);
		mode = ft_get_rdc_mode(head->rdc[i]);
		if (mode == IN_FILES)
		{
			if (create_infiles(head, i, data) == START_RD_LN)
				return (START_RD_LN);
		}
		if (mode == O_TRUNC || mode == O_APPEND)
		{
			if (create_outfiles(head, i, mode) == START_RD_LN)
				return (START_RD_LN);
		}
	}
	return (0);
}
