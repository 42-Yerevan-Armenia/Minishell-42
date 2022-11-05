/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:20:05 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/05 20:21:27 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(t_parse *parser)
{
	int		i;
	char	*tmp;
	char	c;

	i = 0;
	tmp = parser->rd_ln;
	while (tmp[i])
	{
		if (tmp[i] == '\'' || tmp[i] == '"')
		{
			c = tmp[i++];
			if (tmp[i] == '\0' && ft_putstr_fd("minishell: syntax error near\
 unexpected token `newline'\n", 2, FREE_OFF))
				return (1);
			while (tmp[i] && tmp[i] != c)
				i++;
			printf("barev\n");
			if (tmp[i] != c && ft_putstr_fd("minishell: syntax error near\
 unexpected token `newline'\n", 2, FREE_OFF))
				return (1);
		}
		i++;
	}
	return (0);
}
