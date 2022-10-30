/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infile_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:33:28 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/30 16:08:07 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_infile_fd(t_spl_pipe *node)
{
	int i;
	t_spl_pipe *tmp;

	i = 0;
	tmp = node;
	if (node->f_name)
	{
		close(tmp->fd_in);
		unlink(node->f_name);
	}
	while (tmp->in_files[i])
	{
		if (i != 0)
			if (close(tmp->fd_in) == -1 && ft_perror("minishell"))
				return (START_RD_LN);
		tmp->fd_in = open(tmp->in_files[i], O_RDONLY);
		if (tmp->fd_in == -1 && ft_perror("minishell"))
			return (START_RD_LN);
		i++;
	}
	return (0);
}