/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 20:42:48 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/03 13:46:18 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_heredoc(t_data *data)
{
	t_spl_pipe	*head;
	int			i;
	int			error;

	head = data->cmd_line->head;
	i = 0;
	error = 0;
	while (head)
	{
		if (head->heredoc[0])
			if (ft_heredoc(head, data->parser) == START_RD_LN)
				return (START_RD_LN);
		if (create_rd_files(head, &error) == START_RD_LN)
			return (START_RD_LN);
		if (head->hdoc_mode == HEREDOC)
			head->fd_in = head->fd_hdc;
		head = head->next;
	}
	return (0);
}
