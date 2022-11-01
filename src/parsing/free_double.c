/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:42:52 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/01 11:26:54 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_double(void ***ptr)
{
	int	i;

	i = 0;
	if (*ptr == NULL)
		return (0);
	while ((*ptr) && ((*ptr))[i])
	{
		free(((*ptr))[i]);
		((*ptr))[i++] = NULL;
	}
	if (((*ptr)))
		free(((*ptr)));
	((*ptr)) = NULL;
	return (0);
}
