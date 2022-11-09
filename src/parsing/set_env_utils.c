/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:38:38 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/09 20:00:50 by vaghazar         ###   ########.fr       */
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
	// if (i != 0 && new_node->key[i - 1] == '=')
	// 	new_node->key[i - 1] = '\0';
	if (i >= 2 && new_node->key[i - 2] == '+' && ++flag)
	{
		new_node->key[i - 2] = '=';
		new_node->key[i - 1] = '\0';
	}
	head = get_node(head, new_node->key);
	// if (head)
	// {
	// 	printf("stex head->key = %s\n", head->key);
	// 	printf("stex head->val = %s\n", head->val);
	// }
	if (head != NULL)
	{
		// printf("hajox\n");
		// printf("new_node->val = %s\n", new_node->val);
		// printf("new_node->key = %s\n", new_node->key);
		if (flag == 0 && new_node->val && !free_arr(&head->val) && !free_arr(&head->key))
		{
			head->key = ft_strdup(new_node->key);
			head->val = ft_strdup(new_node->val);
		}
		else if (new_node->val && !free_arr(&head->key))
		{
			head->key = ft_strdup(new_node->key);
			head->val = ft_strjoin_1(head->val, new_node->val);
		}
		// printf("astex head->key = %s\n", head->key);
		// printf("astex head->val = %s\n", head->val);
		return (1);
	}
	return (0);
}
