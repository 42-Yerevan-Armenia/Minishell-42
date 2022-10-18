/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:40:29 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/18 21:40:47 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_heredoc(t_parse *parser, char *dlmtr)
{
	char	*res;
	char	*ptr;
	int		i;
	
	res = NULL;
	i = 0;
	while (parser->data->cmd_line->head->heredoc[i])
	{	
		free_arr(&parser->data->cmd_line->head->hdoc_input);
		while (1)
		{
			free_arr(&parser->rd_ln);
			parser->rd_ln = readline(">>");
			if (!parser->rd_ln && !ft_perror("minishell"))
				exit (1);
			if (!ft_strcmp(parser->rd_ln, dlmtr))
				break;
			res = ft_strjoin(res, parser->rd_ln);
		}
		i++;
		free_arr(&parser->rd_ln);
	}
	free_arr(&parser->rd_ln);
	return (res);
}
