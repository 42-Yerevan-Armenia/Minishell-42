/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:43:46 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/03 19:48:30 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_parse(t_parse *parser)
{
	// printf("parser->spl_qutoes = %d\n", parser->spl_qutoes[0]);
	free_double(&parser->spl_qutoes);


	free_double(&parser->spl_pipe);
	free_double(&parser->join_pipe);
	// free_arr(&parser->key);
	return (0);
}
