/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:57:00 by arakhurs          #+#    #+#             */
/*   Updated: 2022/11/24 18:57:35 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	iszero(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (s[i] && (s[i] == '-' || s[i] == '+'))
		i++;
	while (s[i])
	{
		if (s[i] != '0')
			return (0);
		i++;
	}
	return (1);
}

static char	*one_zero_str(char *s)
{
	s[0] = '0';
	s[1] = '\0';
	return (s);
}

static int	numlen(char *s)
{
	int	i;
	int	len;

	if (!s)
		return (0);
	if (iszero(s))
		return (1);
	i = 0;
	len = 0;
	if (s[i] && s[i] == '+')
		i++;
	else if (s[i] && s[i] == '-')
	{
		len++;
		i++;
	}
	while (s[i] == '0')
		i++;
	while (s[i++])
		len++;
	return (len);
}

char	*numstr(char *str)
{
	char	*s;
	int		i;
	int		j;

	s = malloc(numlen(str) + 1);
	if (!s)
		return (NULL);
	if (iszero(str))
		return (one_zero_str(s));
	i = 0;
	j = 0;
	if (str[i] && str[i] == '+')
		i++;
	else if (str[i] && str[i] == '-')
	{
		s[j++] = '-';
		i++;
	}
	while (str[i] == '0')
		i++;
	while (str[i])
		s[j++] = str[i++];
	s[j] = '\0';
	return (s);
}

int	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
		free_arr(&str[i--]);
	return (0);
}
