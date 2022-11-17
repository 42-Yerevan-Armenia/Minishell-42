/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_spl_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:21:30 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/17 10:48:56 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_spl_pipe(t_list_spl_pipe **list)
{
	while ((*list)->head)
	{
		free_double((void *)&(((*list)->head)->cmd));
		free_double((void *)&((*list)->head)->heredoc);
		free_double((void *)&((*list)->head)->rdc);
		if (((*list)->head)->fd_in != 0)
			close((*list)->head->fd_in);
		if (((*list)->head)->fd_out != 1)
			close((*list)->head->fd_out);
		if ((*list)->head->f_name != NULL && (!unlink((*list)->head->f_name)
				|| !ft_perror("minisehll: heredoc: ")))
			free_arr((void *)&((t_spl_pipe *)(*list)->head)->f_name);
		if (((t_spl_pipe *)(*list)->head)->next == NULL)
		{
			free(((*list)->head));
			break ;
		}
		(*list)->head = ((t_spl_pipe *)(*list)->head)->next;
		free(((t_spl_pipe *)(*list)->head)->prev);
	}
	(*list)->head = NULL;
	(*list)->tail = NULL;
	(*list)->size = 0;
	return (0);
}
