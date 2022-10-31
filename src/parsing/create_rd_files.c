/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rd_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:32:59 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/31 10:16:23 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_rd_files(t_parse *parser)
{
	int			i;
	t_spl_pipe	*tmp;

	i = 0;
	tmp = parser->data->cmd_line->head;
	while (tmp)
	{
		while (tmp->out_files[i])
		{
			if (i != 0)
				if (close(tmp->fd_out) == -1 && ft_perror("minishell: "))
					return (1);
			tmp->fd_out = open(tmp->out_files[i],
					O_CREAT | tmp->output_mode | O_RDWR, 0777);
			if (tmp->fd_out == -1 && ft_perror("minishell: "))
				return (START_RD_LN);
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}
