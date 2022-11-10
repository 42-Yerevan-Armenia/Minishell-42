/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_api.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 09:09:39 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/10 18:58:55 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *key, char *val, int is_export)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node && ft_perror("minishell: "))
		exit (1);
	new_node->is_export = is_export;
	new_node->key = ft_strdup(key);
	new_node->val = NULL;
	if (val)
		new_node->val = ft_strdup(val);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

int	del_one(t_env **env)
{
	if (*env != NULL)
	{
		free_arr(&(*env)->key);
		free_arr(&(*env)->val);
		free((*env));
		*env = NULL;
	}
	return (0);
}

static int	set_null(t_list_env *env)
{
	env->head = NULL;
	env->tail = NULL;
	env->size = 0;
	return (0);
}

static void	del_env_node_helper(t_list_env *env, t_env *tmp, t_env *del)
{
	if (tmp->prev == NULL)
	{
		tmp->next->prev = NULL;
		env->head = tmp->next;
		del_one(&del);
	}
	else if (tmp->next == NULL)
	{
		tmp->prev->next = NULL;
		env->tail = tmp->prev;
		del_one(&del);
	}
	else
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		del_one(&del);
	}
}

int	del_env_node(t_list_env *env, char *key)
{
	t_env	*tmp;
	t_env	*del;

	tmp = get_node(env->head, key);
	if (tmp == NULL)
		return (1);
	del = tmp;
	if (env->size == 1 && !set_null(env) && !del_one(&del))
		return (0);
	del_env_node_helper(env, tmp, del);
	return (0);
}
