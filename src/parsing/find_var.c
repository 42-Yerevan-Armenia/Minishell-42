/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:44:23 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/11 09:43:27 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//  echo $"HOME"
int	is_herdoc(char *ptr_sign, char	*start, int i, char *next_arr)
{
	if (&ptr_sign[i] != start)
	{
		i--;
		while (&ptr_sign[i] != start && ft_strchr(SPACES, ptr_sign[i]))
			i--;
		if (&ptr_sign[i] != start && ptr_sign[i] == '<'
			&& ptr_sign[i - 1] == '<')
			return (1);
	}
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

static char	*find_var_helper(char *src, char **ptr, int j, char *next)
{
	int		len;
	int		i;
	char	*res;

	init_zero(&len, &i, NULL, NULL);
	res = NULL;
	while (src[j])
	{
		if (src[j] == '$' && !is_herdoc(src + j, src, i, next))
		{
			*ptr = &src[j++];
			if (src[j] == '?' && ++j)
				len++;
			else
				while (src[j] && (ft_isalnum(src[j]) || src[j] == '_') && ++j)
					len++;
			res = malloc(sizeof(char) * len + 1);
			if (!res && !ft_perror("minishell: "))
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
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!src)
		return (NULL);
	return (find_var_helper(src, ptr, j, next));
}
