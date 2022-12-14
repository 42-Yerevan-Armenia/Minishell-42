/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hdoc_qutoes_mode.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 15:36:54 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/29 19:06:17 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_dollar(char *str)
{
	int	count;

	if (str == NULL)
		return (0);
	count = 0;
	while (*str)
	{
		if (*str == '$')
			count++;
		str++;
	}
	return (count);
}

static int	is_herdoc(char *ptr_sign, char	*start)
{
	int	i;

	i = 0;
	if (&ptr_sign[i] != start)
	{
		i--;
		while (&ptr_sign[i] != start && ft_strchr(SPACES, ptr_sign[i]))
			i--;
		while (&ptr_sign[i] != start && ft_strchr(QUOTES, ptr_sign[i]))
			i--;
		while (&ptr_sign[i] != start && ft_strchr(SPACES, ptr_sign[i]))
			i--;
		if (&ptr_sign[i] != start && ptr_sign[i] == '<'
			&& ptr_sign[i - 1] == '<')
			return (1);
	}
	return (0);
}

char	*put_hdoc_qutoes_mode(char **str)
{
	int		i;
	int		j;
	char	*res;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = *str;
	res = malloc(ft_strlen(tmp) + count_dollar(tmp) + 1);
	if (res == NULL)
		exit (1);
	while (tmp[i])
	{
		res[j++] = tmp[i];
		if (tmp[i] == '$' && is_herdoc(tmp + i, tmp))
		{
			res[j++] = 1;
		}
		i++;
	}
	res[j] = '\0';
	free_arr(str);
	*str = res;
	return (res);
}
