/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_val.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 17:45:02 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/18 20:20:38 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_val(t_envp *head, char *key)
{
	while (key && head)
	{
		// printf("head->key = %s\n", head->key);
		// printf("key = %s\n", key);
		if (!ft_strncmp(head->key, key, ft_strlen(key)))
			return (head->val);
		head = head->next;
	}

	return (NULL);
}