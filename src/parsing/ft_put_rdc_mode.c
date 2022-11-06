/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_rdc_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 10:54:39 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/06 11:46:27 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_put_rdc_mode(char **s, int mode)
{
	int		i;
	char	*res;
	char	*tmp;

	if (*s == NULL)
		return (1);
	i = 0;
	tmp = *s;
	res = malloc(ft_strlen(*s) + 3);
	while (*tmp)
		res[i++] = *tmp++;
	res[i++] = '\0';
	res[i++] = mode;
	res[i] = '\0';
	*s = res;
	return (0);
}

int	ft_get_rdc_mode(char *s)
{
	int		i;

	if (s == NULL || *s == '\0' || !ft_strcmp(s, BAD_RDR))
		return (1);
	i = 0;
	while (s[i])
		i++;
	i++;
	if (s[i] == OUT_FILES)
		return (O_TRUNC);
	if (s[i] == APPEND_FILES)
		return (O_APPEND);
	return (s[i]);
}
