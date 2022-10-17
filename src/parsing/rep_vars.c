/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:56:01 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/17 20:59:39 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	rep_vars(t_parse *parser)
{
	int	i;
	int	j;
	char	**tmp;
	char	*key;
	char	*ptr_var;
	
	if (!parser->spl_qutoes)
		return (1);
	i = 0;
	j = 0;
	ptr_var = NULL;
	tmp = parser->spl_qutoes;
	while (tmp[i])
	{
		if (tmp[i][0] != '\'')
		{
			while (tmp[i][j])
			{
				parser->key = find_var(tmp[i], &ptr_var, j);
				// printf("%s\n", parser->key);
				// printf("%s\n", tmp[i]);
				if (parser->key)
					tmp[i] = ft_replace(parser, tmp[i], &j, ptr_var);
				else
					break;
				// j++;
				// printf(" tmp[i][j] = %c\n", tmp[i][j]);
				// printf(" tmp[i][j] = %d\n", tmp[i][j]);
				// printf("i = %d\n", i);
				// printf("j = %d\n", j);
			}
		}
		j = 0;
		i++;
	}
	return (0);
}