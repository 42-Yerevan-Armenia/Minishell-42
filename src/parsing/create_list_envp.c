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
	list->l_size = 0;
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
	new_node->val = ft_strdup(val);
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

static int del_one(t_env *env)
{
	free_arr(&(env)->key);
	free_arr(&(env)->val);
	// printf("%p\n", (env));
	free((env));
	return (0);
}


static int set_null(t_list_env **env)
{
	(*env)->head = NULL;
	(*env)->tail = NULL;
	(*env)->l_size = 0;
	return (0);
}

static	int find_var_rap(t_list_env **env, t_env *new_node)
{
	t_env	*head;
	int		i;
	int		flag;

	head = (*env)->head;
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
			if (flag == 0 && free_arr(&head->val))
				head->val = new_node->val;
			else
				head->val = ft_strjoin_1(head->val, new_node->val);
			del_one(new_node);
			return (1);
		}
		head = head->next;
	}
	return (0);
}

static void set_exp(t_list_env **env, t_env *new_node)
{
	t_env	*tmp;

	tmp = (*env)->head;
	if (find_var_rap(env, new_node))
		return ;
	while (tmp->next && ft_strcmp(tmp->key, new_node->key) <= 0)
		tmp = tmp->next;
	if (tmp->next == NULL && ft_strcmp(tmp->key, new_node->key) <= 0)
	{
		new_node->prev = tmp;
		new_node->next = NULL;
		tmp->next = new_node;
		(*env)->tail = new_node;
	}
	else
	{
		if (tmp->prev == NULL)
		{
			new_node->prev = NULL;
			(*env)->head = new_node;
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


void set_env(t_list_env **env, t_env *new_node)
{
	t_env	*tmp;
	(*env)->l_size++;
	if ((*env)->head == NULL)
	{
		(*env)->head = new_node;
		(*env)->tail = new_node;
	}
	else
	{
		if (find_var_rap(env, new_node))
			return ;
		if (new_node->is_export == 0)
		{
			(*env)->tail->next = new_node;
			new_node->prev = (*env)->tail;
			(*env)->tail = (*env)->tail->next;
		}
		else
			set_exp(env, new_node);
	}
}

static void del_env_node_helper(t_list_env **env, t_env *tmp, t_env	*del)
{
	if (tmp->prev == NULL)
	{
		tmp->next->prev = NULL;
		(*env)->head = tmp->next;
		del_one(del);
	}
	else if (tmp->next == NULL)
	{
		tmp->prev->next = NULL;
		(*env)->tail = tmp->prev;
		del_one(del);
	}
	else
	{
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		del_one(del);
	}
}

int	del_env_node(t_list_env **env, char *key)
{
	t_env	*tmp;
	t_env	*del;

	tmp = (*env)->head;
	while (tmp && ft_strcmp(tmp->key, key))
		tmp = tmp->next;
	if (tmp == NULL)
		return (1);
	del = tmp;
	if ((*env)->l_size == 1 && !set_null(env) && !del_one(del))
		return (0);
	del_env_node_helper(env, tmp, del);
	return (0);
}

char *get_env_val(t_list_env *env, char *key)
{
	t_env	*tmp;

	tmp = env->head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp->val);
		tmp = tmp->next;
	}
	return (0);
}

// int main(int ac, char **av)
// {
// 	int i;
// 	t_list_env *env;
// 	t_list_env *env_exp;
// 	char *ptr = malloc(100);
// 	// ptr[0] = 'a';
// 	// ptr = malloc(1);

// 	i = 0;
// 	if (ac == 1)
// 	{
// 		env = create_list_env();
// 		env_exp = create_list_env();
// 		set_env(&env_exp, new_env("vahan1", "hajox2", 1));
// 		set_env(&env_exp, new_env("vahan2", "hajox", 1));
// 		set_env(&env_exp, new_env("vahan4", "hajox5", 1));
// 		set_env(&env_exp, new_env("vahan5", "hajox5", 1));
// 		set_env(&env_exp, new_env("vahan", "hajox", 1));
// 		set_env(&env_exp, new_env("vahan3", "hajox3", 1));
// 		set_env(&env, new_env("vahan2", "hajox", 0));
// 		set_env(&env, new_env("vahan", "hajox", 0));
// 		set_env(&env, new_env("vahan4", "hajox5", 0));
// 		set_env(&env, new_env("vahan3", "hajox3", 0));
// 		set_env(&env, new_env("vahan5", "hajox5", 0));
// 		set_env(&env, new_env("vahan1", "hajox2", 0));
// 		del_env_node(&env, "vahan");
// 		del_env_node(&env, "vahan1");
// 		print_env(env->head);
// 		print_env(env_exp->head);
// 		while (1)
// 		{
// 		}
// 	}
// }

// t_spl_pipe *add_pipe(t_list_spl_pipe *list, t_spl_pipe *new_pipe)
// {
// 	if (list->head == NULL)
// 	{
// 		list->head = new_pipe;
// 		list->tail = new_pipe;
// 	}
// 	else 
// 	{
// 		list->tail->next = new_pipe;
// 		list->tail =  list->tail->next;
// 	}
// 	return (new_pipe);
// }

