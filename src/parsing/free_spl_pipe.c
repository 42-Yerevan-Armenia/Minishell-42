/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_spl_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:21:30 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/15 18:20:38 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	free_spl_pipe(t_list_spl_pipe **list)
{
	while ((*list)->head)
	{
		free_double(&(((t_spl_pipe *)(*list)->head)->cmd));
		free_double(&((t_spl_pipe *)(*list)->head)->out_files);
		free_double(&((t_spl_pipe *)(*list)->head)->in_files);
		free_double(&((t_spl_pipe *)(*list)->head)->heredoc);
		if (((t_spl_pipe *)(*list)->head)->next == NULL)
		{
			free(((*list)->head));
			(*list)->head = NULL;
			break;
		}
		(*list)->head = ((t_spl_pipe *)(*list)->head)->next;
		if (((*list)->head))
			free(((t_spl_pipe *)(*list)->head)->prev);
	}
	return (0);
}
