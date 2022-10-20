/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:45:18 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/20 19:44:22 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_replace(t_parse	*parser, char *src, int *j, char *k_ptr)
{
	char	*dest;
	int		place_to_cont;
	int		k;
	char	*res;
	char	*value;
	
	value = get_val(parser->data->env->head, parser->key);
	res = malloc(sizeof(char) * (ft_strlen(src)
		- ft_strlen( parser->key) + ft_strlen(value)) + 1);
	if (!res && !ft_perror("minishell"))
		return (NULL);
		// printf("key = %s\n", parser->key);
		// printf("value = %s\n", value);
	dest = res;
	k = 0;
	*j = 0;
	// printf("k_ptr = %s\n", k_ptr);
	// printf("k_ptr = %p\n", k_ptr);
	while (src[*j])
	{
		// printf("*j = %d\n", *j);
		if (&src[*j] == k_ptr && ++(*j))
		{
			// printf("*j = %d\n", *j);
			while (value && value[k])
				*dest++ = value[k++];
			place_to_cont = *j + ft_strlen(value) - 1;
			*j = (*j + ft_strlen(parser->key));
			// printf("*j = %d\n", *j);
			// printf("ft_strlen(parser->key) = %d\n", ft_strlen(parser->key));
			// printf("dest = %s\n", dest - k);
		}
		if (src[*j]/* && printf("%c %d\n", src[*j], src[*j])*/)
			*dest++ = src[(*j)++];
	}
	*j = place_to_cont;
	*dest = '\0';
	free_arr(&src);
	free_arr(&parser->key);
	printf("res = %s\n", res);
	return (res);
}
