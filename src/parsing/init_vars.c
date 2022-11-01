/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 08:31:09 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/01 08:31:14 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vars(t_vars *v, int i, int j, int k)
{
	v->i = i;
	v->j = j;
	v->k = k;
	v->c = 0;
	v->t = 0;
}
