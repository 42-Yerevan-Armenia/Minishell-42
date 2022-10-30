/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_spl_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:21:30 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/28 21:27:44 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	free_spl_pipe(t_list_spl_pipe **list)
{
	while ((*list)->head)
	{
		free_double((void *)&(((t_spl_pipe *)(*list)->head)->cmd));
		free_double((void *)&((t_spl_pipe *)(*list)->head)->out_files);
		free_double((void *)&((t_spl_pipe *)(*list)->head)->in_files);
		free_double((void *)&((t_spl_pipe *)(*list)->head)->heredoc);
		free_arr(&((t_spl_pipe *)(*list)->head)->hdoc_input);
		(*list)->size = 0;
		if (((t_spl_pipe *)(*list)->head)->next == NULL)
		{
			free(((*list)->head));
			break;
		}
		(*list)->head = ((t_spl_pipe *)(*list)->head)->next;
		if (((*list)->head))
			free(((t_spl_pipe *)(*list)->head)->prev);
	}
	(*list)->head = NULL;
	(*list)->tail = NULL;
	(*list)->size = 0;
	return (0);
}

int	free_data(t_data **data)
{
	free_double((void *)&(*data)->hdoc_mode);
	free_double((void *)&(*data)->hdoc_mode);
	return (0);
}
