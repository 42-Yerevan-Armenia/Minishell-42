/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:19:05 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/07 19:03:02 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_spl_pipe	*create_list_pipe(void)
{
	t_list_spl_pipe	*list;

	list = malloc(sizeof(t_list_spl_pipe));
	if (list == NULL && !ft_perror("minishell: "))
		exit(1);
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
	return (list);
}

t_spl_pipe	*new_spl_pipe(t_data *data)
{
	t_spl_pipe	*new_pipe;

	new_pipe = malloc(sizeof(t_spl_pipe));
	if (new_pipe == NULL && !ft_perror("minishell: "))
		exit(1);
	new_pipe->flag_new_pipe = 0;
	new_pipe->fd_in = 0;
	new_pipe->fd_out = 1;
	new_pipe->cmd = NULL;
	new_pipe->heredoc = NULL;
	new_pipe->rdc = NULL;
	new_pipe->f_name = NULL;
	new_pipe->hdoc_mode = 0;
	new_pipe->fd_hdc = 0;
	new_pipe->input_mode = 0;
	new_pipe->tmp = 2;
	new_pipe->data = data;
	new_pipe->next = NULL;
	new_pipe->prev = NULL;
	return (new_pipe);
}

t_spl_pipe	*add_pipe(t_list_spl_pipe *list, t_spl_pipe *new_pipe)
{
	list->size++;
	if (list->head == NULL)
	{
		list->head = new_pipe;
		list->tail = new_pipe;
	}
	else
	{
		list->tail->next = new_pipe;
		new_pipe->prev = list->tail;
		list->tail = list->tail->next;
	}
	return (new_pipe);
}
