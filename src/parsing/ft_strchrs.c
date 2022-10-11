/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 11:47:10 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/11 11:47:20 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchrs(const char *s, const char *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s || !set)
		return (NULL);
	while (s[i])
	{
		while (set[j])
		{
			if (s[i] == set[j])
				return ((char *)&s[i]);
			j++;
		}
		j = 0;
		i++;
	}
	return (NULL);
}