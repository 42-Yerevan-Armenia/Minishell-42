/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:46:10 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/09 10:27:33 by vaghazar         ###   ########.fr       */
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
	tmp[*l_arr] = NULL;
	if (!tmp && printf("Can't allocate memory."))
		exit (1);
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
	// printf("||||||||||||||||\\\n");
	// while (tmp[i])
	// {
	// 	printf("%s\n", tmp[i++]);
	// }
	// printf("=-----------------\n");
	// printf("tmp[0] = %s\n", tmp[0]);
	return (tmp);
}