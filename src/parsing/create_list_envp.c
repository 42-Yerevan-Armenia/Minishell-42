/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:28:25 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/18 21:30:55 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_envp *create_list_envp(void)
{
	t_list_envp *list;
	
    list = malloc(sizeof(t_list_envp));
    if (list == NULL && !ft_perror("minishell"))
        exit (1);
    list->head = NULL;
    list->tail = NULL;
    return (list);
}
