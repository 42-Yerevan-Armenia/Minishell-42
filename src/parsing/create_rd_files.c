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

int	create_rd_files(t_parse *parser, int *error)
{
	int			i;
	t_spl_pipe	*tmp;
	int			mode;

	i = -1;
	tmp = parser->data->cmd_line->head;
	while (tmp->rdc[++i])
	{
		if (!ft_strcmp(tmp->rdc[i], BAD_RDR) && ft_putstr_fd(BAD_RDR, 2, FREE_OFF))
			return (START_RD_LN);
		mode = ft_get_rdc_mode(tmp->rdc[i]);
		if (mode == IN_FILES)
		{
			if (tmp->fd_in != 0)
				if (close(tmp->fd_in) == -1 && ft_perror("minishell: "))
					return (START_RD_LN);
			tmp->fd_in = open(tmp->rdc[i], O_RDONLY);
			if (tmp->fd_in == -1 && ft_putstr_fd(ft_strjoin_1(ft_strjoin("minishell: ", tmp->rdc[i]), NO_SUCH_F), 2, FREE_ON))
				return (START_RD_LN);
		}
		if (mode == O_TRUNC || mode == O_APPEND)
		{
			if (tmp->fd_out != 1)
				if (close(tmp->fd_out) == -1 && ft_perror("minishell: "))
					return (START_RD_LN);
			tmp->fd_out = open(tmp->rdc[i],
				O_CREAT | mode | O_RDWR, 0777);
			if (tmp->fd_out == -1 && ft_perror("minishell: "))
				return (START_RD_LN);
		}
		// printf("tmp->fd_in = %d\n", tmp->fd_in);
		// printf("tmp->fd_out = %d\n", tmp->fd_out);
	}
	return (0);
}
