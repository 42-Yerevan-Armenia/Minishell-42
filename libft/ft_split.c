/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:31:34 by vaghazar          #+#    #+#             */
/*   Updated: 2022/04/17 15:34:24 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	mal_free(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	if (str)
		free(str);
	return (1);
}

static int	counting_word(char const *s, char c)
{
	int	index;
	int	count;

	count = 0;
	index = 0;
	if (!s && !c)
		return (0);
	while (s[index] != '\0')
	{
		if (s[index] == c && index != 0 && s[index + 1] != c)
			count++;
		index++;
	}
	if (s[index - 1] != c)
		count += 1;
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**splited;
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	splited = malloc(8 * counting_word(s, c) + 1);
	if (!splited)
		return (0);
	while (s[i[0]] != '\0')
	{
		i[1] = i[0];
		while (s[i[0]] != '\0' && s[i[0]] != c)
			i[0]++;
		if (!((i[0] == 0 && s[i[0]] == c)))
		{
			splited[i[2]] = ft_substr(s, i[1], i[0] - i[1]);
			if (!splited[i[2]++] && mal_free(splited))
				return (0);
		}
		while (s[i[0]] != '\0' && s[i[0]] == c)
			i[0]++;
	}
	splited[i[2]] = NULL;
	return (splited);
}
