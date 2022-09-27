/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:47:39 by vaghazar          #+#    #+#             */
/*   Updated: 2022/03/26 20:48:23 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	free_arr(char *str)
{
	if (str != NULL)
	{
		free(str);
		str = NULL;
	}
	return (1);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
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

char	*ft_strdup(char *src, char *str_for_free)
{
	int		i;
	char	*ptr;

	i = 0;
	while (src[i])
		i++;
	ptr = malloc(i + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (src[i])
	{
		ptr[i] = src[i];
		i++;
	}
	free_arr(str_for_free);
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_substr(char const *src, unsigned int start, size_t len)
{
	char	*ptr;
	int		i;
	size_t	s_len;

	s_len = ft_strlen(src + start);
	if (start >= (unsigned int)ft_strlen(src))
	{
		ptr = malloc(sizeof(char));
		ptr[0] = '\0';
		return (ptr);
	}
	if (s_len < len)
		len = s_len;
	ptr = (char *) malloc(len + 1);
	if (ptr == 0)
		return (0);
	i = 0;
	while (src[start] && len--)
		ptr[i++] = src[start++];
	ptr[i] = '\0';
	return (ptr);
}
