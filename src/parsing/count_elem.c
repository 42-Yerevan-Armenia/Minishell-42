/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:41:52 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/12 21:18:22 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_elem	*count_elem(char *str)
{
	int	i;
	int count;
	t_elem	*res;

	i = 0;
	res = malloc(sizeof(t_elem));
	res->heardoc = 1;
	res->out_append_files = 1;
	res->out_file = 1;
	res->in_file = 1;
	while (str[i])
	{
		if (str[i] == '<' && str[i] == '<' && ++i && ++i)
			res->heardoc++;
		if (str[i] == '>' && str[i] == '>' && ++i && ++i)
			res->out_append_files++;
		if (str[i] == '<' && ++i && printf("es em\n"))
			res->in_file++;
		if (str[i] == '>' && ++i && printf("es em\n"))
			res->out_file++;
		else
			i++;
	}
	printf("iii = %d\n", i);
	return (res);
}