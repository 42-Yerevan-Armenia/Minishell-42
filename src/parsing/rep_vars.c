/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:56:01 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/06 11:48:07 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rep_vars(t_parse *parser, int flag)
{
	int		i;
	int		j;
	char	**tmp;
	char	*ptr_var;

	i = -1;
	j = 0;
	tmp = parser->spl_qutoes;
	if (flag == HEREDOC)
		tmp = parser->hered_res;
	while (tmp[++i])
	{
		if (tmp[i][0] != '\'' || flag == HEREDOC)
		{
			while (tmp[i][j])
			{
				parser->key = find_var(tmp[i], &ptr_var, j);
				if (!parser->key)
					break ;
				tmp[i] = ft_replace(parser, tmp[i], &j, ptr_var);
			}
		}
		j = 0;
	}
}
