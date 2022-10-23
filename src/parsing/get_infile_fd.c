/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infile_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:33:28 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/22 20:14:02 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_infile_fd(t_parse *parser)
{
	int i;
	t_spl_pipe *tmp;

	i = 0;
	tmp = parser->data->cmd_line->head;
	while (tmp->in_files[i])
	{
		if (i != 0)
			if (close(tmp->fd_in) == -1 && ft_perror("minishell"))
				return (1);
		tmp->fd_in = open(tmp->in_files[i], O_RDONLY);
		if (tmp->fd_in == -1 && ft_perror("minishell"))
			return (1);
		i++;
	}
	return (0);
}