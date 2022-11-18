/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:41:52 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/18 16:52:28 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_elem	*count_elem(char *str)
{
	int		i;
	t_elem	*res;

	i = 0;
	res = malloc(sizeof(t_elem));
	if (!res && !ft_perror("🔻minishell: "))
		exit (1);
	res->hdoc = 1;
	res->out_a_f = 1;
	res->rdc = 1;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && ++i && ++i)
			(res->hdoc)++;
		if (str[i] == '>' && str[i + 1] == '>' && ++i && ++i)
			(res->rdc)++;
		if (str[i] == '<' && ++i)
			(res->rdc)++;
		if (str[i] == '>' && ++i)
			(res->rdc)++;
		if (str[i] && !ft_strchr(HANDLE, str[i]))
			i++;
	}
	return (res);
}
