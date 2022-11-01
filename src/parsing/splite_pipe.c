/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splite_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:55:05 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/01 09:48:18 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_pipe_helper(t_parse *parser, t_vars *v, char **tmp)
{
	while ((tmp[v->i] && (tmp[v->i][0] == '\'' || tmp[v->i][0] == '"'))
		&& !resize_arr(&parser->spl_pipe, &parser->l_arr, v->k))
		parser->spl_pipe[v->k++] = ft_strdup(tmp[v->i++]);
	while (tmp[v->i] && tmp[v->i][v->j])
	{
		v->t = v->j;
		while (tmp[v->i][v->j] && tmp[v->i][v->j] != '|')
			v->j++;
		if (v->j == 0 && tmp[v->i][v->j] == '|'
			&& !resize_arr(&parser->spl_pipe, &parser->l_arr, v->k))
			parser->spl_pipe[v->k++] = ft_strdup("|");
		else if (!resize_arr(&parser->spl_pipe, &parser->l_arr, v->k))
		{
			parser->spl_pipe[v->k++] = ft_substr(tmp[v->i], v->t, v->j - v->t);
			if (tmp[v->i][v->j] == '|'
				&& !resize_arr(&parser->spl_pipe, &parser->l_arr, v->k))
				parser->spl_pipe[v->k++] = ft_strdup("|");
		}
		if (tmp[v->i][v->j] != '\0')
			v->j++;
	}
	v->j = 0;
}

int	split_pipe(t_parse *parser)
{
	char	**tmp;
	t_vars	v;

	tmp = parser->spl_qutoes;
	parser->l_arr = 2;
	parser->spl_pipe = malloc(sizeof(char *) * (parser->l_arr + 1));
	if (parser->spl_pipe == NULL && !ft_perror("minishell: "))
		exit (1);
	fill_null((void *)&parser->spl_pipe, parser->l_arr + 1);
	init_vars(&v, 0, 0, 0);
	while (tmp[v.i])
	{
		split_pipe_helper(parser, &v, tmp);
		if (tmp[v.i])
			v.i++;
	}
	return (0);
}
