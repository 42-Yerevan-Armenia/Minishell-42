/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 09:19:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/10 20:34:49 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_env(t_env *head)
{
	while (head)
	{
		if (head->is_export == ENV || head->is_export == (ENV | EXPORT))
			printf("%s%s\n", head->key, head->val);
		head = head->next;
	}
	return (0);
}

int	env(t_data *data, char **args)
{
	int			i;
	t_list_env	*env;

	i = 1;
	env = data->env;
	if (args == NULL)
		return (1);
	if (args[i] == NULL)
	{
		print_env(env->head);
		return (0);
	}
	return (0);
}
