/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:33:52 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/22 16:33:59 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	check_syntax(t_parse *parser)
// {
// 	char	*tmp;
// 	int		i;

// 	tmp = parser->rd_ln;
// 	i = 0;
// 	while (tmp[i])
// 	{
// 		if (tmp[i] == '|')
// 		{
// 			if (tmp[i + 1] == '|' || tmp[i + 1] == '\0')
// 				return (1);
// 			while (tmp[i])
// 			{
				
// 				i++;
// 			}
			
// 		}
// 		i++;
// 	}
// 	return (0);
// }