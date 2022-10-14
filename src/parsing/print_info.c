/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:59:27 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/14 10:07:48 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

void print_info(t_parse *parser)
{
	int	i;
	t_node *tmp = parser->data->cmd_line->head;

	i = 0;
	while (tmp)
	{
		// t_node *tmp = parser->data->cmd_line->head;

		printf("\n----------------------------------\n");
		printf("IN_FILES \n");
		while (tmp->in_files && tmp->in_files[i])
		{
			printf("%s, ", tmp->in_files[i++]);
		}
		i = 0;
		printf("\n----------------------------------\n");
		printf("OUT_FILES \n");
		while (tmp->out_files && tmp->out_files[i])
		{
			printf("%s, ", tmp->out_files[i++]);
		}
		i = 0;
		printf("\n----------------------------------\n");
		printf("HEREDOC \n");
		while (tmp->heredoc && tmp->heredoc[i])
		{
			printf("%s, ", tmp->heredoc[i++]);
		}
		i = 0;
		// printf("\n----------------------------------\n");
		// printf("APPEND \n");
		// while (tmp->out_append_files[i])
		// {
		// 	printf("%s\n", tmp->out_append_files[i++]);
		// }
		i = 0;
		printf("\n----------------------------------\n");
		printf("CMD \n");
		while (tmp->cmd && tmp->cmd[i])
		{
			printf("%s, ", tmp->cmd[i++]);
		}
		printf("\n----------------------------------\n");
		printf("OUTPUT_MODE = %d\n", tmp->output_mode);
		printf("\n----------------------------------\n");
		printf("INPUT_MODE = %d\n", tmp->input_mode);
		printf("\n*********************************\n\n\n\n\n\n\n\n");
		tmp = tmp->next;
	}
}
