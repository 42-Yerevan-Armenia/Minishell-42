/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:42:52 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/31 21:47:12 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_double(char ***ptr)
{
	int	i;

	i = 0;
		// write(1, "||||||\n", 9);
	printf("ptr  = %d\n", (*ptr));
	if (*ptr == NULL && printf("es em\n"))
		return (0);
	while ((*ptr) && ((*ptr))[i])
	{
		printf("%d\n", (*ptr[i]));
		free(((*ptr))[i]);
		((*ptr))[i++] = NULL;
	}
	if (((*ptr)))
		free(((*ptr)));
	((*ptr)) = NULL;
	return (0);
}
