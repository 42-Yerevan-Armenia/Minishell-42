/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:59:27 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/13 20:01:55 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_info(t_parse *parser)
{
	int	i;
	t_node *tmp = parser->data->cmd_line->head;

	i = 0;
	printf("\n----------------------------------\n");
	printf("IN_FILES \n");
	while (tmp->in_files[i])
	{
		printf("%s\n", tmp->in_files[i++]);
	}
	printf("\n----------------------------------\n");
	i = 0;
	printf("\n----------------------------------\n");
	printf("OUT_FILES \n");
	while (tmp->out_files[i])
	{
		printf("%s\n", tmp->out_files[i++]);
	}
	printf("\n----------------------------------\n");
	i = 0;
	printf("\n----------------------------------\n");
	printf("HEREDOC \n");
	while (tmp->heredoc[i])
	{
		printf("%s\n", tmp->heredoc[i++]);
	}
	printf("\n----------------------------------\n");
	i = 0;
	printf("\n----------------------------------\n");
	printf("APPEND \n");
	while (tmp->out_append_files[i])
	{
		printf("%s\n", tmp->out_append_files[i++]);
	}
	printf("\n----------------------------------\n");
	i = 0;
	printf("\n----------------------------------\n");
	printf("CMD \n");
	if (tmp->cmd[i])
	{
		printf("%s\n", tmp->cmd[i++]);
	}
	printf("\n----------------------------------\n");
	printf("OUTPUT_MODE = %d\n", tmp->output_mode);
	printf("\n----------------------------------\n");
	printf("INPUT_MODE = %d\n", tmp->input_mode);
	printf("\n----------------------------------\n");
}
