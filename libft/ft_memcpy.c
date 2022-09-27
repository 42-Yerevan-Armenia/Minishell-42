/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:26:34 by vaghazar          #+#    #+#             */
/*   Updated: 2022/03/17 21:26:36 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*ptr;
	const char	*ptr1;
	int			i;

	ptr = dest;
	ptr1 = src;
	i = 0;
	if (ptr < ptr1)
	{
		while (n-- > 0)
		{
			ptr[i] = ptr1[i];
			i++;
		}
	}
	else
	{
		while (n-- > 0)
			ptr[n] = ptr1[n];
	}
	return (dest);
}
