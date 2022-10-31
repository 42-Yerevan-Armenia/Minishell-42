/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 20:42:48 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/31 20:43:02 by vaghazar         ###   ########.fr       */
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
			ft_heredoc(head, data->parser, &error);
		if (error == START_RD_LN)
			return (START_RD_LN);
		if (error == START_RD_LN)
			return (START_RD_LN);
		if (head->input_mode == IN_FILES)
			if (get_infile_fd(head) == START_RD_LN)
				return (START_RD_LN);
		head = head->next;
	}
	return (0);
}
