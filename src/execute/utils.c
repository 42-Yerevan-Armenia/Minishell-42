/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 09:21:55 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/17 08:47:50 by vaghazar         ###   ########.fr       */
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
	// free_all()
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
	res[0] = ft_strdup("cd");
	res[1] = ft_strdup("echo");
	res[2] = ft_strdup("env");
	res[3] = ft_strdup("exit");
	res[4] = ft_strdup("export");
	res[5] = ft_strdup("pwd");
	res[6] = ft_strdup("unset");
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
