/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:21:20 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/01 13:56:16 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_flag(char *s, int *i)
{
	int	j;

	j = 0;
	if (!s)
		return (-1);
	if (s[j] == '-' && s[j + 1] == 'n' && ++j)
	{
		while (s[j])
		{
			if (s[j] != 'n')
				return (1);
			j++;
		}
	}
	else
		return (1);
	(*i)++;
	return (0);
}

int	echo(char **args)
{
	int	flag;
	int	i;
	int	j;

	j = 0;
	i = 1;
	flag = 0;
	if (arr_double_len(args) != 1)
	{
		while (args[i])
		{
			while (((!valid_flag(args[i], &i))))
				flag = 1;
			ft_putstr_fd(args[i], 1, FREE_OFF);
			if (args[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}
