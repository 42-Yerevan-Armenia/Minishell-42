/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 20:42:48 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/07 20:03:18 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_heredoc(t_data *data)
{
	t_spl_pipe	*head;

	head = data->cmd_line->head;
	while (head)
	{
		if (head->heredoc[0])
			if (ft_heredoc(head, data->parser) == START_RD_LN)
				return (START_RD_LN);
		head = head->next;
	}
	head = data->cmd_line->head;
	while (head)
	{
		if (create_rd_files(head) == START_RD_LN)
			return (START_RD_LN);
		if (head->input_mode == HEREDOC)
			head->fd_in = head->fd_hdc;
		head = head->next;
	}
	return (0);
}
