/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:38:38 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/07 22:06:57 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_var_rap(t_list_env *env, t_env *new_node)
{
	t_env	*head;
	int		i;
	int		flag;

	head = env->head;
	i = ft_strlen(new_node->key);
	flag = 0;
	if (i != 0 && new_node->key[i - 1] == '=')
		new_node->key[i - 1] = '\0';
	if (i != 0 && i != 1 && new_node->key[i - 2] == '+' && ++flag)
		new_node->key[i - 2] = '\0';
	while (head)
	{
		if (!ft_strcmp(head->key, new_node->key)
			&& new_node->is_export != FORME)
		{
			if (flag == 0 && !free_arr(&head->val))
				head->val = ft_strdup(new_node->val);
			else
				head->val = ft_strjoin_1(head->val, new_node->val);
			return (1);
		}
		head = head->next;
	}
	return (0);
}
