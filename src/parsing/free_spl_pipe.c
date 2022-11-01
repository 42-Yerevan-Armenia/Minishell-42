/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_spl_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 17:21:30 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/01 11:27:52 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_spl_pipe(t_list_spl_pipe **list)
{
	while ((*list)->head)
	{
		free_double((void *)&(((*list)->head)->cmd));
		free_double((void *)&((*list)->head)->out_files);
		free_double((void *)&((*list)->head)->in_files);
		free_double((void *)&((*list)->head)->heredoc);
		if ((*list)->head->f_name != NULL && (!unlink((*list)->head->f_name)
				|| ft_perror("minisehll: heredoc: ")))
			free_arr((void *)&((t_spl_pipe *)(*list)->head)->f_name);
		free_arr(&((*list)->head)->hdoc_input);
		(*list)->size = 0;
		if (((t_spl_pipe *)(*list)->head)->next == NULL)
		{
			free(((*list)->head));
			break ;
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
