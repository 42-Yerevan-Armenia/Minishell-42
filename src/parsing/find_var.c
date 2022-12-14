/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:44:23 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/29 19:04:44 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid(char *ptr_sign, char *next_arr)
{
	int	i;

	i = 0;
	if (*(ptr_sign + 1) == UNPRINTABLE)
		return (1);
	i = 1;
	while (ptr_sign[i] && ft_strchr(SPACES, ptr_sign[i]))
		i++;
	if (ptr_sign[i] == '"' || ptr_sign[i] == '\'')
		return (1);
	if (ptr_sign[i] == '\0')
	{
		if (next_arr && (next_arr[0] == '\'' || next_arr[0] == '"'))
			return (0);
		return (1);
	}
	return (0);
}

static void	find_var_helper_helper(char *src, int *j, int *len)
{
	if (src[*j] == '?' && ++(*j))
		(*len)++;
	else
		while (src[*j] && (ft_isalnum(src[*j]) || src[*j] == '_') && ++(*j))
			(*len)++;
}

static char	*find_var_helper(char *src, char **ptr, int j, char *next)
{
	int		len;
	int		i;
	char	*res;

	init_zero(&len, &i, NULL, NULL);
	res = NULL;
	while (src[j])
	{
		if (src[j] == '$' && !is_valid(src + j, next))
		{
			*ptr = &src[j++];
			find_var_helper_helper(src, &j, &len);
			res = malloc(sizeof(char) * len + 1);
			if (!res && !ft_perror("🔻minishell: "))
				exit(1);
			while (len)
				res[i++] = src[j - len--];
			break ;
		}
		j++;
	}
	if (res)
		res[i] = '\0';
	return (res);
}

char	*find_var(char *src, char **ptr, int j, char *next)
{
	if (!src)
		return (NULL);
	return (find_var_helper(src, ptr, j, next));
}
