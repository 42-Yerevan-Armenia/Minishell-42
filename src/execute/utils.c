/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 09:21:55 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/07 20:17:51 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pass_qutoes(int *i, char *str)
{
	char	tmp;

	tmp = str[(*i)++];
	while (str[*i] && str[*i] != tmp)
		(*i)++;
}

int	ft_perror(char *str)
{
	perror(str);
	return (0);
}

int	put_exit_s(t_data *data, int status)
 {
 	data->exit_status = status;
 	return (0);
 }

char	**ft_bultins(void)
{
	char	**res;

	res = malloc(sizeof(char *) * 8);
	fill_null((void *)&res, 8);
	res[0] = "cd";
	res[1] = "echo";
	res[2] = "env";
	res[3] = "exit";
	res[4] = "export";
	res[5] = "pwd";
	res[6] = "unset"; 

	return (res);
}

int	search_builtin(char *s, char **builtins)
{
	int	i;

	i = 0;
	while (builtins[i])
		if (!ft_strcmp(s, builtins[i++]))
			return (1);
	return (0);
}
