/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:43:46 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/28 19:41:30 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_parse(t_parse *parser)
{
	free_double(&parser->spl_qutoes);
	free_double(&parser->spl_pipe);
	free_double(&parser->join_pipe);
	free_double((char ***)&parser->hdoc_mode);
	free_arr(&parser->rd_ln);
	free_arr(&parser->key);
	return (0);
}
