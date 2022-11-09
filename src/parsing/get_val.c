/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:45:02 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/09 19:55:13 by vaghazar         ###   ########.fr       */
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
	int		i;

	i = 0;
	ptr = NULL;
	while (key[i])
		i++;
	if (i != 0 && key[i - 1] == '=')
	{
		ptr = ft_strdup(key);
		ptr[i - 1] = '\0';
	}
	else
		ptr = ft_strjoin(key, "=");
	// printf("key = %s\n", key);
	// printf("ptr = %s\n", ptr);
	while (key && head)
	{
		if (!ft_strcmp(head->key, key) && !free_arr(&ptr))
			return (head);
		if (ptr && !ft_strcmp(head->key, ptr) && !free_arr(&ptr))
			return (head);
		head = head->next;
	}
	free_arr(&ptr);
	return (NULL);
}
