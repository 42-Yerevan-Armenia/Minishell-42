/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:43:46 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/31 10:19:44 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_parse(t_parse *parser)
{
	free_double((void *)&parser->spl_qutoes);
	free_double((void *)&parser->spl_pipe);
	free_double((void *)&parser->join_pipe);
	free_arr((void *)&parser->key);
	return (0);
}
