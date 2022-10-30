/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:28:25 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/19 10:49:37 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list_env *create_list_env(void)
{
	t_list_env *list;
	
	list = malloc(sizeof(t_list_env));
	if (list == NULL && !ft_perror("minishell"))
		exit (1);
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
	return (list);
}

t_env *new_env(char *key, char *val, int is_export)
{
	int i;
	t_env *new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node && ft_perror("minishell"))
		return (NULL);
	new_node->is_export = is_export;
	new_node->key = ft_strdup(key);
	new_node->val = NULL;
	if (val)
		new_node->val = ft_strdup(val);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

static int del_one(t_env **env)
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


static int set_null(t_list_env *env)
{
	env->head = NULL;
	env->tail = NULL;
	env->size = 0;
	return (0);
}

static	int find_var_rap(t_list_env *env, t_env *new_node)
{
	t_env	*head;
	int		i;
	int		flag;

	head = env->head;
	i = 0;
	flag = 0;
	while (new_node->key[i])
		i++;
	if (i != 0 && new_node->key[i - 1] == '+' && ++flag)
		new_node->key[i - 1] = '\0';
	while (head)
	{
		if (!ft_strcmp(head->key, new_node->key))
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

static void set_exp(t_list_env *env, t_env *new_node)
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
}

int set_env_helper(t_list_env *env, t_env **new_node, t_env **tmp)
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

void set_env(t_data *data, t_env *new_node)
{
	t_env	*tmp;
	int		v_ret;

	tmp = NULL;
	if (new_node->is_export == (ENV | EXPORT))
		tmp = new_env(new_node->key, new_node->val, new_node->is_export);
	else
		tmp = new_node;
	if (new_node && (new_node->is_export == EXPORT || new_node->is_export == (ENV | EXPORT)))
	{
		v_ret = set_env_helper(data->env_exp, &new_node, &tmp);
		if (v_ret == 0 && ++(data->env_exp->size))
			set_exp(data->env_exp, new_node);
	}
	if (tmp && ((tmp->is_export == ENV || tmp->is_export == (EXPORT | ENV))
		|| tmp->is_export == FORME))
	{
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
}

static void del_env_node_helper(t_list_env *env, t_env *tmp, t_env	*del)
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

	tmp = env->head;
	while (tmp && ft_strcmp(tmp->key, key))
		tmp = tmp->next;
	if (tmp == NULL)
		return (1);
	del = tmp;
	if (env->size == 1 && !set_null(env) && !del_one(&del))
		return (0);
	del_env_node_helper(env, tmp, del);
	return (0);
}
