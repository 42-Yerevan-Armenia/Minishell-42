/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:51:17 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/23 09:45:23 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  "<<hd'" |   kd|   dd|" dj $'* ><kkk -ld sdf"  rt' pwd|"$ho'|M

int	pipe_join(t_parse *parser)
{
	int	i;
	int	j;
	int	k;
	int	l_arr;

	i = 0;
	k = 0;
	l_arr = 2;
	j = 0;
	parser->join_pipe = malloc(sizeof(char *) * (l_arr + 1));
	if (parser->join_pipe == NULL && !ft_perror("minishell"))
		return (0);
    fill_null((void *)&parser->join_pipe, l_arr + 1);
	while (parser->spl_pipe && parser->spl_pipe[i] != NULL)
	{
		while (parser->spl_pipe && parser->spl_pipe[i] && parser->spl_pipe[i][0] != '|')
		{
			parser->join_pipe[k] = ft_strjoin(parser->join_pipe[k], parser->spl_pipe[i++]);
		}
		k++;
		if (l_arr == k)
				parser->join_pipe = resize_arr(parser->join_pipe, &l_arr);
		if (parser->spl_pipe[i])
			i++;
	}
	return (0);
}
