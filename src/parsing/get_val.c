/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:45:02 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/12 19:25:15 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_val(t_env *head, char *key, int mode)
{
	char	*ptr;

	ptr = ft_strjoin(key, "=");
	while (key && head)
	{
		if (!ft_strcmp(head->key, key) && head->is_export == mode
			&& !free_arr(&ptr))
			return (head->val);
		if (!ft_strcmp(head->key, ptr) && head->is_export == mode
			&& !free_arr(&ptr))
			return (head->val);
		head = head->next;
	}
	free_arr(&ptr);
	return (NULL);
}

t_env	*get_node(t_env *head, char *key, int mode)
{
	char	*ptr;
	int		len;

	len = 0;
	ptr = NULL;
	len = ft_strlen(key);
	if (len != 0 && key[len - 1] == '=')
	{
		ptr = ft_strdup(key);
		ptr[len - 1] = '\0';
	}
	else
		ptr = ft_strjoin(key, "=");
	while (key && head)
	{
		if (!ft_strcmp(head->key, key) && head->is_export == mode
			&& !free_arr(&ptr))
			return (head);
		if (ptr && !ft_strcmp(head->key, ptr) && head->is_export == mode
			&& !free_arr(&ptr))
			return (head);
		head = head->next;
	}
	free_arr(&ptr);
	return (NULL);
}
