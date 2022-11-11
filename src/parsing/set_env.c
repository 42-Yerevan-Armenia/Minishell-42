/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 09:49:58 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/11 21:07:27 by vaghazar         ###   ########.fr       */
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

static int	set_env_helper(t_list_env *env, t_env **new_node)
{
	int	i;

	i = ft_strlen((*new_node)->key);
	if (env->head == NULL)
	{
		if ((*new_node)->is_export != FORME)
			++(env->size);
		if (i != 0 && i != 1 && (*new_node)->key[i - 2] == '+')
		{
			(*new_node)->key[i - 2] = '=';
			(*new_node)->key[i - 1] = '\0';
		}
		env->head = *new_node;
		env->tail = *new_node;
		return (1);
	}
	if (find_var_rap(env, *new_node))
	{
		del_one(new_node);
		return (2);
	}
	return (0);
}

static void	put_env(t_data *data, t_env *new_node)
{
	int	v_ret;
	v_ret = set_env_helper(data->env, &new_node);
	if (v_ret == 0)
	{
		if (new_node->is_export != FORME)
			++(data->env->size);
		data->env->tail->next = new_node;
		new_node->prev = data->env->tail;
		data->env->tail = data->env->tail->next;
	}
	data->envp = env_cpy(data, data->env);
}

int	set_env(t_data *data, t_env *new_node)
{
	int		mode;
	int		v_ret;

	mode = new_node->is_export;
	if (new_node->key == NULL)
		return (1);
	if ((new_node->is_export == EXPORT
			|| new_node->is_export == (ENV | EXPORT)))
	{
		new_node->is_export = EXPORT;
		v_ret = set_env_helper(data->env_exp, &new_node);
		if (v_ret == 0 && ++(data->env_exp->size))
			set_exp(data->env_exp, new_node);
	}
	if (((mode == ENV || mode == (ENV | EXPORT))
			|| mode == FORME))
	{
		if (mode != FORME)
			v_ret = ENV;
		put_env(data, new_env(new_node->key, new_node->val, v_ret));
		if (mode != EXPORT && mode != (ENV | EXPORT))
			del_one(&new_node);
	}
	return (0);
}
