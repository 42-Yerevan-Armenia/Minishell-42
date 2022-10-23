/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_hdoc_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 09:22:00 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/23 09:45:07 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_single_qutoe(char *str)
{
	int	i;

	i = 0;
	while (str[i] &&  ft_strchr(SPACES, str[i]))
		i++;
	if (str[i] == '\'')
		return (HDOC_SQ_MODE);
	return (HDOC_DQ_MODE);
}

int	find_hdoc_mode(char *str)
{
	int i;
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

int get_all_hd_modes(t_parse *parser)
{
    char    **tmp;
    int i;

    i = 0;
    tmp = parser->join_pipe;
    parser->data->hdoc_mode = malloc(sizeof(char *) * (arr_double_len(tmp) + 1));
    fill_null((void *)&parser->data->hdoc_mode, arr_double_len(tmp) + 1);
    while (tmp[i])
    {
        parser->data->hdoc_mode[i] = malloc(sizeof(int));
        parser->data->hdoc_mode[i][0] = find_hdoc_mode(tmp[i]);
        i++;
    }
    return (0);
}