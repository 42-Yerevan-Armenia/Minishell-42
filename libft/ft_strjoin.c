/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:22:45 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/08 20:13:51 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*ptr;
// 	char	*ptr1;

// 	ptr = (char *) malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
// 	if (ptr == 0)
// 		return (0);
// 	ptr1 = ptr;
// 	if (!ptr)
// 		return (0);
// 	while (*s1 != '\0')
// 		*ptr++ = *s1++;
// 	while (*s2 != '\0')
// 		*ptr++ = *s2++;
// 	*ptr = '\0';
// 	return (ptr1);
// }
int	free_arr(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	return (1);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*ptr;
	char	*ptr1;
	char	*arr_to_free;

	arr_to_free = s1;
	ptr = (char *) malloc(ft_strlen(s1) + ft_strlen((char *)s2) + 1);
	if (ptr == 0)
		return (0);
	ptr1 = ptr;
	while (s1 && *s1 != '\0')
		*ptr++ = *s1++;
	while (s2 && *s2 != '\0')
		*ptr++ = *s2++;
	*ptr = '\0';
	free_arr(arr_to_free);
	return (ptr1);
}
