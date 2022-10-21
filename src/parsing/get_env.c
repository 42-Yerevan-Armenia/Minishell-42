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

t_env	*get_env(t_list_env **env_list, char **envp, int is_export)
{
	t_env	*env;
	char	**tmp;
	int		i;

	i = 0;
	while (envp[i])
	{
		tmp = ft_split(envp[i++], '=');
		env = new_env(ft_strdup(tmp[0]), ft_strdup(tmp[1]), is_export);
		set_env(env_list, env);
		free_double(&tmp);
	}
	return ((*env_list)->head);
}
