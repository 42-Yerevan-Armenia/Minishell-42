/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_hdoc_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 09:22:00 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/25 11:03:21 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_limit(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && ++i && ++i)
			count++;
		if (str[i])
			i++;
	}
	return (count);
}

static int	is_single_qutoe(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_strchr(SPACES, str[i]))
		i++;
	while (str[i] && !ft_strchr(METACHARS, str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
			return (HDOC_SQ_MODE);
		i++;
	}
	return (HDOC_DQ_MODE);
}

static int	find_hdoc_mode(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = str;
	while (tmp[i])
	{
		if (tmp[i] == '<' && tmp[i + 1] == '<' && is_single_qutoe(str + i + 2))
			return (HDOC_SQ_MODE);
		i++;
	}
	return (HDOC_DQ_MODE);
}

int	get_all_hd_modes(t_parse *parser)
{
	char	**tmp;
	int		i;

	if (heredoc_limit(parser->rd_ln) > 16
		&& ft_putstr_fd(MAX_HDOC, 2, FREE_OFF)
		&& !free_all(parser->data))
		exit(2);
	i = 0;
	tmp = parser->join_pipe;
	parser->hdoc_mode = malloc(sizeof(int *) * (arr_double_len(tmp) + 1));
	if (parser->hdoc_mode == NULL && !ft_perror("minishell: malloc: "))
		exit (1);
	fill_null((void *)&parser->hdoc_mode, arr_double_len(tmp) + 1);
	while (tmp[i])
	{
		parser->hdoc_mode[i] = malloc(sizeof(int));
		if (parser->hdoc_mode[i] == NULL && !ft_perror("minishell: malloc: "))
			exit (1);
		parser->hdoc_mode[i][0] = find_hdoc_mode(tmp[i]);
		i++;
	}
	return (0);
}

int	get_hd_mode_in_pipe(t_parse *parser)
{
	t_spl_pipe	*tmp;
	int			i;

	i = 0;
	tmp = parser->data->cmd_line->head;
	tmp->hdoc_mode = 0;
	while (tmp && parser->hdoc_mode[i])
	{
		tmp->hdoc_mode = parser->hdoc_mode[i][0];
		i++;
		tmp = tmp->next;
	}
	free_double((void *)&parser->hdoc_mode);
	return (0);
}
