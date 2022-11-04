/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rd_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:32:59 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/03 14:18:16 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_rd_files(t_spl_pipe *head, int *error)
{
	int			i;
	int			mode;

	i = -1;
	while (head->rdc[++i])
	{
		if (!ft_strcmp(head->rdc[i], BAD_RDR) && ft_putstr_fd(BAD_RDR, 2, FREE_OFF))
			return (START_RD_LN);
		mode = ft_get_rdc_mode(head->rdc[i]);
		if (mode == IN_FILES)
		{
			if (head->fd_in != 0)
				if (close(head->fd_in) == -1 && ft_perror("minishell: "))
					return (START_RD_LN);
			head->fd_in = open(head->rdc[i], O_RDONLY);
			if (head->fd_in == -1 && ft_putstr_fd(ft_strjoin_1(ft_strjoin("minishell: ", head->rdc[i]), NO_SUCH_F), 2, FREE_ON))
				return (START_RD_LN);
		}
		if (mode == O_TRUNC || mode == O_APPEND)
		{
			if (head->fd_out != 1)
				if (close(head->fd_out) == -1 && ft_perror("minishell: "))
					return (START_RD_LN);
			head->fd_out = open(head->rdc[i],
				O_CREAT | mode | O_RDWR, 0644);
			if (head->fd_out == -1 && ft_perror("minishell: "))
				return (START_RD_LN);
		}
		// printf("❎ head->fd_in = %d\n", head->fd_in);
		// printf("❎ head->fd_out = %d\n", head->fd_out);
	}
	return (0);
}
