/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:27:02 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/15 18:27:14 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_envp(t_list_envp **list)
{
	while ((*list)->head)
	{
		free((t_envp *)(*list)->head->key);
		free((t_envp *)(*list)->head->val);
		if (((t_envp *)(*list)->head)->next == NULL)
		{
			free(((*list)->head));
			(*list)->head = NULL;
			break;
		}
		(*list)->head = ((t_envp *)(*list)->head)->next;
		if (((*list)->head))
			free(((t_envp *)(*list)->head)->prev);
	}
	return (0);
}
