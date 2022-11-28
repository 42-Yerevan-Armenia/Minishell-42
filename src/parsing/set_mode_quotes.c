/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mode_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:13:28 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/27 15:03:34 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_quotes(char *arr)
{
	int		i;
	int		count;

	if (arr == NULL)
		return (0);
	i = 0;
	count = 0;
	while (arr[i])
	{
		if (ft_strchr(QUOTES, arr[i]))
			count++;
		i++;
	}
	return (count);
}

char	*clean_unprintable(char *arr)
{
	int		i;
	int		j;
	char	*res;

	if (arr == NULL)
		return (0);
	res = malloc(sizeof(char) * (ft_strlen(arr) + 1));
	if (res == NULL && !ft_perror("minishell: malloc: "))
		exit (1);
	i = 0;
	j = 0;
	while (arr[j])
	{
		if (arr[j] != UNPRINTABLE)
			res[i++] = arr[j++];
		else
			j++;
	}
	res[i] = '\0';
	free_arr(&arr);
	return (res);
}

char	*set_mode_quotes(char *s)
{
	int		i;
	char	*res;
	int		j;

	j = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s) + count_quotes(s) + 10));
	if (res == NULL && !ft_perror("minishell: malloc: "))
		exit (1);
	while (s[i])
	{
		if (ft_strchr(QUOTES, s[i]))
		{
			res[j++] = s[i++];
			res[j++] = UNPRINTABLE;
		}
		if (s[i] == '\0')
			break ;
		res[j++] = s[i++];
	}
	res[j] = '\0';
	return (res);
}
