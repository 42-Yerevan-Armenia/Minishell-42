/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:51:17 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/31 12:26:20 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_join(t_parse *parser)
{
	int	i;
	int	j;
	int	k;

	init_zero(&i, &k, &j, NULL);
	parser->l_arr = 2;
	parser->join_pipe = malloc(sizeof(char *) * (parser->l_arr + 1));
	if (parser->join_pipe == NULL && !ft_perror("minishell: "))
		exit (1);
	fill_null((void *)&parser->join_pipe, parser->l_arr + 1);
	while (parser->spl_pipe && parser->spl_pipe[i] != NULL)
	{
		while (parser->spl_pipe && parser->spl_pipe[i]
			&& parser->spl_pipe[i][0] != '|')
		{
			parser->join_pipe[k] = ft_strjoin_1(parser->join_pipe[k],
					parser->spl_pipe[i++]);
		}
		k++;
		if (parser->l_arr == k)
			parser->join_pipe = resize_arr(parser->join_pipe, &parser->l_arr);
		if (parser->spl_pipe[i])
			i++;
	}
	return (0);
}
