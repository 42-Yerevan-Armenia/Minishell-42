/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rd_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:32:59 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/23 12:57:58 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int create_rd_files(t_parse *parser)
{
	int i;
	t_spl_pipe *tmp;

	i = 0;
	tmp = parser->data->cmd_line->head;
	while (tmp->out_files[i])
	{
		if (i != 0)
			if (close(tmp->fd_out) == -1 && ft_perror("minishell"))
				return (1);
		tmp->fd_out = open(tmp->out_files[i], O_CREAT | tmp->output_mode | O_RDWR, 0777);
		printf("fd = %d\n", tmp->fd_out );
		if (tmp->fd_out == -1 && ft_perror("minishell"))
			return (1);
		i++;
	}
	return (0);
}