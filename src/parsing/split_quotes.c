/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 09:16:10 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/14 18:15:07 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_quotes_helper(t_parse *parser, t_vars *v, char *tmp)
{
	while (tmp[v->i] && (tmp[v->i] != '\'' && tmp[v->i] != '"'))
		v->i++;
	if (v->t != v->i
		&& !resize_arr(&parser->spl_qutoes, &parser->l_arr, v->k))
		parser->spl_qutoes[v->k++] = ft_substr(tmp, v->t, v->i - v->t);
	if (tmp[v->i] && (tmp[v->i] == '\'' || tmp[v->i] == '"'))
	{
		v->j = v->i;
		v->c = tmp[v->i++];
		while (tmp[v->i] && (tmp[v->i] != v->c && tmp[v->i] != v->c))
			v->i++;
		resize_arr(&parser->spl_qutoes, &parser->l_arr, v->k);
		parser->spl_qutoes[v->k++] = ft_substr(tmp, v->j, v->i - v->j + 1);
	}
}

int	split_quotes(t_parse *parser)
{
	char	*tmp;
	t_vars	v;

	tmp = parser->rd_ln;
	parser->l_arr = 2;
	init_vars(&v, 0, 0, 0);
	parser->spl_qutoes = malloc(sizeof(char *) * (parser->l_arr + 1));
	if (!parser->spl_qutoes && !ft_perror("minishell: "))
		exit(1);
	fill_null((void *)&parser->spl_qutoes, parser->l_arr + 1);
	while (tmp[v.i])
	{
		v.t = v.i;
		split_quotes_helper(parser, &v, tmp);
		if (tmp[v.i])
			v.i++;
	}
	return (0);
}
