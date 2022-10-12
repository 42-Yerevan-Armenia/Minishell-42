/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_null.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:46:08 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/12 19:31:08 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_null(char **ptr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ptr[i++] = NULL;
	}
	if (len == 0)
		ptr[0] = NULL;
	return (0);
}