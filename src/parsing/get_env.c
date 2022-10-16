/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:27:59 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/15 19:11:07 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*get_env(t_list_envp *env_list, char **envp)
{
	t_envp	*env;
	char	**tmp;
	int		i;

	i = 0;
	if (envp[i])
	{
		env = malloc(sizeof(t_envp));
		if (!env && write(2, "Can't allocate memory.", ft_strlen("Can't allocate memory.")))
			exit (1);
			tmp = ft_split(envp[i++], '=');
		env->key = tmp[0];
		env->val = tmp[1];
		env->is_export = 0;
		env->next = NULL;
		env->prev = NULL;
		env_list->head = env;
		free_double(&tmp);
	}
	while (envp[i])
	{
		env->next = malloc(sizeof(t_envp));
		if (!env->next && write(2, "Can't allocate memory.", ft_strlen("Can't allocate memory.")))
			exit (1);
		env = env->next;
		tmp = ft_split(envp[i++], '=');
		env->key = tmp[0];
		env->val = tmp[1];
		env->is_export = 0;
		env->next = NULL;
		env->prev = NULL;
		free_double(&tmp);
	}
	return (env_list->head);
}
