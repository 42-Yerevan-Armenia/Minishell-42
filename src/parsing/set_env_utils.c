/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:38:38 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/10 20:09:52 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_var_rap_helper(t_env *head, int flag, t_env *new_node)
{
	head = get_node(head, new_node->key);
	if (head != NULL)
	{
		if (flag == 0 && new_node->val
			&& !free_arr(&head->val) && !free_arr(&head->key))
		{
			head->key = ft_strdup(new_node->key);
			head->val = ft_strdup(new_node->val);
		}
		else if (new_node->val && !free_arr(&head->key))
		{
			head->key = ft_strdup(new_node->key);
			head->val = ft_strjoin_1(head->val, new_node->val);
		}
		return (1);
	}
	return (0);
}

int	find_var_rap(t_list_env *env, t_env *new_node)
{
	int		i;
	int		flag;

	i = ft_strlen(new_node->key);
	flag = 0;
	if (i >= 2 && new_node->key[i - 2] == '+' && ++flag)
	{
		new_node->key[i - 2] = '=';
		new_node->key[i - 1] = '\0';
	}
	if (find_var_rap_helper(env->head, flag, new_node) == 1)
		return (1);
	return (0);
}
