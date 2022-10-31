/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 09:16:10 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/31 21:36:45 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_quotes(t_parse *parser)
{
	int		i;
	char	c;
	char	*tmp;
	int		j;
	int		k;
	int		t;

	tmp = parser->rd_ln;
	parser->l_arr = 2;
	k = 0;
	i = 0;
	parser->spl_qutoes = malloc(sizeof(char *) * (parser->l_arr + 1));
	if (!parser->spl_qutoes && !ft_perror("minishell: "))
		exit(1);
	fill_null((void *)&parser->spl_qutoes, parser->l_arr + 1);
	while (tmp[i])
	{
		t = i;
		while (tmp[i] && (tmp[i] != '\'' && tmp[i] != '"'))
			i++;
		if (t != i)
		{
			if (parser->l_arr == k)
				parser->spl_qutoes = resize_arr(parser->spl_qutoes,
												&parser->l_arr);
			parser->spl_qutoes[k++] = ft_substr(tmp, t, i - t);
		}
		if (tmp[i] && (tmp[i] == '\'' || tmp[i] == '"'))
		{
			j = i;
			c = tmp[i++];
			while (tmp[i] && (tmp[i] != c && tmp[i] != c))
				i++;
			if (tmp[i] != c && printf("syntax error invalid quotes\n"))
				return (1);
			if (parser->l_arr == k)
				parser->spl_qutoes = resize_arr(parser->spl_qutoes,
												&parser->l_arr);
			parser->spl_qutoes[k++] = ft_substr(tmp, j, i - j + 1);
		}
		if (tmp[i])
			i++;
	}
	return (0);
}