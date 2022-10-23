/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:46:10 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/23 09:35:14 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**resize_arr(char **arr, int *l_arr)
{
	char	**tmp;
	int i;

	i = -1;
	*l_arr *= 2;
	tmp = malloc(sizeof(char *) * (*l_arr + 1));
	if (!tmp && !ft_perror("minishell"))
		exit (1);
	fill_null((void *)&tmp, *l_arr + 1);
	while (arr[++i])
		tmp[i] = ft_strdup(arr[i]);
	while (i < (*l_arr / 2))
	{
		tmp[i++] = NULL;
	}
	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
	i = 0;
	return (tmp);
}