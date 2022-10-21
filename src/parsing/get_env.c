/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:27:59 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/19 10:50:22 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_env(t_list_env *env_list, char **envp)
{
	t_env	*env;
	char	**tmp;
	int		i;

	i = 0;
	if (envp[i])
	{
		env = malloc(sizeof(t_env));
		if (!env && !ft_perror("minishell"))
			exit (1);
		env_list->head = env;
	}
	while (envp[i])
	{
		tmp = ft_split(envp[i++], '=');
		env->key = ft_strdup(tmp[0]);
		env->val = ft_strdup(tmp[1]);
		env->is_export = 0;
		env->next = NULL;
		env->prev = NULL;
		free_double(&tmp);
		if (envp[i])
		{
			env->next = malloc(sizeof(t_env));
			if (!env->next && !ft_perror("minishell"))
				exit (1);
			env = env->next;
		}
	}
	return (env_list->head);
}
