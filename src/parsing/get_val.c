/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:45:02 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/08 21:53:24 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_val(t_env *head, char *key)
{
	char	*ptr;

	ptr = ft_strjoin(key, "=");
	while (key && head)
	{
		if (!ft_strcmp(head->key, key))
			return (head->val);
		if (!ft_strcmp(head->key, ptr) && !free_arr(&ptr))
			return (head->val);
		head = head->next;
	}
	free_arr(&ptr);
	return (NULL);
}

t_env	*get_node(t_env *head, char *key)
{
	char	*ptr;

	ptr = ft_strjoin(key, "=");
	while (key && head)
	{
		if (!ft_strcmp(head->key, key))
			return (head);
		if (!ft_strcmp(head->key, ptr) && !free_arr(&ptr))
			return (head);
		head = head->next;
	}
	free_arr(&ptr);
	return (NULL);
}
