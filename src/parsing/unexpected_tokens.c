/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unexpected_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:59:18 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/07 20:27:37 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_unexpected_token(char *s, int i)
{
	while (s[i] && ft_strchr(SPACES, s[i]))
		i++;
	if (s[i] == '\0')
	{
		ft_putendl_fd(ft_charjoin(ft_strjoin_1(ft_charjoin(UNEXPECTED_TOKEN,
						'`', FREE_OFF), "newline"), '\'', FREE_ON), 2, FREE_ON);
		return (START_RD_LN);
	}
	if (ft_strchr(UNEXPECTED_RED, s[i]))
	{
		ft_putendl_fd(ft_charjoin(ft_charjoin(ft_charjoin(UNEXPECTED_TOKEN, '`',
						FREE_OFF), s[i], FREE_ON), '\'', FREE_ON), 2, FREE_ON);
		return (START_RD_LN);
	}
	return (0);
}

static int	valid_redircet(char	*s)
{
	int	i;

	i = -1;
	while (s[++i] && !ft_strchr(UNEXPECTED, s[i]))
	{
		if ((s[i] == '>' && s[i + 1] == '>' && ++i && ++i)
			|| (s[i] == '<' && s[i + 1] == '<' && ++i && ++i)
			|| (s[i] == '<' && ++i)
			|| (s[i] == '>' && ++i))
		{
			if (find_unexpected_token(s, i) == START_RD_LN)
				return (START_RD_LN);
		}
	}
	return (0);
}

static int	unexpected_newline(char *tmp, int *i)
{
	while (tmp[*i] && !ft_strchr(UNEXPECTED, tmp[*i]))
		++(*i);
	if (tmp[*i] && ft_strchr(UNEXPECTED, tmp[*i]) && ++(*i))
	{
		while (tmp[*i] && ft_strchr(SPACES, tmp[*i]))
			(*i)++;
		if (tmp[*i] == '\0')
		{
			ft_putendl_fd(ft_charjoin(ft_strjoin_1(ft_charjoin
						(UNEXPECTED_TOKEN, '`', FREE_OFF),
						"newline"), '\'', FREE_ON), 2, FREE_ON);
			return (START_RD_LN);
		}
	}
	return (0);
}

static int	unexpected_char(char *tmp, int i)
{
	if (tmp[i] == '\0' || ft_strchr(UNEXPECTED, tmp[i]))
	{
		if (tmp[i] == '\0' || ft_strchr(UNEXPECTED, tmp[i]))
		{
			ft_putendl_fd(ft_charjoin(ft_charjoin(ft_charjoin(UNEXPECTED_TOKEN,
							'`', FREE_OFF), tmp[i], FREE_ON),
					'\'', FREE_ON), 2, FREE_ON);
			return (START_RD_LN);
		}
	}
	return (0);
}

int	unexpected_tokens(t_parse *p)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = p->rd_ln;
	while (tmp[i])
	{
		if (valid_redircet(tmp + i) == START_RD_LN)
			return (START_RD_LN);
		while (tmp[i] && ft_strchr(SPACES, tmp[i]))
			i++;
		if (tmp[i] && ft_strchr(UNEXPECTED, tmp[i]))
		{
			if (unexpected_char(tmp, i) == START_RD_LN)
				return (START_RD_LN);
		}
		else
			if (unexpected_newline(tmp, &i) == START_RD_LN)
				return (START_RD_LN);
		if (tmp[i] && !ft_strchr(UNEXPECTED, tmp[i]))
			i++;
	}
	return (0);
}
