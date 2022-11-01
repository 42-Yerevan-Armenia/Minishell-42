/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:45:02 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/01 20:26:27 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_val(t_env *head, char *key)
{
	while (key && head)
	{
		if (!ft_strcmp(head->key, key))
			return (head->val);
		head = head->next;
	}
	return (NULL);
}
