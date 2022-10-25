/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:59:27 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/23 09:53:38 by vaghazar         ###   ########.fr       */
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
		while (tmp->in_files && tmp->in_files[i])
		{
			printf("🛑 %s, ", tmp->in_files[i++]);
		}
		i = 0;
		printf("**OUT_FILES - ");
		while (tmp->out_files && tmp->out_files[i])
		{
			printf("🛑 %s, ", tmp->out_files[i++]);
		}
		i = 0;
		printf("**HEREDOC - ");
		while (tmp->heredoc && tmp->heredoc[i])
		{
			printf("🛑 %s, ", tmp->heredoc[i++]);
		}
		i = 0;
		// printf("\n----------------------------------\n");
		// printf("APPEND \n");
		// while (tmp->out_append_files[i])
		// {
		// 	printf("%s\n", tmp->out_append_files[i++]);
		// }
		printf("OUTPUT_MODE = %d, ", tmp->output_mode);
		printf("INPUT_MODE = %d ", tmp->input_mode);
		printf("HDOC_MODE = %d", tmp->hdoc_mode);
		printf("\n\n*********************************\n");
		tmp = tmp->next;
	}
}
