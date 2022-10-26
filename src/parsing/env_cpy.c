/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:21:23 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/26 18:40:51 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_env_arr(char **env)
{
    int i;

    i = 0;
    while (env && env[i])
    {
        printf("%s\n", env[i]);
        i++;
    }
}


char **env_cpy(t_list_env *env)
{
	char	**res;
	t_env	*tmp;
	int		i;

	res = malloc(sizeof(char *) * (env->size + 1));
	if (!res && ft_perror("minishell"))
		exit(1);
	fill_null((void *)&res, env->size + 1);
	tmp = env->head;
	i = 0;
	while (tmp)
	{
		if (tmp->is_export == ENV)
			res[i++] = ft_strjoin_1(ft_strjoin(tmp->key, "="), tmp->val);
		tmp = tmp->next;
	}
	return (res);
}