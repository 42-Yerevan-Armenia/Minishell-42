/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:27:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/05/23 13:23:45 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int	find_first(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (set[++j] && s1[i])
	{
		if (s1[i] == set[j] && set[j] != '\0')
		{
			j = -1;
			i++;
		}
	}
	return (i);
}

int	find_last(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	count;

	i = ft_strlen(s1) - 1;
	j = -1;
	count = 0;
	while (set[++j] && s1[i])
	{
		if (s1[i] == set[j] && set[j] != '\0')
		{
			j = -1;
			i--;
			count++;
		}
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	int		first;
	int		last;

	if (s1 && set)
	{
		first = find_first(s1, set);
		last = find_last(s1, set);
		ptr = ft_substr(s1, first, ft_strlen(s1) - first - last);
		return (ptr);
	}
	else
		return (ft_strdup(s1));
	return (0);
}
