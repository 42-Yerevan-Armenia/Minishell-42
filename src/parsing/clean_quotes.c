/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 16:32:24 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/22 20:34:06 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_quotes(char *arr)
{
	int i;
	int count;

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

int	clean_quotes(char ***arr)
{
	int i;
	char **res = *arr;
	int j;
	int k;
	char *tmp;

	if (arr == NULL)
		return (0);
	i = 0;
	while (res[i])
	{
		j = 0;
		k = 0;
		tmp = malloc(ft_strlen(res[i]) - count_quotes(res[i]) + 1);
		while (res[i][j])
		{
			if (!ft_strchr(QUOTES, res[i][j]))
				tmp[k++] = res[i][j];
			j++;
		}
		tmp[k] = '\0';
		free_arr(&res[i]);
		res[i] = tmp;
		i++;
	}
	return (0);
}