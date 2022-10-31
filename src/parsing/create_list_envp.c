/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:28:25 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/19 10:49:37 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_env	*create_list_env(void)
{
	t_list_env	*list;

	list = malloc(sizeof(t_list_env));
	if (list == NULL && !ft_perror("minishell: "))
		exit(1);
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}
