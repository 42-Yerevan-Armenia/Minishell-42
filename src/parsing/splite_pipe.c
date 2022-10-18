/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:55:05 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/17 21:18:44 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  "<<hd'" |kd|dd|" dj $'* ><kkk -ld sdf"  rt' pwd|"$ho'|M

int split_pipe(t_parse *parser)
{
	char	**tmp;
	int		l_arr;
	int		t;
	int		i;
	int		j;
	int		k;

	tmp = parser->spl_qutoes;
	l_arr = 2;
	parser->spl_pipe = malloc(sizeof(char *) * (l_arr + 1));
	if (parser->spl_pipe == NULL)
		return (0);
	fill_null(&parser->spl_pipe, l_arr + 1);
	parser->spl_pipe[l_arr] = NULL;
	i = 0;
	j = 0;
	k = 0;
	while (tmp[i])
	{
		while ((tmp[i] && (tmp[i][0] == '\'' || tmp[i][0] == '"')))
		{
			if (l_arr == k)
					parser->spl_pipe = resize_arr(parser->spl_pipe, &l_arr);
			parser->spl_pipe[k++] = ft_strdup(tmp[i++]);
		}
		while (tmp[i] && tmp[i][j])
		{
			t = j;
			while (tmp[i][j] && tmp[i][j] != '|')
				j++;
			if (j == 0 && tmp[i][j] == '|')
			{
				if (l_arr == k)
					parser->spl_pipe = resize_arr(parser->spl_pipe, &l_arr);
				parser->spl_pipe[k++] = ft_strdup("|");
			}
			else
			{
				if (l_arr == k)
					parser->spl_pipe = resize_arr(parser->spl_pipe, &l_arr);
				parser->spl_pipe[k++] = ft_substr(tmp[i], t, j - t);
				if (tmp[i][j] == '|')
				{
					if (l_arr == k)
						parser->spl_pipe = resize_arr(parser->spl_pipe, &l_arr);
					parser->spl_pipe[k++] = ft_strdup("|");
				}
			}
			if (tmp[i][j] != '\0')
				j++;
		}
		j = 0;
		if (tmp[i])
			i++;
	}
	return (0);
}
