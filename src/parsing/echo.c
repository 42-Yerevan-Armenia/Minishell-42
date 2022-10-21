/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:21:20 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/19 10:21:34 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_data *data, char **args)
{
	int	flag;
	int	i;

	i  = 1;
	flag  = 0;
	if (!args || !*args)
		return (1);
	while (!ft_strcmp(args[i], "-n") && ++i)
		flag = 1;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		i++;
		if (args[i])
			write(1, " ", 1);
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}
