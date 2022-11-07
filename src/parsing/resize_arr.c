/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:46:10 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/07 10:25:13 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	free_double_r(char ***ptr)
{
	int	i;

	i = 0;
	while ((*ptr)[i])
	{
		free((*ptr)[i]);
		(*ptr)[i] = NULL;
		i++;
	}
	free(*ptr);
	*ptr = NULL;
	return (0);
}

int	resize_arr(char ***arr, int *l_arr, int k)
{
	char	**tmp;
	int		i;

	if (*l_arr != k)
		return (0);
	i = -1;
	*l_arr *= 2;
	tmp = malloc(sizeof(char *) * (*l_arr + 1));
	if (!tmp && !ft_perror("minishell: "))
		exit(1);
	fill_null((void *)&tmp, *l_arr + 1);
	while ((*arr)[++i])
		tmp[i] = ft_strdup((*arr)[i]);
	while (i < (*l_arr / 2))
		tmp[i++] = NULL;
	free_double_r(arr);
	*arr = tmp;
	return (0);
}
