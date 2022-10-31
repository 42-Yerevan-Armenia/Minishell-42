/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:44:23 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/31 11:40:59 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_var_helper(char *src, char **res, char **ptr, int j)
{
	int	len;
	int	i;

	init_zero(&len, &i, NULL, NULL);
	while (src[j])
	{
		if (src[j] == '$')
		{
			*ptr = &src[j++];
			if (src[j] == '?' && ++j)
				len++;
			else
				while (src[j] && (ft_isalnum(src[j]) || src[j] == '_') && ++j)
					len++;
			(*res) = malloc(sizeof(char) * len + 1);
			if (!(*res) && !ft_perror("minishell: "))
				exit(1);
			while (len)
				(*res)[i++] = src[j - len--];
			break ;
		}
		j++;
	}
	if ((*res))
		(*res)[i] = '\0';
}

char	*find_var(char *src, char **ptr, int j)
{
	int		i;
	char	*res;
	int		len;

	i = 0;
	len = 0;
	res = NULL;
	if (!src)
		return (NULL);
	find_var_helper(src, &res, ptr, j);
	return (res);
}
