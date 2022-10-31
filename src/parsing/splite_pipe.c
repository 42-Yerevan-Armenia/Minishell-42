/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:55:05 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/31 12:54:18 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_pipe(t_parse *parser)
{
	char	**tmp;
	int		t;
	int		i;
	int		j;
	int		k;

	tmp = parser->spl_qutoes;
	parser->l_arr = 2;
	parser->spl_pipe = malloc(sizeof(char *) * (parser->l_arr + 1));
	if (parser->spl_pipe == NULL && !ft_perror("minishell: "))
		exit (1);
	fill_null((void *)&parser->spl_pipe, parser->l_arr + 1);
	init_zero(&i, &j, &k, NULL);
	while (tmp[i])
	{
		while ((tmp[i] && (tmp[i][0] == '\'' || tmp[i][0] == '"')))
		{
			if (parser->l_arr == k)
				parser->spl_pipe = resize_arr(parser->spl_pipe, &parser->l_arr);
			parser->spl_pipe[k++] = ft_strdup(tmp[i++]);
		}
		while (tmp[i] && tmp[i][j])
		{
			t = j;
			while (tmp[i][j] && tmp[i][j] != '|')
				j++;
			if (j == 0 && tmp[i][j] == '|')
			{
				if (parser->l_arr == k)
					parser->spl_pipe = resize_arr(parser->spl_pipe, &parser->l_arr);
				parser->spl_pipe[k++] = ft_strdup("|");
			}
			else
			{
				if (parser->l_arr == k)
					parser->spl_pipe = resize_arr(parser->spl_pipe, &parser->l_arr);
				parser->spl_pipe[k++] = ft_substr(tmp[i], t, j - t);
				if (tmp[i][j] == '|')
				{
					if (parser->l_arr == k)
						parser->spl_pipe = resize_arr(parser->spl_pipe, &parser->l_arr);
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
