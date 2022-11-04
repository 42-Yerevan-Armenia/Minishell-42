/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:59:18 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/04 10:08:45 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_unexpected_token(char *s, int i)
{
	while (s[i] && ft_strchr(SPACES, s[i]))
		i++;
	if (s[i] == '\0')
	{
		ft_putendl_fd(ft_charjoin(ft_strjoin_1(ft_charjoin(UNEXPECTED_TOKEN, '`', FREE_OFF), "newline"), '\'', FREE_ON), 2, FREE_ON);
		return (START_RD_LN);
	}
	if (ft_strchr(UNEXPECTED_RED, s[i]))
	{
		ft_putendl_fd(ft_charjoin(ft_charjoin(ft_charjoin(UNEXPECTED_TOKEN, '`', FREE_OFF), s[i], FREE_ON), '\'', FREE_ON), 2, FREE_ON);
		return (START_RD_LN);
	}
	return (0);
}

static int valid_redircet(char	*s)
{
	int	i;

	i = 0;
	while (s[i] && !ft_strchr(UNEXPECTED, s[i]))
	{
		if (s[i] == '>' && s[i + 1] == '>' && ++i && ++i)
		{
			if (find_unexpected_token(s, i) == START_RD_LN)
				return (START_RD_LN);
		}
		if (s[i] == '<' && s[i + 1] == '<' && ++i && ++i)
		{
			if (find_unexpected_token(s, i) == START_RD_LN)
				return (START_RD_LN);
		}
		if (s[i] == '<' && ++i)
		{
			if (find_unexpected_token(s, i) == START_RD_LN)
				return (START_RD_LN);
		}
		if (s[i] == '>' && ++i)
		{
			if (find_unexpected_token(s, i) == START_RD_LN)
				return (START_RD_LN);
		}
		i++;
	}
	return (0);
}

int	unexpected_tokens(t_parse *parser)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = parser->rd_ln;
	while (tmp[i])
	{
		if (valid_redircet(tmp + i) == START_RD_LN)
			return (START_RD_LN);
		while (tmp[i] && ft_strchr(SPACES, tmp[i]))
			i++;
		if (tmp[i] && ft_strchr(UNEXPECTED, tmp[i]))
		{
			if (tmp[i] == '\0' || ft_strchr(UNEXPECTED, tmp[i]))
			{
				ft_putendl_fd(ft_charjoin(ft_charjoin(ft_charjoin(UNEXPECTED_TOKEN, '`', FREE_OFF), tmp[i], FREE_ON), '\'', FREE_ON), 2, FREE_ON);
				return (START_RD_LN);
			}
		}
		else
		{
			while (tmp[i] && !ft_strchr(UNEXPECTED, tmp[i]))
				++i;
			if (tmp[i] && ft_strchr(UNEXPECTED, tmp[i]) && ++i)
			{
				while (tmp[i] && ft_strchr(SPACES, tmp[i]))
					i++;
				if (tmp[i] == '\0')
				{
					ft_putendl_fd(ft_charjoin(ft_strjoin_1(ft_charjoin(UNEXPECTED_TOKEN, '`', FREE_OFF), "newline"), '\'', FREE_ON), 2, FREE_ON);
					return (START_RD_LN);
				}
			}
		}
		if (tmp[i] && !ft_strchr(UNEXPECTED, tmp[i]))
			i++;
	}
	return (0);
}
