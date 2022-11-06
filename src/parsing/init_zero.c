/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_zero.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:29:14 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/06 10:57:19 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_zero(int *ptr1, int *ptr2, int *ptr3, int *ptr4)
{
	if (ptr1)
		*ptr1 = 0;
	if (ptr2)
		*ptr2 = 0;
	if (ptr3)
		*ptr3 = 0;
	if (ptr4)
		*ptr4 = 0;
	return (0);
}
