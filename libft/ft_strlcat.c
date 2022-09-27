/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:24:20 by vaghazar          #+#    #+#             */
/*   Updated: 2022/03/20 13:33:43 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	de;
	size_t	sr;

	i = 0;
	j = 0;
	while (dest[j] != '\0')
		j++;
	de = j;
	sr = ft_strlen(src);
	if (size == 0 || size <= de)
	{
		return (sr + size);
	}
	while (src[i] != '\0' && i < size - de - 1)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (de + sr);
}
