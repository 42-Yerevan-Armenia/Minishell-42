/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:45:18 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/01 08:31:58 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_replace_helper(t_parse *parser, char *src, char **value, int *j)
{
	char	*res;

	*value = get_val(parser->data->env->head, parser->key);
	res = malloc(sizeof(char) * (ft_strlen(src) - ft_strlen(parser->key)
				+ ft_strlen(*value)) + 1);
	if (!res && !ft_perror("minishell: "))
		exit (1);
	*j = 0;
	return (res);
}

char	*ft_replace(t_parse *parser, char *src, int *j, char *k_ptr)
{
	int		place_to_cont;
	int		k;
	char	*res;
	char	*value;
	int		i;

	res = ft_replace_helper(parser, src, &value, j);
	init_zero(&k, &i, NULL, NULL);
	while (src[*j])
	{
		if (&src[*j] == k_ptr && ++(*j))
		{
			while (value && value[k])
				res[i++] = value[k++];
			place_to_cont = *j + ft_strlen(value) - 1;
			*j = (*j + ft_strlen(parser->key));
		}
		if (src[*j])
			res[i++] = src[(*j)++];
	}
	*j = place_to_cont;
	res[i] = '\0';
	free_arr(&src);
	free_arr(&parser->key);
	return (res);
}
