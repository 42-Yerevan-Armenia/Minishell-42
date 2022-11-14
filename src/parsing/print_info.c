/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:42:00 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/13 17:39:52 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_info(t_parse *parser)
{
	int	i;
	t_spl_pipe *tmp = parser->data->cmd_line->head;

	i = 0;
	
	while (tmp)
	{
		printf("\n----------------------------------\n");
		i = 0;
		printf("**CMD - ");
		while (tmp->cmd && tmp->cmd[i])
		{
			printf("🛑 %s ", tmp->cmd[i++]);
		}
		printf("**IN_FILES - ");
		i = 0;
		while (tmp->rdc[i])
		{
			if (ft_get_rdc_mode(tmp->rdc[i]) == IN_FILES)
				printf("🛑 %s, ", tmp->rdc[i]);
			i++;
		}
		i = 0;
		printf("**OUT_FILES - ");
		while (tmp->rdc && tmp->rdc[i])
		{
			if (ft_get_rdc_mode(tmp->rdc[i]) == O_TRUNC)
				printf("🛑 %s, ", tmp->rdc[i]);
			i++;
		}
		i = 0;
		printf("**HEREDOC - ");
		while (tmp->heredoc && tmp->heredoc[i])
		{
			printf("🛑 %s, ", tmp->heredoc[i++]);
		}
		i = 0;
		// printf("\n----------------------------------\n");
		printf("APPEND ");
		while (tmp->rdc[i])
		{
			if (ft_get_rdc_mode(tmp->rdc[i]) == O_APPEND)
				printf("🛑 %s", tmp->rdc[i]);
			i++;
		}
		printf("INPUT_MODE = %d ", tmp->input_mode);
		printf("HDOC_MODE = %d", tmp->hdoc_mode);
		printf("\n\n*********************************\n");
		tmp = tmp->next;
	}
}
