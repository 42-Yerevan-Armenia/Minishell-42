/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:21:20 by vaghazar          #+#    #+#             */
/*   Updated: 2025/02/22 19:59:26 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	valid_flag(char **s, int *i)
{
	int	j;

	if (!s || !*s)
		return (-1);
	j = 0;
	if (s[*i][j] != '-')
		return (1);
	while (s[*i])
	{
		j = 0;
		if (s[*i][j] == '-' && s[*i][j + 1] == 'n' && ++j)
		{
			while (s[*i][j])
			{
				if (s[*i][j] != 'n')
					return (0);
				j++;
			}
		}
		else
			break ;
		(*i)++;
	}
	return (0);
}

int	echo(t_spl_pipe *node, char **args)
{
	int	flag;
	int	i;

	i = 1;
	flag = 0;
	if (arr_double_len(args) != 1)
	{
		if (!valid_flag(args, &i) && i != 1)
			flag = 1;
		while (args[i])
		{
			ft_putstr_fd(args[i], node->fd_out, FREE_OFF);
			if (args[i + 1])
				write(node->fd_out, " ", 1);
			i++;
		}
	}
	if (flag == 0)
		write(node->fd_out, "\n", 1);
	return (0);
}
