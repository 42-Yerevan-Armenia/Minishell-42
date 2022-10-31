/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 09:49:58 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/31 19:40:49 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_exp_helper(t_list_env *env, t_env *new_node, t_env	*tmp)
{
	if (tmp->prev == NULL)
	{
		new_node->prev = NULL;
		env->head = new_node;
	}
	else
	{
		new_node->prev = tmp->prev;
		tmp->prev->next = new_node;
	}
	new_node->next = tmp;
	tmp->prev = new_node;
}

static void	set_exp(t_list_env *env, t_env *new_node)
{
	t_env	*tmp;

	tmp = env->head;
	while (tmp->next && ft_strcmp(tmp->key, new_node->key) <= 0)
		tmp = tmp->next;
	if (tmp->next == NULL && ft_strcmp(tmp->key, new_node->key) <= 0)
	{
		new_node->prev = tmp;
		new_node->next = NULL;
		tmp->next = new_node;
		env->tail = new_node;
	}
	else
		set_exp_helper(env, new_node, tmp);
}

static int	set_env_helper(t_list_env *env, t_env **new_node, t_env **tmp)
{
	if (env->head == NULL)
	{
		if ((*new_node)->is_export != FORME)
			++(env->size);
		env->head = *new_node;
		env->tail = *new_node;
		return (1);
	}
	if (find_var_rap(env, *new_node))
	{
		if ((*new_node)->is_export == EXPORT)
			*tmp = NULL;
		del_one(new_node);
		return (2);
	}
	return (0);
}

static void	put_env(t_data *data, t_env *new_node, t_env *tmp)
{
	int	v_ret;

	v_ret = set_env_helper(data->env, &tmp, &new_node);
	if (v_ret == 0)
	{
		if (tmp->is_export != FORME)
			++(data->env->size);
		data->env->tail->next = tmp;
		tmp->prev = data->env->tail;
		data->env->tail = data->env->tail->next;
	}
	data->envp = env_cpy(data, data->env);
}


void	set_env(t_data *data, t_env *new_node)
{
	t_env	*tmp;
	int		v_ret;

	tmp = NULL;
	if (new_node->is_export == (ENV | EXPORT))
		tmp = new_env(new_node->key, new_node->val, new_node->is_export);
	else
		tmp = new_node;
	if (new_node && (new_node->is_export == EXPORT
			|| new_node->is_export == (ENV | EXPORT)))
	{
		v_ret = set_env_helper(data->env_exp, &new_node, &tmp);
		if (v_ret == 0 && ++(data->env_exp->size))
			set_exp(data->env_exp, new_node);
	}
	if (tmp && ((tmp->is_export == ENV || tmp->is_export == (EXPORT | ENV))
			|| tmp->is_export == FORME))
		put_env(data, new_node, tmp);
}
