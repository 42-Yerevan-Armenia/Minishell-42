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

void del_one(t_env **env)
{
	t_env *tmp;

	tmp = *env;
	free_arr(&(*env)->key);
	free_arr(&(*env)->val);
	printf("%p\n", (*env));
	free((*env));
	(*env) = NULL;
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
	new_node->next_exp = NULL;
	new_node->prev_exp = NULL;
	return (new_node);
}

void set_null(t_list_env **env)
{
	(*env)->head = NULL;
	(*env)->tail = NULL;
	(*env)->head_exp = NULL;
	(*env)->tail_exp = NULL;
	(*env)->l_size = 0;
}
void set_env(t_list_env **env, t_env *new_node)
{
	t_env	*tmp;
	(*env)->l_size++;
	if ((*env)->head == NULL)
	{
		(*env)->head = new_node;
		(*env)->tail = new_node;
		(*env)->head_exp = new_node;
		(*env)->tail_exp = new_node;
	}
	else
	{
		if (new_node->is_export == 0)
		{
			(*env)->tail->next = new_node;
        	new_node->prev = (*env)->tail;
			(*env)->tail = (*env)->tail->next;
		}
		else
		{
			tmp = (*env)->head_exp;
			while (tmp->next_exp && ft_strcmp(tmp->key, new_node->key) <= 0)
			{
				tmp = tmp->next_exp;
			}
			// printf("tmp->key) = %s\n", tmp->key);
			if (tmp->prev_exp == NULL)
			{
				if (ft_strcmp(tmp->key, new_node->key) >= 0)
				{
					new_node->prev_exp = NULL;
					new_node->next_exp = tmp;
					tmp->prev_exp = new_node;
					(*env)->head_exp = new_node;
				}
				else
				{
					new_node->next_exp = NULL;
					new_node->prev_exp = tmp;
					tmp->next_exp = new_node;
				}
			}
			else if (tmp->next_exp == NULL)
			{
				if (ft_strcmp(tmp->key, new_node->key) >= 0)
				{
					new_node->next_exp = tmp;;
					new_node->prev_exp = tmp->prev_exp;
					tmp->prev_exp = new_node;
				}
				else
				{
					new_node->next_exp = NULL;
					new_node->prev_exp = tmp;
					tmp->next_exp = new_node;
				}
			}
			else
			{
				tmp->prev_exp->next_exp = new_node;
				new_node->next_exp = tmp;
				new_node->prev_exp = tmp->prev_exp;
				tmp->prev_exp = new_node;
			}
		}
	}
}


void	del_env_node(t_list_env **env, char *key)
{
	t_env	*tmp;
	t_env	**del;

	tmp = (*env)->head_exp;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (tmp->prev_exp == NULL)
			{
				*del = tmp;
				if ((*env)->l_size == 1)
					set_null(env);
				else
				{
					(*env)->head_exp = tmp->next_exp;
					(*env)->head->prev_exp = NULL;
				}
				del_one(del);
			}
			else
			{
				del = tmp;
				tmp->prev_exp->next_exp = tmp->next_exp;
				tmp->next_exp->prev_exp = tmp->prev_exp;
				if (tmp->next_exp == NULL)
					(*env)->tail_exp = tmp->prev_exp;
				del_one(&del);
			}
			if (tmp && tmp->prev == NULL)
			{
				del = tmp;
				if ((*env)->l_size == 1)
					set_null(env);
				else
				{
					(*env)->head = tmp->next;
					printf("barev\n");
					(*env)->head->prev = NULL;
				}
				del_one(&del);
			}
			else if (tmp)
			{
				del = tmp;
				tmp->prev_exp->next = tmp->next;
				tmp->next_exp->prev = tmp->prev;
				if (tmp->next == NULL)
					(*env)->tail = tmp->prev;
				del_one(&del);
			}
			(*env)->l_size--;
	printf("barev\n");
			break;
		}
	}
}

int main(int ac, char **av)
{
	int i;
	t_list_env *env;

	i = 0;
	if (ac == 1)
	{
		env = create_list_env();
		set_env(&env, new_env("vahan1", "hajox2", 1));
		set_env(&env, new_env("vahan2", "hajox", 1));
		set_env(&env, new_env("vahan4", "hajox5", 1));
		set_env(&env, new_env("vahan5", "hajox5", 1));
		set_env(&env, new_env("vahan", "hajox", 1));
		set_env(&env, new_env("vahan3", "hajox3", 1));
		// printf("barev\n");
		print_exp(env->head_exp);
		del_env_node(&env, "vahan");
		print_exp(env->head_exp);
		// printf("%d\n", ft_strcmp("barev1", "barev2"));
	}
}

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

